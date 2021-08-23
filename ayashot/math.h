#pragma once

#include"common.h"

//consts
const double pi = std::acos(-1);
const double e = std::exp(1);

//math functions.
template <typename T>
T gcd(T a, T b){ return b == 0?a:gcd(b, a % b); }

template <typename T>
T pwr(T a, T b, T mod){
    T r = 1; while (b){ if (b & 1)r = 1ll * r * r % mod; b >>= 1; } return r;
} 