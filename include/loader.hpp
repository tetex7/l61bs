#pragma once

#ifndef LOADER_HPP
#define LOADER_HPP
#include "defs.h"

C_CALL int load(lua_State *L);
C_CALL int getdirR(lua_State *L);
void lua_libmount(lua_State *L, const char* libname, const char* as);
void lua_mount_cfun(lua_State *L, const char* fname, lua_CFunction fun_ptr);
void lua_def_string(lua_State *L, const char* dname, const char* val);
void lua_def_int(lua_State *L, const char* dname, lua_Integer val);
void lua_def_nil(lua_State *L, const char* dname);
void lua_def_float(lua_State *L, const char* dname, lua_Number val);
void lua_def_bool(lua_State *L, const char* dname, bool val);
void lua_def_table(lua_State *L, const char* table, const char* as);

#endif