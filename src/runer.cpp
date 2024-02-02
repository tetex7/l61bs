#include <lua.hpp>
#include "vals.hpp"

std::vector<std::string> splitString(const std::string& input) {
    std::vector<std::string> result;
    std::string currentToken;
    bool insideQuotes = false;

    for (char c : input) {
        if (c == '\"') {
            insideQuotes = !insideQuotes;
            currentToken += c;
        } else if (c == ' ' && !insideQuotes) {
            if (!currentToken.empty()) {
                result.push_back(currentToken);
                currentToken.clear();
            }
        } else {
            currentToken += c;
        }
    }

    // Add the last token if it exists
    if (!currentToken.empty()) {
        result.push_back(currentToken);
    }

    return result;
}


int getTableLength(lua_State *L,int index) {
    lua_len(L,index); // push the length
    int length = lua_tointeger(L,-1);
    lua_pop(L,1); // pop the length
    return length;
}


C_CALL int libl61_taplelen(lua_State *L)
{
    if (lua_istable(L, -1))
    {
        int i = getTableLength(L, -1);
        lua_pushinteger(L, i);
        return 1;
    }
    lua_pushnil(L);
    return 1;
}

void createIntStrTable(lua_State *L,const std::vector<std::string> &values) {
    lua_newtable(L);
    int index = lua_gettop(L);
    
    int key = 1;
    std::vector<std::string>::const_iterator itr;
    for (itr = values.begin(); itr != values.end(); ++itr) {
        // key
        lua_pushinteger(L,key);
        key++;
        
        // value
        const char *value = (*itr).c_str();
        lua_pushstring(L,value);
        
        // set table[key] = value (pops the key and the value from the stack)
        lua_settable(L,index);
    }
    // the new table is at top of the stack
}

//extern "C"
C_CALL int load(lua_State *L)
{
    FLAG it = 1;
    if (!lua_isstring(L, -1))
    {
        std::cout << "[l61/C] input is not string\n";
    }


    std::string lib_name = lua_tostring(L, -1);

    std::string locl_path = L61stat.work_path + "/scripts/" + lib_name + ".lua";

    std::string binb_path = L61stat.bin_path + "/lib/" + lib_name + ".lua";

    if (luaL_dofile(L, locl_path.c_str()) == LUA_OK) {
        goto Wret;
    }
    else if (luaL_dofile(L, binb_path.c_str()) == LUA_OK) {
        goto Wret;
    }
    else
    {
        std::cerr << "[l61/C] Error loading Lua script: " << lua_tostring(L, -1) << '\n';
        return 1;
    }


Wret:
    // Get the global variable "myTable"
    if (lua_getglobal(L, lib_name.c_str()))
    {
        
        // Check if it's a table
        if (lua_istable(L, -1)) {
            return 1;

        } else {
            std::cerr << "[l61/C]lib table is not a table???\n";
            lua_pushnil(L);
            return 1;
        }
    }
    else
    {
        if (!it)
        {
            std::cerr << "[l61/C]no lib table???\n";
        }
        lua_pushnil(L);
        return 1;
    }
    return 0;
}


C_CALL int getdirR(lua_State *L)
{
    if (!lua_isstring(L, -1))
    {
        lua_pushnil(L);
        return 1;
    }
    else if(!lua_isnil(L, -1))
    {
        lua_pushstring(L, L61stat.bin_path.c_str());
        return 1;
    }
    else
    {
        std::cout << "[l61/C] Error: didn't find a arg on top of Lua stack\n";
        lua_pushstring(L, L61stat.bin_path.c_str());
        return 1;
    }
    std::string raw_dir = lua_tostring(L, -1);
    std::string out_dir = L61stat.bin_path + raw_dir;
    
    lua_pushstring(L, out_dir.c_str());
    return 1;
}


void lua_libmount(lua_State *L, const char* libname, const char* as)
{
    lua_getglobal(L61stat.L, "libmount"); // get the function on the stack
    if (!lua_isfunction(L61stat.L, -1)) { 
        exit(1);
    }
    lua_pushstring(L61stat.L, libname);
    lua_pcall(L61stat.L, 1, 1, 0);
    if (!lua_istable(L61stat.L, -1))
    {
        std::cout << "[C] Error: didn't find lib tabl" << libname << " \n";
        return;
    }
    else
    {
        lua_setglobal(L61stat.L, as);
    }
}


void lua_mount_cfun(lua_State *L, const char* fname, lua_CFunction fun_ptr)
{
    lua_pushcfunction(L, fun_ptr);
    lua_setglobal(L, fname);
}


void lua_def_int(lua_State *L, const char* dname, lua_Integer val)
{
    lua_pushinteger(L, val);
    lua_setglobal(L, dname);
}

void lua_def_nil(lua_State *L, const char* dname)
{
    lua_pushnil(L);
    lua_setglobal(L, dname);
}

void lua_def_float(lua_State *L, const char* dname, lua_Number val)
{
    lua_pushnumber(L, val);
    lua_setglobal(L, dname);
}

void lua_def_bool(lua_State *L, const char* dname, bool val)
{
    lua_pushboolean(L, (int)val);
    lua_setglobal(L, dname);
}

void lua_def_string(lua_State *L, const char* dname, const char* val)
{
    lua_pushstring(L, val);
    lua_setglobal(L, dname);
}
