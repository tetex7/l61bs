#include "l61_runer.hpp"

std::string exec(const char* cmd)
{
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