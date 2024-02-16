/*
l61 exec code
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
#include "l61_runer.hpp"

std::string exec(const char* cmd)
{
setlocc(8);
    std::array<char, PATH_MAX> buffer;
    std::string result;
    std::unique_ptr<FILE, getTypeOf(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

std::string exec(std::string cmd)
{
    return exec(cmd.c_str());
}

C_CALL int lua_exec(lua_State* L)
{
setlocc(450);
    if (!lua_isstring(L, -1))
    {
        std::cout << "[l61/C] Error: didn't find a string on top of Lua stack\n";
        lua_pushnil(L);
        return 1;
    }
    std::string cmd = lua_tostring(L, -1);
    std::string cmd_out = exec(cmd.c_str());

    lua_pushstring(L, cmd_out.c_str());
    return 1;
}