#pragma once
#ifndef LIO_HPP
#define LIO_HPP
#include "defs.h"

constexpr size_t const_strlen(const char* str)
{
    size_t len = 0;
    while (str[len] != '\0')
    {
        len++;
    }
    return len;
}

constexpr size_t const_strlen_r(const char* str)
{
    size_t len = arrlen(str);
    return len;
}


constexpr std::vector<char> to_vec_buff(const char* str)
{
    std::vector<char> o;
    size_t len = const_strlen(str) + 1;
    for (size_t i = 0; i < len; i++)
    {
        o.push_back(str[i]);
    }
    return o;
}

std::string get_file_str(std::string f_name);
std::vector<char> get_file(std::string f_name);
std::vector<BYTE> get_file_b(std::string f_name);
std::string get_input(std::string say = STR_NULL);

#endif