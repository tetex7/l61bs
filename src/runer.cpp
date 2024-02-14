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
    FLAG it = 0;
    if (!lua_isstring(L, -1))
    {
        std::cout << "[l61/C] input is not string\n";
    }


    std::string lib_name = lua_tostring(L, -1);

    for(const std::string& path_to : spaths)
    {
        //std::cout << path_to << " \n";
        std::string path;

        if (fs::exists(path_to + "/" + lib_name + ".lib61"))
        {
            path = path_to + "/" + lib_name + ".lib61";
        }
        else
        {
           path = path_to + "/" + lib_name + ".lua"; 
        }

        if (luaL_dofile(L, path.c_str()) == LUA_OK) {
            goto Wret;
        }
        else
        {
            std::string sd = lua_tostring(L, -1);
            if (sd.find("No such file or directory",0))
            {
                continue;
            }
            std::cerr << "[l61/C] Error loading Lua script: " << lua_tostring(L, -1) << '\n';
            exit(666);
            return 0;
        }
    }
    std::cerr << "[l61/C] Error loading Lua lib: " << lib_name << " doen't exist\n";
    return 0;
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
        lua_getglobal(L, "allowMountTableError");
        FLAG AMTE = lua_toboolean(L, -1);
        if (AMTE)
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


void lua_libmount(lua_State *L, const char* libname, const char* as, FLAG has_tale)
{
    lua_getglobal(L61stat.L, "libmount"); // get the function on the stack
    if (!lua_isfunction(L61stat.L, -1)) { 
        exit(1);
    }
    lua_pushstring(L61stat.L, libname);
    lua_pcall(L61stat.L, 1, 1, 0);
    if (lua_istable(L61stat.L, -1))
    {
        lua_setglobal(L61stat.L, as);
        return;
    }
    else if(!has_tale)
    {
        return;
    }
    std::cout << "[C] Error: didn't find lib tabl " << libname << " \n";
    return;
}


void luaT_mount_cfun(lua_State *L,const char* tabl, const char* fname, lua_CFunction fun_ptr)
{
    lua_getglobal(L61stat.L, tabl);
    if(lua_istable(L61stat.L, -1))
    {
        lua_pushcfunction(L61stat.L, fun_ptr);
        lua_setfield(L61stat.L, -2, fname);
        
    }
}

void lua_mount_cfun(lua_State *L, const char* fname, lua_CFunction fun_ptr)
{
    lua_pushcfunction(L, fun_ptr);
    lua_setglobal(L, fname);
}

void luaT_def_table(lua_State *L, const char* table, const char* mtable)
{
    lua_getglobal(L61stat.L, table);
    if(lua_istable(L61stat.L, -1))
    {
        lua_getglobal(L, mtable);
        lua_setfield(L61stat.L, -2, mtable);
        
    }
}

void lua_def_table(lua_State *L, const char* table, const char* as)
{
    lua_getglobal(L, table);
    lua_setglobal(L, as);
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
