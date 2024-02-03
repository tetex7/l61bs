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


struct l61_stat
{
    lua_State* L;
    std::string work_path;
    std::string make_file_path;
    std::string bin_path;
    std::string user_name;
    l61_stat();
    l61_stat(lua_State* L, const std::string work_path, const std::string make_file_path, std::string bin_path, std::string user);
};



#endif