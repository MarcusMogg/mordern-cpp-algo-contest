import("core.project.config")
import("core.project.project")
import("core.tool.compiler")
import("lib.detect")

function get_api()
    local target_name = "leetcode-api"
    local program_name = project.target(target_name):filename()
    -- local program_path = path.join(config.buildir(), program_name)
    local api = detect.find_program(program_name,{
        pathes = { 
            config.buildir()
        }})
    if api == nil then
        raise(format("can't find %s please run xmake build first", program_name))
    end

    return api
end


function main()
   local api = get_api()
   os.exec(api)
end