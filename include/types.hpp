/*
l61 types header
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
#ifndef TYPES_HPP
#define TYPES_HPP
#include "defs.h"
#include <lua.hpp>

/*#define Lua_getVal(LUA_STAT, v_name, e_name) \
FLAG err_##e_name = 0; \
if (lua_getglobal(LUA_STAT, v_name) != LUA_OK) \
{ \
    err_##e_name = 1; \
}*/

struct term_group_t
{
    std::string name;
    uint16_t id;
};


struct prog_info
{
    std::string fname;
    std::vector<std::string> args;
    std::string output;
};

struct lib_load_data
{
    std::string as;
    std::string lib;
    FLAG tap;
};
std::ostream& operator<<(std::ostream& stream, const lib_load_data& Ls);

struct confg_t
{
    std::string confg_vid;
    FLAG lib_pre_load;
    std::vector<lib_load_data> ldata;
};

std::vector<std::string> gettap_str(lua_State* L, std::string name);
confg_t mk_confg();
std::vector<std::string> iterateOverIntStrTable(lua_State *L, int index) ;

struct l61_stat
{
    lua_State* L;
    std::string work_path;
    std::string make_file_path;
    std::string bin_path;
    std::string user_name;
    confg_t conf = mk_confg();
    operator lua_State*();
    friend std::ostream& operator<<(std::ostream& stream, const l61_stat& Ls);
    l61_stat();
    l61_stat(lua_State* L, const std::string work_path, const std::string make_file_path, std::string bin_path, std::string user);
};
std::ostream& operator<<(std::ostream& stream, const confg_t& Ls);
void mk_errror(const char* str, int code, const char* mg);
std::ostream& operator<<(std::ostream& stream, const std::vector<BYTE>& b);
std::vector<BYTE> ldump(lua_State* L);

#endif