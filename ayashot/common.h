#ifndef AYA_COMMON_H
#define AYA_COMMON_H

#define VERSION "0.0.1"

//Container
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>

#include <cstdio>
#include <cctype>
#include <cstddef>
#include <cmath>
#include <cstring>

#include <iostream>
#include <limits>
#include <functional>
#include <stdio.h>

//short for some typenames.
typedef int                __aya_i32;
typedef long long          __aya_i64;
typedef unsigned int       __aya_u32;
typedef unsigned long long __aya_u64;
typedef float              __aya_f32;
typedef double             __aya_f64;
typedef long double        __aya_f80;

namespace Tools{
    namespace Float2Integer{
        enum {
            _1e3=(int)1e3,_2e3=(int)2e3,_3e3=(int)3e3,_4e3=(int)4e3,_5e3=(int)5e3,
            _6e3=(int)6e3,_7e3=(int)7e3,_8e3=(int)8e3,_9e3=(int)9e5,
            _1e4=(int)1e4,_2e4=(int)2e4,_3e4=(int)3e4,_4e4=(int)4e4,_5e4=(int)5e4,
            _6e4=(int)6e4,_7e4=(int)7e4,_8e4=(int)8e4,_9e4=(int)9e4,
            _1e5=(int)1e5,_2e5=(int)2e5,_3e5=(int)3e5,_4e5=(int)4e5,_5e5=(int)5e5,
            _6e5=(int)6e5,_7e5=(int)7e5,_8e5=(int)8e5,_9e5=(int)9e5,
            _1e6=(int)1e6,_2e6=(int)2e6,_3e6=(int)3e6,_4e6=(int)4e6,_5e6=(int)5e6,
            _6e6=(int)6e6,_7e6=(int)7e6,_8e6=(int)8e6,_9e6=(int)9e6,
            _1e7=(int)1e7,_2e7=(int)2e7,_3e7=(int)3e7,_4e7=(int)4e7,_5e7=(int)5e7,
            _6e7=(int)6e7,_7e7=(int)7e7,_8e7=(int)8e7,_9e7=(int)9e7,
            _1e8=(int)1e8,_2e8=(int)2e8,_3e8=(int)3e8,_4e8=(int)4e8,_5e8=(int)5e8,
            _6e8=(int)6e8,_7e8=(int)7e8,_8e8=(int)8e8,_9e8=(int)9e8,
            _1e9=(int)1e9,_2e9=(int)2e9
        };
        enum {
            _1eA=(__aya_i64)1e18,_1eB=(__aya_i64)2e18,_1eC=(__aya_i64)3e18,
            _1eD=(__aya_i64)4e18,_1eE=(__aya_i64)5e18
        };
    }
}

#define __aya_up(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define __aya_dn(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)

//Hash table.
std::hash <__aya_u64> __aya_hash_ullong;

std::hash <std::string> __aya_hash_string;

struct HashPair{
    std::size_t operator()
        (const std::pair<__aya_u64, __aya_u64> &p) const{
        return __aya_hash_ullong(p.first) ^ 
               __aya_hash_ullong(p.second);
    }
};

#endif