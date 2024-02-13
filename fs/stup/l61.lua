---
---Returns a lib for name as a tabe.
---
---@param name string
---@return table|nil
function libmount(name)
    return {}
end

---comment
---@param path string
function pushLibPath(path)
    
end

---comment
---@param say string|nil
---@return string
function input(say)
    
end

---comment
---@return string
function input()
    
end

function pushLibPath()
    
end

---@return string
function peekLibPath()
    
end

---@return integer
function getSizeLibPath()
    
end
---comment
---@param index integer
---@return string
function getLibPathAt(index)
    
end

---@return table
function getLibPathStack()
end


---
---Returns a string output for cmd.
---
---@param cmd string
---@return string
function exec(cmd)
    return ""
end

---
---Returns a the root install path to l61.
---
---@param cmd string sdsd
---@return string|nil
function getdirR(name)
    return ""
end

function lsf(dir)
    return ""
end


---
---Returns true if a path exists.
---
---@param path string paht
---@return boolean
function libfs.exists(path)
    return false
end

---@param code integer paht
--@return none
function setExitCode(code)
    
end

--- the main function
---@param argc integer
---@param argv table
---@return integer
function main(argc, argv)
    return 0
end

---
---Returns the length of a tabe.
---
---@param tap tabe paht
---@return integer|nil
function libl61.taplelen(tap)
--    local out_len = 0
--    for i = 1, 855 do
--        local v = tap[i]
--        if v == nil then
--            return out_len
--            
--        else
--            out_len = out_len + 1
--        end
--    end
    return 0
end

---
---Returns true if a path exists.
---
---@param path string paht
---@return boolean
function libfs.is_dir(path)
    --C++ code
    return false
end

---
---
---
---@param path string paht
---@return string
function libfs.getEx(path)
    
end



---comment
---@param from string
---@param to string
function libfs.copy(from, to)
    
end


function mk_segfault()
    
end

---comment
---@param from string
---@param to string
function libfs.copyr(from, to)
    
end

---comment
---@param dir string
---@return table
function libfs.list_files_c(dir)
    --    local df = l61.stringEx.split(exec(string.format("ls %s", dir)), "  \n")
    --    return df
end
---
---
---
---@param path string paht
---@return string
function libfs.raw_filename(path)
    
end

---@param path string paht
function libfs.delet(path)
    
end

---@param path string paht
function libfs.mkdir(path)
    
end

---comment
---@param code integer
function l61.exit(code)
    
end

---comment
---@param code integer
function sys.exit(code)
    
end

---preload var var of libl61

sys = {}
sys.argv = {}
sys.argc = 0
sys.l61 = l61
sys.fs = fs

sys.user = ""
DEBUG = false
---@type boolean
allowMountTableError = false
--@type osdateparam
--sd = {}
L61_VID = ""
l61 = libl61
fs = libfs
os = sys
---the PWD as of $PWD in bash
PWD = ""
