libpak = {}


---comment
---@param name string
---@param from string
---@param to string
local function nl(name, from, to)
end
---@type function
libpak.prer = nl

libpak.name = ""
function libpak.pak()
    fs.delet(PWD.."/"..libpak.name)
    fs.copy(PWD.."/fs", PWD.."/"..libpak.name)
end