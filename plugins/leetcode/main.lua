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
    task.run("build", {target = "leetcode-api", all = false})
    local program = detect.find_program(target_name,{
        pathes = { 
            config.buildir()
        }})
    project.unlock()

    
    if program == nil then
        raise(format("can't build & find %s", program_name))
    end
    
    return program
end


function main()
    local name = option.get("target")
    if name == nil then
        raise("can't find program_name")
    end

    local gen = option.get("generate") or false

    if gen then
        local api = GetProgram("leetcode-api",false)
        os.execv(api, {"generate", format("--build-dir=%s", config.buildir()), name})
    end
end