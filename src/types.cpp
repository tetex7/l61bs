#include "types.hpp"

l61_stat::l61_stat()
: L(NULL), work_path(STR_NULL), make_file_path(STR_NULL) {}

l61_stat::l61_stat(lua_State* L, const std::string work_path, const std::string make_file_path, std::string bin_path)
: L(L), work_path(work_path), make_file_path(make_file_path), bin_path(bin_path){}