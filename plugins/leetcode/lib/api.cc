#include "api.h"

#include <iostream>
#include <memory>
#include <string_view>

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
      .default_value(false);
  GetParser()
      .add_argument(kBuildName)
      .help("generator output directory path(don't need absolute)")
      .required();
}

std::string_view GeneratorCommand::ProblemName() const { return GetParser().get(kProblemName); }
bool GeneratorCommand::ForceUpdate() const { return GetParser().get<bool>(kFroceName); }
std::string_view GeneratorCommand::BuildDir() const { return GetParser().get(kBuildName); }

void GeneratorCommand::RealWork() {
  if (ForceUpdate() || !CheckMetaExist()) {
    GetMeta();
  }
}

void GeneratorCommand::GetMeta() { std::cout << GetMetaOutputPath(); }

}  // namespace leetcodeapi
