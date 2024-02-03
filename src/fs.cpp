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
    std::string fext = fs::extension(raw_dir);
    std::string out = fs::basename(raw_dir) + fext;
    lua_pushstring(L, out.c_str());
    return 1;
}

C_CALL int fs_mkdir(lua_State* L)
{
    if (!lua_isstring(L, -1))
    {
        std::cout << "[l61/C] Error: didn't find a string on top of Lua stack\n";
        return 0;
    }
    std::string raw_dir = lua_tostring(L, -1);
    fs::create_directory(raw_dir);
    return 0;
}

C_CALL int fs_delet(lua_State* L)
{
    if (!lua_isstring(L, -1))
    {
        std::cout << "[l61/C] Error: didn't find a string on top of Lua stack\n";
        return 0;
    }
    std::string raw_dir = lua_tostring(L, -1);
    fs::remove_all(raw_dir);
    //lua_pushstring(L, out.c_str());
    return 0;
}

C_CALL int fs_copyr(lua_State* L)
{
    if (!lua_isstring(L, -1))
    {
        std::cout << "[l61/C] Error: didn't find a string on top of Lua stack\n";
        return 0;
    }
    if (!lua_isstring(L, -2))
    {
        std::cout << "[l61/C] Error: didn't find a string on top of Lua stack\n";
        return 0;
    }
    std::string from = lua_tostring(L, -2);
    std::string to = lua_tostring(L, -1);
    std::filesystem::copy(to, from, std::filesystem::copy_options::recursive);
    //lua_pushstring(L, out.c_str());
    return 0;
}

C_CALL int fs_copy(lua_State* L)
{
    if (!lua_isstring(L, -1))
    {
        std::cout << "[l61/C] Error: didn't find a string on top of Lua stack\n";
        return 0;
    }
    if (!lua_isstring(L, -2))
    {
        std::cout << "[l61/C] Error: didn't find a string on top of Lua stack\n";
        return 0;
    }
    std::string from = lua_tostring(L, -2);
    std::string to = lua_tostring(L, -1);
    std::filesystem::copy(to, from, std::filesystem::copy_options::none);
    //lua_pushstring(L, out.c_str());
    return 0;
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


/*C_CALL int  fs_list_files(lua_State* L)
{
    if (!lua_isstring(L, -1))
    {
        std::cout << "[l61/C] Error: didn't find a string on top of Lua stack\n";
        lua_pushnil(L);
        return 1;
    }
    std::vector<std::string> out;
    std::string raw_dir = lua_tostring(L, -1);
    fs::path pdir = fs::absolute(raw_dir);
    fs::directory_entry d = fs::directory_entry(pdir);
    for (const auto file& : d)
    {
        out.push_back(d.string());
    }
    createIntStrTable(L, out);
    return 1;
}*/

