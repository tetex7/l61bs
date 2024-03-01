/*
l61 vals header
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
#pragma once
#ifndef VALS_HPP
#define VALS_HPP
#include "defs.h"
#include "types.hpp"
#include "inputs.hpp"
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

template<typename form, typename to>
to lto_type(std::type_identity_t<form>& f)
{
    return std::bit_cast<std::type_identity_t<to>>(f);
}

C_CALL void bl61_exit();

lua_type_e lua_gettype(lua_State *L, int idx);
extern l61_stat L61stat;
extern FLAG canTRUST;
extern int exit_code;
extern WORD sage;
extern const size_t sp_size;

#define setlocc(v) (sage = v)
#define getlocc() (sage)

extern std::vector<std::string> spaths;
extern std::vector<address_t> gc_addr;
#define REP_BUG_TEXT "Copyright (C) 2024  Tete.\nFor Docs and bug reporting\nplease see: <https://github.com/tetex7/l61bs>."
#define NO_ROOT_MEG "PLEASE DO NOT RUN AS ROOT\nyou have better things to do in your life then destroy your system"
#define COPY_STR "Copyright (C) 2024  Tete\n\nThis program is free software: you can redistribute it and/or modify\nit under the terms of the GNU General Public License as published by\nthe Free Software Foundation, either version 3 of the License.\n\nThis program is distributed in the hope that it will be useful,\nbut WITHOUT ANY WARRANTY; without even the implied warranty of\nMERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\nGNU General Public License for more details.\n\nYou should have received a copy of the GNU General Public License\nalong with this program.  If not, see <https://www.gnu.org/licenses/>."
#define LCTEXT "[λ61/C++]"
#define LUATXT "[λ61/LUA]"
#endif