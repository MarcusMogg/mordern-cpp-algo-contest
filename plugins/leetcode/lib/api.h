#pragma once

#include <memory>
#include <string_view>
#include <type_traits>
#include <vector>

void Hello();

namespace leetcodeapi {
class ICommand {
 public:
  ICommand() = default;
  ICommand(ICommand&) = delete;
  ICommand(ICommand&& rhs) noexcept { children_.swap(rhs.children_); }

  template <class SubCommand>
    requires std::is_base_of_v<ICommand, SubCommand>
  void AddSubComand(SubCommand&& c) {
    children_.emplace_back(std::forward<SubCommand>(c));
  };
  void Run() {
    if (!CheckUsed()) {
      return;
    }
    for (const auto& i : children_) {
      i->Run();
    }
    RealWork();
  }

  virtual void ParseArgs(const std::vector<std::string_view>&) = 0;

 protected:
  virtual bool CheckUsed() = 0;
  virtual void RealWork(){};

 private:
  std::vector<std::unique_ptr<ICommand>> children_;
};
}  // namespace leetcodeapi