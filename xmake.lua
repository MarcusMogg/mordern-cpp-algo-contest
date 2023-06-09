add_rules("mode.debug", "mode.release")

set_languages("cxx23")
set_warnings("all", "error")
-- set_toolchains("clang")
-- add_cxxflags("-stdlib=libc++", {tools = "clang"})

add_plugindirs(path.join(os.projectdir(), "plugins"))

includes("lcsrc")
includes("codetest")