libl61={}

--function libl61.test()
--ret = {}
--local v = loadfile("./lib/" + name, "bt", ret)
--    print("fuck\n")
--end

libl61.stringEx={}
function libl61.stringEx.split (inputstr, sep)
    if sep == nil then
            sep = "%s"
    end
    local t={}
    for str in string.gmatch(inputstr, "([^"..sep.."]+)") do
            table.insert(t, str)
    end
    return t
end

function libl61.execl(cmd)
    o = exec(cmd)
    print(o)
    return o
end

