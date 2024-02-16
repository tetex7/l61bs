/*
l61 input calls header
Copyright (C) 2024  Tete

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