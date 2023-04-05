#include <exception>

#include "api.h"

int main(int argc, const char** argv) {
  leetcodeapi::BaseCommand command;

  command.AddSubComand(leetcodeapi::GeneratorCommand{});

  try {
    command.ParseArgs(argc, argv);
    command.Run();
  } catch (const std::runtime_error& e) {
    std::cout << e.what() << "\n";
  }
}