#pragma once

#include <filesystem>
#include <memory>
#include <string_view>
#include <type_traits>
#include <vector>

#include "argparse/argparse.hpp"

namespace leetcodeapi {
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
  [[nodiscard]] std::string_view ProblemName() const;
  [[nodiscard]] bool ForceUpdate() const;
  [[nodiscard]] std::string_view BuildDir() const;

  [[nodiscard]] std::filesystem::path GetMetaOutputPath() const {
    return std::filesystem::path(BuildDir()) / ProblemName() / "meta.json";
  }

  [[nodiscard]] bool CheckMetaExist() const { return std::filesystem::exists(GetMetaOutputPath()); }

  void GetMeta();

  static constexpr std::string_view kProblemName = "problem-name";
  static constexpr std::string_view kFroceName = "--force";
  static constexpr std::string_view kBuildName = "--build-dir";

  static size_t CallBack(void* contents, size_t size, size_t nmemb, void* userp) {
    (static_cast<std::string*>(userp))->append(static_cast<char*>(contents), size * nmemb);
    return size * nmemb;
  };
};
}  // namespace leetcodeapi