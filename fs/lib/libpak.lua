--Copyright (C) 2024  Tete

--This program is free software: you can redistribute it and/or modify
--it under the terms of the GNU General Public License as published by
--the Free Software Foundation, either version 3 of the License.

--This program is distributed in the hope that it will be useful,
--but WITHOUT ANY WARRANTY; without even the implied warranty of
--MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
--GNU General Public License for more details.

--You should have received a copy of the GNU General Public License
--along with this program.  If not, see <https://www.gnu.org/licenses/>.

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