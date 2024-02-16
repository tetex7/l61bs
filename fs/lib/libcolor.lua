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
libcolor={}

local esc = string.char(27, 91)
libcolor.esc = esc
libcolor.NO_COL  = esc.."0m"
libcolor.RED     = esc.."0;31m"
libcolor.GREEN   = esc.."0;32m"
libcolor.BLUE    = esc.."0;34m"
libcolor.YELLOW  = esc.."0;33m"
libcolor.BLINK   = esc.."33;5m"
libcolor.MAGENTA = esc.."0;35m"