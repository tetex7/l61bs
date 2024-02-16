/*
l61 exit code
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
#include "vals.hpp"


std::vector<VOID_FPTR> exit_funs;
std::vector<address_t> gc_addr;

C_CALL void bl61_exit()
{
setlocc(2);
    if(gc_addr.empty())
    {
        goto eL1;
    }
    for(const address_t adder : gc_addr)
    {
        free(to_ptr<void*>(adder));
    }
eL0:
    if(exit_funs.empty())
    {
        goto eL1;
    } 
    for(const VOID_FPTR v : exit_funs)
    {
        v();
    }
eL1:
    if (L61stat.L != NULL)
    {
        lua_close(L61stat.L);
        L61stat.L = NULL;
        goto eL2;
    }
eL2:
    return;
}