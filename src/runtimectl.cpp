#include <iostream>
#include "defs.h"
#include "vals.hpp"
#include "l61_runer.hpp"
#include "loader.hpp"
#include "fs.hpp"
#include "package.hpp"
#include "inputs.hpp"


C_CALL int lexit_setcode(lua_State *L)
{
    if (lua_isinteger(L, -1))
    {
        exit_code = lua_tointeger(L, -1);
        return 0;
    }
    return 0;
}

C_CALL int getLibPathStack(lua_State *L)
{
    createIntStrTable(L, spaths);
    return 1;
}


C_CALL int pushLibPath(lua_State *L)
{
    if (lua_isstring(L, -1))
    {
        std::string path = lua_tostring(L, -1);
        spaths.push_back(path);
        return 0;
    }
    return 0;
}

C_CALL int getLibPathAt(lua_State *L)
{
    if (lua_isinteger(L, -1))
    {
        int index = (int)lua_tointeger(L, -1);
        if (index == spaths.size())
        {
            lua_pushstring(L, spaths[index - 1].c_str());
            return 1;
        }
        return 0;
    }
    return 0;
}

C_CALL int getSizeLibPath(lua_State *L)
{
    lua_pushinteger(L, spaths.size());
    return 1;
}

C_CALL int peekLibPath(lua_State *L)
{
    /*if (lua_isstring(L, -1))
    {
        std::string path = lua_tostring(L, -1);
        spaths.push_back(path);
        return 0;
    }*/
    lua_pushstring(L, spaths[spaths.size() - 1].c_str());
    return 1;
}

C_CALL int str_to_int(lua_State *L)
{
    if (lua_isstring(L, -1))
    {
        std::string str = lua_tostring(L, -1);
        int o = std::stoi(str);
        lua_pushinteger(L, o);
        return 1;
    }
}

C_CALL int popLibPath(lua_State *L)
{
    if (spaths.size() != sp_size)
    {
        spaths.pop_back();
    }
    return 0;
}

C_CALL int lexit(lua_State *L)
{
    if (lua_isinteger(L, -1))
    {
        int exitcode = lua_tointeger(L, -1);
        exit(exitcode);
    }
    else
    {
        exit(0);
    }
    return 0;
}

C_CALL int lget_input(lua_State *L)
{
    if (lua_isstring(L, -1))
    {
        std::string out = get_input(lua_tostring(L, -1));
        lua_pushstring(L, out.c_str());
        return 1;
    }
    std::string out = get_input();
    lua_pushstring(L, out.c_str());
    return 1;
}

C_CALL int mks(lua_State *L)
{
    setlocc(666);
    mk_segfault();
}

C_CALL int ctl_env(lua_State *L)
{
    setlocc(2);
    if(!lua_isstring(L, -1))
    {
        lua_pushnil(L);
        return 1;
    }

    const char* vname = lua_tostring(L, -1);
    if(const char* data = getenv(vname))
    {
        lua_pushstring(L, data);
        return 1;
    }
    else
    {
        lua_pushnil(L);
        return 1;
    }
    return 0;
}

C_CALL void loadenv(lua_State *L)
{
    const std::vector<lib_load_data>& ldata = L61stat.conf.ldata;
    for(const lib_load_data& data : ldata)
    {
        if (data.as != "NULL")
        {
            lua_libmount(L, data.lib.c_str(), data.as.c_str(), data.tap);
        }
    }
}
