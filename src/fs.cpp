#include "fs.hpp"
#include "l61_runer.hpp"

std::vector<std::string> split(std::string s, std::string delimiter)
{
    std::vector<std::string> out;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        out.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    return out;
}


std::string lsf(const char* dir);

std::string lsf(std::string dir)
{
    return lsf(dir.c_str());
}


C_CALL int fs_exists(lua_State* L)
{
    if (!lua_isstring(L, -1))
    {
        std::cout << "[l61/C] Error: didn't find a string on top of Lua stack\n";
        lua_pushboolean(L, 0);
        return 1;
    }
    std::string raw_dir = lua_tostring(L, -1);
    lua_pushboolean(L, fs::exists(raw_dir));
    return 1;
}


C_CALL int fs_getEx(lua_State* L)
{
    if (!lua_isstring(L, -1))
    {
        std::cout << "[l61/C] Error: didn't find a string on top of Lua stack\n";
        lua_pushboolean(L, 0);
        return 1;
    }
    std::string raw_dir = lua_tostring(L, -1);
    lua_pushstring(L, fs::extension(raw_dir).c_str());
    return 1;
}

C_CALL int fs_rfilename(lua_State* L)
{
    if (!lua_isstring(L, -1))
    {
        std::cout << "[l61/C] Error: didn't find a string on top of Lua stack\n";
        lua_pushboolean(L, 0);
        return 1;
    }
    std::string raw_dir = lua_tostring(L, -1);
    lua_pushstring(L, fs::basename(raw_dir).c_str());
    return 1;
}

C_CALL int fs_is_dir(lua_State* L)
{
    if (!lua_isstring(L, -1))
    {
        std::cout << "[l61/C] Error: didn't find a string on top of Lua stack\n";
        lua_pushboolean(L, 0);
        return 1;
    }
    std::string raw_dir = lua_tostring(L, -1);
    lua_pushboolean(L, fs::is_directory(raw_dir));
    return 1;
}

std::string lsf(const char* dir)
{
    std::string out = "";
    FLAG st = 1;
    FLAG isdir = 0;
    FLAG EOT = 0;
    std::vector<std::string> bre_file = split(exec(std::string("ls ") + dir), "\n ");
    for(auto& v : bre_file)
    {
        if (fs::is_directory(std::string(dir) + '/' + v))
        {
            if (!st)
            {
                out += " " + lsf(dir + '/' + v);
            }
            else
            {
                out += lsf(dir + '/' + v);
            }
        }
        else
        {
            if (!st)
            {
                out += " " + (dir + '/' + v);
            }
            else
            {
                out += dir + '/' + v;
            }
        }
        if (st)
        {
            st = 0;
        }

    }

    return dir;
}

C_CALL int lua_lsf(lua_State* L)
{
    if (!lua_isstring(L, -1))
    {
        std::cout << "[l61/C] Error: didn't find a string on top of Lua stack\n";
        lua_pushnil(L);
        return 1;
    }
    std::string raw_dir = lua_tostring(L, -1);
    std::string send = lsf(raw_dir);

    lua_pushstring(L, send.c_str());
    return 1;
}

