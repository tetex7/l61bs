/*
l61 fs calls header
Copyright (C) 2024  Tete

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#pragma once

#ifndef FS_HPP
#define FS_HPP

#include "vals.hpp"

C_CALL int fs_exists(lua_State* L);
C_CALL int fs_is_dir(lua_State* L);
C_CALL int fs_getEx(lua_State* L);
C_CALL int fs_rfilename(lua_State* L);
C_CALL int fs_delet(lua_State* L);
C_CALL int fs_mkdir(lua_State* L);
C_CALL int fs_copy(lua_State* L);
C_CALL int fs_copyr(lua_State* L);
C_CALL int  fs_list_files(lua_State* L);

#endif