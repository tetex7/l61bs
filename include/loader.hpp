/*
l61 libmount header
Copyright (C) 2024  tete

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

#ifndef LOADER_HPP
#define LOADER_HPP
#include "defs.h"

C_CALL int load(lua_State *L);
C_CALL int getdirR(lua_State *L);
void lua_libmount(lua_State *L, const char* libname, const char* as, FLAG has_tale = 1);
void lua_mount_cfun(lua_State *L, const char* fname, lua_CFunction fun_ptr);
void lua_def_string(lua_State *L, const char* dname, const char* val);
void lua_def_int(lua_State *L, const char* dname, lua_Integer val);
void lua_def_nil(lua_State *L, const char* dname);
void lua_def_float(lua_State *L, const char* dname, lua_Number val);
void lua_def_bool(lua_State *L, const char* dname, bool val);
void lua_def_table(lua_State *L, const char* table, const char* as);
void luaT_mount_cfun(lua_State *L,const char* tabl, const char* fname, lua_CFunction fun_ptr);

#endif