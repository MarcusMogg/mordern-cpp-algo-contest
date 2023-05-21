#include "api.h"

#include <exception>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <memory>
#include <string_view>

#include "curl/curl.h"
#include "nlohmann/json.hpp"

namespace leetcodeapi {

ICommand::ICommand(std::string_view name)
    : name_(name), parser_(std::make_unique<argparse::ArgumentParser>(name_)) {}

ICommand::~ICommand() = default;

void ICommand::AddSubparser(const ICommand& subcommand) {
  parser_->add_subparser(subcommand.GetParser());
}

bool ICommand::CheckUsed(const ICommand& subcommand) {
  return parser_->is_subcommand_used(subcommand.GetName());
}

// NOLINTNEXTLINE (cppcoreguidelines-avoid-c-arrays)
void BaseCommand::ParseArgs(int argc, const char* argv[]) { GetParser().parse_args(argc, argv); }

GeneratorCommand::GeneratorCommand() : ICommand("generate") {
  GetParser().add_argument(kProblemName).help("name copy from leetcode problem url");
  GetParser()
      .add_argument(kFroceName)
      .help("force update all generator output")
      .default_value(false)
      .implicit_value(true)
      .nargs(0);
  GetParser()
      .add_argument(kBuildName)
      .help("generator output directory path(don't need absolute)")
      .required();
  GetParser()
      .add_argument(kTemplateName)
      .help("generator output directory path(don't need absolute)")
      .required();
}

std::string GeneratorCommand::ProblemName() const { return GetParser().get(kProblemName); }
bool GeneratorCommand::ForceUpdate() const { return GetParser().get<bool>(kFroceName); }
std::string GeneratorCommand::BuildDir() const { return GetParser().get(kBuildName); }
std::string GeneratorCommand::TmplDir() const { return GetParser().get(kTemplateName); }

void GeneratorCommand::RealWork() {
  MakeOutputDir();
  if (ForceUpdate() || !CheckMetaExist()) {
    std::cout << "Update meta begin\n";
    int ret = GetMeta();
    std::cout << std::format("Update meta {}\n", GetResultMsg(ret));
  }
  GenTmpl();
}

int GeneratorCommand::GetMeta() {
  const auto resp = CurlLeetcode();
  if (resp.empty()) {
    return kFail;
  }

  try {
    const auto response = nlohmann::json::parse(resp);
    auto meta = nlohmann::json::parse(response["data"]["question"]["metaData"].get<std::string>());
    meta["exampleTestcases"] = response["data"]["question"]["exampleTestcases"];
    ConvertMetaJson(meta);
    const auto meta_path = GetMetaOutputPath();
    std::filesystem::create_directory(meta_path.parent_path());
    std::ofstream meta_out(meta_path);
    meta_out << meta.dump(1);
    meta_out.close();
  } catch (const std::exception& e) {
    std::cout << std::format(
        "parse leetcode response failed | response {} | error {}\n", resp, e.what());
    return kFail;
  }
  return kSuccess;
}

void GeneratorCommand::MakeOutputDir() const {
  const auto out_dir = GetOutputPath();
  if (std::filesystem::exists(out_dir)) {
    return;
  }
  std::cout << std::format("create dir {} \n", out_dir.string());
  std::filesystem::create_directories(out_dir);
}

void GeneratorCommand::GenTmpl() const {
  const auto tmpl_dir = std::filesystem::path(TmplDir());
  for (const auto& entry : std::filesystem::directory_iterator(tmpl_dir)) {
    GenTmpl(entry.path());
  }
}

void GeneratorCommand::ConvertMetaJson(nlohmann::json& meta) {
  meta["program_name"] = ProblemName();
  meta["program_cname"] = CTypeName(ProblemName());

  if (meta.contains("systemdesign") && meta["systemdesign"].get<bool>()) {
    for (auto& i : meta["constructor"]["params"]) {
      i["c_type"] = LctypeToCtype(i["type"]);
      i["parser_type"] = LcParseType(i["type"]);
      i["need_ref"] = NeedRef(i["type"]);
    }
    for (auto& methdod : meta["methods"]) {
      for (auto& i : methdod["params"]) {
        i["c_type"] = LctypeToCtype(i["type"]);
        i["parser_type"] = LcParseType(i["type"]);
        i["need_ref"] = NeedRef(i["type"]);
      }
      methdod["return"]["c_type"] = LctypeToCtype(methdod["return"]["type"]);
    }

  } else {
    meta["systemdesign"] = false;
    for (auto& i : meta["params"]) {
      i["c_type"] = LctypeToCtype(i["type"]);
      i["parser_type"] = LcParseType(i["type"]);
      i["need_ref"] = NeedRef(i["type"]);
    }
    meta["return"]["c_type"] = LctypeToCtype(meta["return"]["type"]);
  }
}

std::string GeneratorCommand::CurlLeetcode() {
  auto* handle = curl_easy_init();
  if (handle == nullptr) {
    return {};
  }
  [[maybe_unused]] std::shared_ptr<CURL> auto_clean(handle, curl_easy_cleanup);
  // well, maybe they use vernier calipers
  const auto data = std::format(
      R"({{
        "operationName":"questionData",
        "variables":{{"titleSlug":"{}"}},
        "query": "query questionData($titleSlug: String!) {{\n question(titleSlug: $titleSlug) {{\n    questionId\n    metaData\n    exampleTestcases\n  }}\n}}\n"
        }})",
      ProblemName());
  std::cout << data << "\n";
  curl_easy_setopt(handle, CURLOPT_URL, "https://leetcode.cn/graphql");  // the URL to post to
  curl_easy_setopt(handle, CURLOPT_POST, 1L);

  curl_slist* headers = nullptr;  // init to NULL is important
  [[maybe_unused]] std::shared_ptr<curl_slist> auto_clean_headers(headers, curl_slist_free_all);
  headers = curl_slist_append(headers, "Content-Type: application/json");
  curl_easy_setopt(handle, CURLOPT_HTTPHEADER, headers);

  curl_easy_setopt(handle, CURLOPT_POSTFIELDS, data.c_str());      // the data to send
  curl_easy_setopt(handle, CURLOPT_POSTFIELDSIZE, data.length());  // the size of the data
  std::string read_buffer;
  curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, CallBack);
  curl_easy_setopt(handle, CURLOPT_WRITEDATA, &read_buffer);

  const auto res = curl_easy_perform(handle);  // perform the request
  if (res != CURLE_OK) {
    std::cout << std::format("curl_easy_perform() failed: {}\n", curl_easy_strerror(res));
    return {};
  }
  return read_buffer;
}
}  // namespace leetcodeapi
