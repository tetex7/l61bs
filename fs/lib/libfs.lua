--Copyright (C) 2024  Tete

--This program is free software: you can redistribute it and/or modify
--it under the terms of the GNU General Public License as published by
--the Free Software Foundation, either version 3 of the License, or any later version.

--This program is distributed in the hope that it will be useful,
--but WITHOUT ANY WARRANTY; without even the implied warranty of
--MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
--GNU General Public License for more details.

--You should have received a copy of the GNU General Public License
--along with this program.  If not, see <https://www.gnu.org/licenses/>.

libfs={
    CWD = PWD
}


function libfs.list_files(dir)
    local df = l61.stringEx.split(exec(string.format("ls %s", dir)), "  \n")
    return df
end

function libfs.lfs_l(path)
    local f = fs.list_files(path)
    local files = ""
    local sep = ""
    for i = 1, l61.taplelen(f) do
        if fs.is_dir(path.."/"..f[i]) then
            files = files..sep..libfs.lfs(f[i])
        else
            files = files..sep..f[i]
        end
        sep = " "
    end
    return files
end

function libfs.lfl_l(dir)
    local df = l61.stringEx.split(libfs.lfs_l(dir), " ")
    return df
end

---comment
---@param path string
---@return string
function libfs.lfs(path)
    local f = fs.list_files(path)
    local files = ""
    local sep = ""
    for i = 1, l61.taplelen(f) do
        if fs.is_dir(path.."/"..f[i]) then
            files = files..sep..libfs.lfs(path.."/"..f[i])
        else
            files = files..sep..path.."/"..f[i]
        end
        sep = " "
    end
    return files
end

function libfs.lfl(dir)
    local df = l61.stringEx.split(libfs.lfs(dir), " ")
    return df
end
