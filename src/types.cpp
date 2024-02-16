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
    << "\nL61stat DUMP: 0x" << dm();
    return stream;
}