#pragma once

#ifndef FS_HPP
#define FS_HPP

#include "vals.hpp"

std::string lsf(const char* dir);

std::string lsf(std::string dir);

C_CALL int lua_lsf(lua_State* L);
C_CALL int fs_exists(lua_State* L);
C_CALL int fs_is_dir(lua_State* L);
C_CALL int fs_getEx(lua_State* L);
C_CALL int fs_rfilename(lua_State* L);

#endif