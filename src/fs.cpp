/*
l61 fs code
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
    setlocc(303);
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
    setlocc(304);
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
    setlocc(308);
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
    setlocc(306);
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
    setlocc(308);
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
    setlocc(314);
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
    setlocc(304);
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
    setlocc(353);
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


C_CALL int  fs_list_files(lua_State* L)
{
    setlocc(383);
    if (!lua_isstring(L, -1))
    {
        std::cout << "[l61/C] Error: didn't find a string on top of Lua stack\n";
        lua_pushnil(L);
        return 1;
    }
    std::vector<std::string> out;
    std::string raw_dir = lua_tostring(L, -1);
    std::filesystem::path p = raw_dir;
    for (const auto& file : std::filesystem::directory_iterator{p})
    {
        out.push_back(file.path().string());
    }
    createIntStrTable(L, out);
    return 1;
}

