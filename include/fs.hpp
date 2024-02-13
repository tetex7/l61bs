#pragma once

#ifndef FS_HPP
#define FS_HPP

#include "vals.hpp"

C_CALL int fs_exists(lua_State* L);
C_CALL int fs_is_dir(lua_State* L);
C_CALL int fs_getEx(lua_State* L);
C_CALL int fs_rfilename(lua_State* L);
C_CALL int fs_delet(lua_State* L);
C_CALL int fs_mkdir(lua_State* L);
C_CALL int fs_copy(lua_State* L);
C_CALL int fs_copyr(lua_State* L);
C_CALL int  fs_list_files(lua_State* L);

#endif