#pragma once

#include <filesystem>
#include <map>
#include <memory>
#include <regex>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

#include "argparse/argparse.hpp"

namespace leetcodeapi {

[[maybe_unused]] static constexpr int kFail = -1;
[[maybe_unused]] static constexpr int kSuccess = 0;

inline std::string_view GetResultMsg(int ret) { return ret == kSuccess ? "success" : "fail"; }

inline std::string CTypeName(std::string_view input) {
  std::string res;
  std::regex_replace(back_inserter(res), input.begin(), input.end(), std::regex(R"([\s|-])"), "");
  return res;
}

inline std::string_view LctypeToCtype(std::string_view lctype) {
  // TODO(mogg): new type here
  static const std::map<std::string_view, std::string_view> kConvertMap{
      {"integer", "int"},
      {"integer[]", "std::vector<int>"},
      {"string", "std::string"},
      {"string[]", "std::vector<std::string>"},
      {"list<boolean>", "std::vector<bool>"},
  };

  const auto it = kConvertMap.find(lctype);
  if (it == kConvertMap.end()) {
    return "Unknown";
  }
  return it->second;
}

inline std::string_view LcParseType(std::string_view lctype) {
  // TODO(mogg): new type here
  static const std::map<std::string_view, std::string_view> kConvertMap{
      {"integer", "IntParser"},
      {"integer[]", "VectorParser<IntParser>"},
      {"string", "StringParser"},
      {"string[]", "VectorParser<StringParser>"},
      {"list<boolean>", "VectorParser<BoolParser>"},
  };

  const auto it = kConvertMap.find(lctype);
  if (it == kConvertMap.end()) {
    return "Unknown";
  }
  return it->second;
}

class ICommand {
 public:
  explicit ICommand(std::string_view name);
  ICommand(ICommand&) = delete;
  ICommand(ICommand&& rhs) noexcept = default;

  virtual ~ICommand();

  template <class SubCommand>
    requires std::is_base_of_v<ICommand, SubCommand>
  void AddSubComand(SubCommand&& c) {
    AddSubparser(*children_.emplace_back(
        // NOTICE: SubCommand ptr
        std::make_unique<SubCommand>(std::forward<SubCommand>(c))));
  };

  void Run() {
    for (const auto& i : children_) {
      if (CheckUsed(*i)) {
        i->Run();
      }
    }
    RealWork();
  }

 protected:
  virtual void RealWork() = 0;

  [[nodiscard]] argparse::ArgumentParser& GetParser() const { return *parser_; }
  [[nodiscard]] std::string_view GetName() const { return name_; }

  void AddSubparser(const ICommand& subcommand);
  bool CheckUsed(const ICommand& subcommand);

 private:
  std::string name_;
  std::vector<std::unique_ptr<ICommand>> children_;
  std::unique_ptr<argparse::ArgumentParser> parser_;
};

class BaseCommand final : public ICommand {
 public:
  BaseCommand() : ICommand("leetcode-api") {}
  // NOLINTNEXTLINE (cppcoreguidelines-avoid-c-arrays)
  void ParseArgs(int argc, const char* argv[]);
  void RealWork() override {}
};

class GeneratorCommand final : public ICommand {
 public:
  GeneratorCommand();

 protected:
  void RealWork() override;

 private:
  [[nodiscard]] std::string ProblemName() const;
  [[nodiscard]] bool ForceUpdate() const;
  [[nodiscard]] std::string BuildDir() const;
  [[nodiscard]] std::string TmplDir() const;

  [[nodiscard]] std::filesystem::path GetOutputPath() const {
    return std::filesystem::path(BuildDir()) / ProblemName();
  }

  [[nodiscard]] std::filesystem::path GetMetaOutputPath() const {
    return GetOutputPath() / "meta.json";
  }

  [[nodiscard]] bool CheckMetaExist() const { return std::filesystem::exists(GetMetaOutputPath()); }

  int GetMeta();
  void MakeOutputDir() const;
  void GenTmpl() const;
  void GenTmpl(const std::filesystem::path& file_name) const;

  static constexpr std::string_view kProblemName = "problem-name";
  static constexpr std::string_view kFroceName = "--force";
  static constexpr std::string_view kBuildName = "--build-dir";
  static constexpr std::string_view kTemplateName = "--tmpl-dir";

  static size_t CallBack(void* contents, size_t size, size_t nmemb, void* userp) {
    (static_cast<std::string*>(userp))->append(static_cast<char*>(contents), size * nmemb);
    return size * nmemb;
  };
};
}  // namespace leetcodeapi