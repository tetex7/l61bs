/*
l61 type call
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

#include "types.hpp"
#include "vals.hpp"
#include <stacktrace>
#include "json.hpp"
#include <fstream>

l61_stat::l61_stat()
: L(NULL), work_path(STR_NULL), make_file_path(STR_NULL) {}

l61_stat::l61_stat(lua_State* L, const std::string work_path, const std::string make_file_path, std::string bin_path, std::string user)
: L(L), work_path(work_path), make_file_path(make_file_path), bin_path(bin_path), user_name(user){}

l61_stat::operator lua_State*()
{
    return this->L;
}
std::vector<BYTE> ldump(lua_State* L)
{
    std::vector<BYTE> out;
    BYTE* bL = (BYTE*)L;
    size_t len = arrlen(bL);
    for (size_t i = 0; i < len; i++)
    {
        out.push_back(bL[i]);
    }
    return out;
    
}


std::ostream& operator<<(std::ostream& stream, const std::vector<BYTE>& b)
{
    stream << std::hex;
    int newB = 0;
    FLAG f = 1;
    for (size_t i = 0; i < b.size(); i++)
    {
        /*if (newB != 7)
        {
            newB++;
            if(f == 1)
            {
                goto L14;
            }
            else
            {
                f = 0;
                stream << ' ';
            }
        }
        else
        {
            stream << '\n';
            newB = 0;
            f = 1;
            goto L14;
        }

    L14:*/
        stream << b[i];
    }
    stream << std::dec;
    return stream;
    
}

void mk_errror(const char* str, int code, const char* mg)
{
    std::cout << "\n\n!!" << str << "!! :-(\n\ndumping L61stat@" << &L61stat << '\n';
    std::cout << L61stat << "\n\n";

    std::cout << "START OF SPATHS\n";
    for(const std::string& path : spaths)
    {
        std::cout << "  " << path << '\n';
    }
    std::cout << "END OF SPATHS\n\n";
    //std::cout << "START OF STACKTRACE\n" <<  std::stacktrace::current() << "\nSTART OF STACKTRACE\n\n";
    if (std::string(mg) == STR_NULL)
    {
        std::cout << "MSG: " << mg << '\n';
    }
    for (size_t i = 0; i < 400; i++);
    if ((getlocc() <= 10))
    {
        abort();
    }
    exit(code);
}

static std::string dm()
{
    std::stringstream st;
    const size_t* p = (size_t*)&L61stat;
    const size_t len = sizeof((size_t*)&L61stat);
    for (size_t i = 0; i < len; i++)
    {
        st << std::hex << p[i];
    }
    return st.str();
}
std::ostream& operator<<(std::ostream& stream, const l61_stat& Ls)
{
    stream 
    << "LUA_State: " << Ls.L 
    << "\nuser name: " << Ls.user_name 
    << "\nPWD: " << Ls.work_path 
    << "\nROOT: " << Ls.bin_path
    << "\nscript: " << Ls.make_file_path
    << "\nLUAS: " << std::hex << ((const size_t*)Ls.L)[2] << std::dec
    << "\nSTAGE: E" << getlocc()
    << "\nLINK: " << STRex("https://github.com/tetex7/l61bs/tree/main/doc/ecode/E", getlocc(), ".md")
    //<< "\nCONF: " << Ls.conf
    << "\nL61stat DUMP: 0x" << dm();
    return stream;
}


std::ostream& operator<<(std::ostream& stream, const confg_t& Ls)
{
    stream << '(' << Ls.confg_vid << ", " << Ls.lib_pre_load << ')';
    return stream;
}

std::vector<std::string> gettap_str(lua_State* L, std::string name)
{
setlocc(9);
    std::vector<std::string> out;
    
    lua_getglobal(L, name.c_str());
    lua_len(L, -1);
    size_t len = lua_tointeger(L, -1);
    lua_pop(L, -1);
    int32_t s = -1;
    for (size_t i = 1; i < len; i++)
    {
        lua_geti(L,-1, i);
        out.push_back(lua_tostring(L, -1));
        lua_pop(L, -1);
        
    }
    return out;
}

std::vector<std::string> iterateOverIntStrTable(lua_State *L, int index) 
{
    // push the first key
    std::vector<std::string> out;
    lua_pushnil(L);
    
    // while there are elements in the table
    while (lua_next(L,index) != 0) {
        // key at index -2
        int key = (int)lua_tointeger(L,-2);
        
        // value at index -1
        const char *value = lua_tostring(L,-1);
        
        // pop the value, keep the key for the next iteration
        lua_pop(L,1);
        
        // print
        out.push_back(value);
    }
    return out;
}
using nlohmann::json;
confg_t mk_confg()
{
    confg_t out = {"", 0, std::vector<lib_load_data>()};
    std::ifstream file = std::ifstream("/etc/l61confg.conf61");
    json jso;
    file >> jso;

    out.confg_vid = jso["confg_vid"].get<std::string>();
    out.lib_pre_load = jso["lib_pre_load"].get<FLAG>();
    std::vector<lib_load_data> ldata;
    for(const json& j : jso["libload"].get<std::vector<json>>())
    {
        ldata.push_back((lib_load_data){j["as"].get<std::string>(), j["lib"].get<std::string>(), j["tap"].get<FLAG>()});
    }
    out.ldata = ldata;
    return out;
}

std::ostream& operator<<(std::ostream& stream, const lib_load_data& s)
{
    stream << '(' << s.as << ", " << s.lib << ", " << s.tap << ')';
    return stream;
}