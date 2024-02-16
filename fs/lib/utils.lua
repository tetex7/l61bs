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

---comment
---@param lang string
---@param obj string
---@return string
function pre_comp_print(primp, lang, obj)
    return color.GREEN..primp..": "..color.YELLOW..lang..color.GREEN.." -> "..color.BLUE..obj..color.NO_COL
end

---comment
---@param lang string
---@param obj string
function comp_print(primp, lang, obj)
    print(pre_comp_print(primp, lang, obj))
end