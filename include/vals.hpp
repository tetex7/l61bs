#pragma once
#ifndef VALS_HPP
#define VALS_HPP
#include "defs.h"
#include "types.hpp"
std::vector<std::string> splitString(const std::string& input);
// class d{};

enum class lua_type_e
{
    L_NONE = -1,
    L_NIL = 0,
    L_BOOLEAN = 1,
    L_NUMBER = 3,
    L_STRING = 4,
    L_TABLE = 5,
    L_FUNCTION = 6,
    L_THREAD = 8,
    L_NUMTYPES = 9,
    L_LIGHTUSERDATA = 2,
    L_USERDATA = 7, 
};

//lua_type_e:

/*#define LUA_TNONE		(-1)

#define LUA_TNIL		0
#define LUA_TBOOLEAN		1
#define LUA_TLIGHTUSERDATA	2
#define LUA_TNUMBER		3
#define LUA_TSTRING		4
#define LUA_TTABLE		5
#define LUA_TFUNCTION		6
#define LUA_TUSERDATA		7
#define LUA_TTHREAD		8

#define LUA_NUMTYPES		9*/

template<typename ret_bi>
ret_bi run(std::function<ret_bi()> fun)
{
    return fun();
}


lua_type_e lua_gettype(lua_State *L, int idx);
extern l61_stat L61stat;
extern FLAG canTRUST;
extern std::vector<std::string> spaths;
#define REP_BUG_TEXT "For Docs and bug reporting\nplease see: <https://github.com/tetex7/l61bs>."
#define NO_ROOT_MEG "PLEASE DO NOT RUN AS ROOT\nyou have better things to do in your life then destroy your system"
#define LCTEXT "[λ61/C++]"
#define LUATXT "[λ61/LUA]"
#endif