add_rules("mode.debug", "mode.release")

set_languages("cxx23")
set_warnings("all", "error")

add_plugindirs(path.join(os.projectdir(), "plugins"))

includes("lcsrc")
