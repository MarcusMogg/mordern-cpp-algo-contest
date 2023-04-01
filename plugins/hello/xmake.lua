-- 定义一个名叫hello的插件任务
task("hello")
    set_category("plugin")
    on_run(function ()
        print("hello xmake!")
    end)
    set_menu {
            usage = "xmake hello [options]",
            description = "Hello xmake!",
            options = {},
            } 