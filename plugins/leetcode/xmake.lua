includes("lib")

task("lc")
    set_category("plugin")
    on_run("main")
    set_menu {
                -- usage
                usage = "xmake hello [options]"
                -- description
            ,   description = "Hello xmake!"
                -- options
            ,   options = {}
            }
