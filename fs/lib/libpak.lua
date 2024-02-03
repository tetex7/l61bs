libpak = {}

libpak.name = ""
function libpak.pak()
    fs.delet(PWD.."/"..libpak.name)
    fs.copy(PWD.."/fs", PWD.."/"..libpak.name)
end