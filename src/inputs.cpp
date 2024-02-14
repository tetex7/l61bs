#include "inputs.hpp"
#include <fstream>

#define DEBUG_INPUTS 0


std::string get_file_str(std::string f_name)
{

    std::vector<char> out_vet = get_file(f_name);
    out_vet.push_back(EOS);
    std::string out = std::string(out_vet.data());
    return out;
}

std::vector<char> get_file(std::string f_name)
{
    std::fstream file = std::fstream(f_name);
    std::vector<char> out_vet;
    char ch = 0;
    while(ch != std::fstream::traits_type::eof())
    {
        ch = file.get();
        out_vet.push_back(ch);
    }
    return out_vet;
}

std::vector<BYTE> get_file_b(std::string f_name)
{
    typedef std::basic_fstream<BYTE> fstream;
    fstream file = fstream(f_name);
    std::vector<BYTE> out_vet;
    BYTE ch = 0;
    while(ch != std::fstream::traits_type::eof())
    {
        ch = file.get();
        out_vet.push_back(ch);
    }
    return out_vet;
}

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
    out_vet.push_back(EOS);
    std::string out = std::string(out_vet.data());
    //std::cout << '\n';
    return out;
}