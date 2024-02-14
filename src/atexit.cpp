#include "vals.hpp"


std::vector<VOID_FPTR> exit_funs;
std::vector<address_t> gc_addr;

C_CALL void bl61_exit()
{
    mk_segfault();
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