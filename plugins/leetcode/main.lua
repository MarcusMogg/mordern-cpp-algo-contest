import("core.base.option")
import("core.base.task")
import("core.project.rule")
import("core.project.config")
import("core.project.project")
import("core.tool.compiler")
import("lib.detect")

function GetProgram(target_name, lazy_build)
    if lazy_build then
        local program = detect.find_program(target_name,{
            pathes = { 
                config.buildir()
            }})
        if program ~= nil then
            return program
        end
        print(format("can't find program %s",target_name))
    end 
    project.lock()
    task.run("build", {target = target_name, all = false})
    project.unlock()

    local program = detect.find_program(target_name,{
        pathes = { 
            config.buildir()
        }})
    if program == nil then
        raise(format("can't build & find %s", target_name))
    end
    
    return program
end

function GetTargetDir(name) 
    return path.join(os.projectdir(),"lcsrc");
end 

function GetTmplDir() 
    return path.join(os.scriptdir(),"template");
end 

function GetForce(force) 
    if force then
        return "--force"
    end
    return ""
end

function main()
    local name = option.get("target")
    if name == nil then
        raise("can't find program_name")
    end

    local gen = option.get("generate") or false
    local force = option.get("force") or false
    local ouput_dir = GetTargetDir(name)
    local tmpl_dir = GetTmplDir()

    if gen then
        local api = GetProgram("leetcode-api",not force)
        print(force)
        os.execv(api, {
            "generate", 
            format("--build-dir=%s", ouput_dir), 
            format("--tmpl-dir=%s", tmpl_dir),
            name,
            GetForce(force)})
    end

    local run = option.get("run") or false

    if run then
        local api = GetProgram(name, false)
        os.execv(api, {
            path.join(GetTargetDir(),name,"simple_test_cases")
        })
    end

    task.run("format",{files = path.join("lcsrc",name,"*.cc")})
    task.run("format",{files = path.join("lcsrc",name,"*.h")})
    task.run("project",{kind = "compile_commands",outputdir = "build"})
end