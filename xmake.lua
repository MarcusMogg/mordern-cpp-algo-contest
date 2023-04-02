add_rules("mode.debug", "mode.release")

set_languages("cxxlatest")

add_plugindirs(path.join(os.projectdir(), "plugins"))

target("mordern-cpp-algo-contest")
    set_kind("binary")
    add_files("src/*.cpp")
