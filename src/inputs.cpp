#include "inputs.hpp"

#define DEBUG_INPUTS 0

std::string get_input(std::string say)
{
    if (say != STR_NULL)
    {
        std::cout << say << ' ';
    }
    std::vector<char> out_vet;
    char key = 0;
    while(key != ENTER_KEY_CODE)
    {
        key = std::cin.get();
#   if DEBUG_INPUTS == 1
        std::cout << "hex: " << std::hex << (int)key << std::dec << "\n";
#   endif
        switch (key)
        {
        case BACK_SPACE_KEY_CODE:
            out_vet.pop_back();
            break;
        
        default:
            out_vet.push_back(key);
        }        
    }
    out_vet.push_back('\0');
    std::string out = std::string(out_vet.data());
    std::cout << '\n';
    return out;
}