/*
l61 main header
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

#pragma once
#ifndef DEF_H
#define DEF_H
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#ifdef __cplusplus
extern "C" {
#endif
#define STR_NULL "\0\0\0\'NULL\x69 STR\'\0\0"
#define L61_BS 100
#define readonly const
#define SWITCH(v) v = !v
#define rlen(v) (v - 1)
#define pass continue
#define arrlen(val) ((size_t)(sizeof(val) / sizeof(*val)))
#define alen(v) rlen(arrlen(v))
#define arr(v) v*
#define mk_segfault() *(char*)NULL = 0
#define __forceinline __attribute__((always_inline))
typedef bool FLAG;

typedef readonly bool CFLAG;

typedef unsigned long       DWORD;

typedef __uint128_t       QWORD;

typedef unsigned char       BYTE;

typedef BYTE BYTE_FLAG;

typedef readonly BYTE CBYTE_FLAG;

typedef unsigned short      WORD;

typedef signed long       SDWORD;

typedef signed char       SBYTE;

typedef signed short      SWORD;

typedef void* VOID_PTR;
typedef arr(void*) VOID_PTR_ARR;
typedef void (*FREE_FUN)();
typedef volatile void* VVOID_PTR;
typedef void(*VOID_FPTR)();

typedef uint8_t address8_t;
typedef uint16_t address16_t;
typedef size_t address_t;
//#define ptr_to_addr8(ptr) (address8_t)ptr
//#define ptr_to_addr16(ptr) (address16_t)ptr
#define addr_to_ptr(add) (void*)add
#define EOS '\0'

//typedef long double ldouble_t;

typedef WORD EWORD;

#define ENTER_KEY_CODE '\x0A'
#define BACK_SPACE_KEY_CODE '\x08'
//#define LINE_FEED_KEY_CODE '\x0A'

typedef enum ERROR_STAT_e
{
	ER_FAILED = 10,
	ER_SUCCESS = 20,
	ER_UNDEF = 404,
} ERROR_STAT;

typedef struct ERROR_PAK_s
{
	ERROR_STAT STAT;
	EWORD ECODE;
} ERROR_PAK;

typedef const char* CHAR_STR;

typedef ERROR_PAK* ER_PAC_PTR;

#define MK_ECODE(DOM_CODE, SUB_CODE) (DOM_CODE + SUB_CODE)
#define ER_PAK_PLOAD {ER_UNDEF, 0}

#define ER_PAK_INIT(Nn) ERROR_PAK Nn = ER_PAK_PLOAD
#define ER_PAK_FAILED(Nn, X) \
	Nn.ECODE = X; \
    Nn.STAT = ER_FAILED; \
    return Nn

#define MK_ER_PAK(Nn, X, ST) \
	Nn.ECODE = X; \
    Nn.STAT = ST; \
    return Nn

#define ER_PAK_SUCCESS(Nn, X) \
	Nn.ECODE = X; \
    Nn.STAT = ER_SUCCESS; \
    return Nn

#define ER_PAK_UNDEF(Nn, X) \
	Nn.ECODE = X; \
    Nn.STAT = ER_UNDEF; \
    return Nn

#define ER_PAK_JOIN(Nn, _pak) \
	Nn = _pak; \
    return Nn
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include <any>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <vector>
#include <vector>
#include <string>
#include <stack>
#include <stdexcept>
#include <boost/json.hpp>
#include <boost/any.hpp>
#include <boost/system.hpp>
#include <boost/thread.hpp>
#include <boost/process.hpp>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <boost/thread.hpp>
#include <functional>
#include <map>
#include <json.hpp>
#include <signal.h>
#include <boost/algorithm/string.hpp>

namespace fs = boost::filesystem;
namespace bt = boost;
namespace po = boost::program_options;


#include <lua.hpp>
#define L61_NAME(X) namespace l61 { X }

#define getTypeOf decltype

#define C_CALL extern "C"
#define C_CALL_BLOCK(def) extern "C" {def}
//#define var auto
//#define val const auto
typedef std::u8string ustring;

template<typename... bi_args>
__inline std::string STRex(bi_args... vals)
{
    std::stringstream ss;
    (ss << ... << vals);
    return ss.str();
}

template<typename type_ptr>
constexpr type_ptr to_ptr(address_t add)
{
    return (type_ptr)add;
}

//extern std::vector<std::string> args;
#endif
#endif