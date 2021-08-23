#pragma once

#define VERSION "0.0.1"

#define random __random_deprecated

//Tools
#include <cstdlib>
#include <cstdio>
#include <functional>
#include <cstdarg>

//Limits Header
#include <climits>

//Strings
#include <cctype>
#include <cstring>

//Container
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <iterator>

//Math
#include <cmath>

//File IO
#include <iostream>

#undef random


//short for some typenames.

typedef std::vector<int>   __aya_vec;
typedef std::string        __aya_str;

namespace Tools{
    namespace Float2Integer{
        enum {
            _1e3 = (int32_t)1e3, _2e3 = (int32_t)2e3, _3e3 = (int32_t)3e3, _4e3 = (int32_t)4e3, _5e3 = (int32_t)5e3,
            _6e3 = (int32_t)6e3, _7e3 = (int32_t)7e3, _8e3 = (int32_t)8e3, _9e3 = (int32_t)9e5,
            _1e4 = (int32_t)1e4, _2e4 = (int32_t)2e4, _3e4 = (int32_t)3e4, _4e4 = (int32_t)4e4, _5e4 = (int32_t)5e4,
            _6e4 = (int32_t)6e4, _7e4 = (int32_t)7e4, _8e4 = (int32_t)8e4, _9e4 = (int32_t)9e4,
            _1e5 = (int32_t)1e5, _2e5 = (int32_t)2e5, _3e5 = (int32_t)3e5, _4e5 = (int32_t)4e5, _5e5 = (int32_t)5e5,
            _6e5 = (int32_t)6e5, _7e5 = (int32_t)7e5, _8e5 = (int32_t)8e5, _9e5 = (int32_t)9e5,
            _1e6 = (int32_t)1e6, _2e6 = (int32_t)2e6, _3e6 = (int32_t)3e6, _4e6 = (int32_t)4e6, _5e6 = (int32_t)5e6,
            _6e6 = (int32_t)6e6, _7e6 = (int32_t)7e6, _8e6 = (int32_t)8e6, _9e6 = (int32_t)9e6,
            _1e7 = (int32_t)1e7, _2e7 = (int32_t)2e7, _3e7 = (int32_t)3e7, _4e7 = (int32_t)4e7, _5e7 = (int32_t)5e7,
            _6e7 = (int32_t)6e7, _7e7 = (int32_t)7e7, _8e7 = (int32_t)8e7, _9e7 = (int32_t)9e7,
            _1e8 = (int32_t)1e8, _2e8 = (int32_t)2e8, _3e8 = (int32_t)3e8, _4e8 = (int32_t)4e8, _5e8 = (int32_t)5e8,
            _6e8 = (int32_t)6e8, _7e8 = (int32_t)7e8, _8e8 = (int32_t)8e8, _9e8 = (int32_t)9e8,
            _1e9 = (int32_t)1e9, _2e9 = (int32_t)2e9
        };
        enum {
            _1eA = (int64_t)1e18, _1eB = (int64_t)2e18, _1eC = (int64_t)3e18,
            _1eD = (int64_t)4e18, _1eE = (int64_t)5e18
        };
    } // namespace Float2Integer
} // namespace Tools

//Hash table.
std::hash <uint64_t> __aya_hash_ullong;

std::hash <std::string> __aya_hash_string;

const int MAX_BUF = 1 << 20;
char __aya_buf1[MAX_BUF];
char __aya_buf2[MAX_BUF];