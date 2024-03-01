#pragma once
#ifndef RUNCTL_HPP
#define RUNCTL_HPP
#include "defs.h"

C_CALL int lexit_setcode(lua_State *L);
C_CALL int getLibPathStack(lua_State *L);
C_CALL int pushLibPath(lua_State *L);
C_CALL int getLibPathAt(lua_State *L);
C_CALL int getSizeLibPath(lua_State *L);
C_CALL int peekLibPath(lua_State *L);
C_CALL int str_to_int(lua_State *L);
C_CALL int popLibPath(lua_State *L);
C_CALL int lexit(lua_State *L);
C_CALL int lget_input(lua_State *L);
C_CALL int mks(lua_State *L);
C_CALL int ctl_env(lua_State *L);

#endif