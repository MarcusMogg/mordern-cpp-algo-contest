target("sort-the-people")
    set_kind("binary")
    add_files("*.cc")
    add_deps("lc-lib")
    after_build(function (target)
        import("core.project.config")
        local targetfile = target:targetfile()
        os.cp(targetfile, path.join(config.buildir(), path.filename(targetfile)))
        print("build %s", targetfile)
    end)
