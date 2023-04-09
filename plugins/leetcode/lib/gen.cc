// https://stackoverflow.com/questions/1825904/error-c2589-on-stdnumeric-limitsdoublemin
#define NOMINMAX

#include "api.h"
#include "inja/inja.hpp"
namespace leetcodeapi {

void GeneratorCommand::GenTmpl(const std::filesystem::path& file_name) const {
  const auto base_name = file_name.filename();
  std::string output_file_name = base_name.string().substr(0, base_name.string().find_last_of('.'));
  auto out_path = GetOutputPath() / output_file_name;

  if (ForceUpdate() || !std::filesystem::exists(out_path)) {
    std::filesystem::remove(out_path);
    inja::Environment env;
    std::cout << std::format("GenTmpl {} from {} \n", out_path.string(), file_name.string());
    env.write_with_json_file(file_name.string(), GetMetaOutputPath().string(), out_path.string());
  }
}
}  // namespace leetcodeapi