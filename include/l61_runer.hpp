#pragma once
#ifndef L61_RUNER
#define L61_RUNER
#include "vals.hpp"

std::string exec(const char* cmd);
std::string exec(std::string cmd);
C_CALL int lua_exec(lua_State* L);
std::vector<std::string> splitString(const std::string& input);
void createIntStrTable(lua_State *L,const std::vector<std::string> &values);
C_CALL int libl61_taplelen(lua_State *L);
int getTableLength(lua_State *L,int index);

#endif