#pragma once

#ifndef LSTACK_HPP
#define FSTACK_HPP

#include "vals.hpp"

template<typename bi>
struct stack : public std::vector<bi>
{
    bi& pop();
    void push(bi& d);
}

#endif