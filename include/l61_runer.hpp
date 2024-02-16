/*
l61 exce calls header
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
#ifndef L61_RUNER
#define L61_RUNER
#include "vals.hpp"

std::string exec(const char* cmd);
std::string exec(std::string cmd);
C_CALL int lua_exec(lua_State* L);
std::vector<std::string> splitString(const std::string& input);
void createIntStrTable(lua_State *L,const std::vector<std::string> &values);
C_CALL int libl61_taplelen(lua_State *L);
int getTableLength(lua_State *L,int index);

#endif