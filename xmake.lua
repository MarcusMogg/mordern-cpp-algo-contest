add_rules("mode.debug", "mode.release")

set_languages("cxx23")

target("mordern-cpp-algo-contest")
    set_kind("binary")
    add_files("src/*.cpp")

