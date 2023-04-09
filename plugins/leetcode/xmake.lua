includes("lib")

task("lc")
    set_category("plugin")
    on_run("main")
    set_menu {
        usage = "xmake lc [options]",
        description = "Quick generate leetcode template and run testcase locally",
        options = {
            {'f', "force", "k", false, "force update output"},
            {'g', "generate", "k", false, "generate template from leetcode"},
            {'r', "run", "k", false, "run program"},
            {},
            {nil, "target", "v", nil, "problem name copy from leetcode problem url"},
        },
    }
