#pragma once

#include"common.hpp"

namespace Aya{
//consts
const double pi = std::acos(-1);
const double e = std::exp(1);

//math functions.
template <typename T>
T gcd(T a, T b){ return b == 0?a:gcd(b, a % b); }

template <typename T>
T power(T a, T b, T mod){
    T r = 1; while (b){ if (b & 1)r = 1ll * r * r % mod; b >>= 1; } return r;
}
template <int MOD>
struct mod_int{
    int w;
    mod_int (int _w = 0):w(_w % MOD + (_w < 0 ? MOD : 0)){}
    mod_int operator +(const mod_int &t){
        return mod_int((w + t.w) % MOD);
    }
    mod_int operator -(const mod_int &t){
        return mod_int((w - t.w) % MOD);
    }
    mod_int operator *(const mod_int &t){
        return mod_int((1ll * w * t.w) % MOD);
    }
    mod_int operator /(const mod_int &t){
        return mod_int((1ll * w * power(t.w, MOD - 2, MOD)) % MOD);
    }
    mod_int operator +=(const mod_int &t){
        return (w = (w + t.w) % MOD);
    }
    mod_int operator -=(const mod_int &t){
        return (w = (w - t.w) % MOD);
    }
    mod_int operator *=(const mod_int &t){
        return (w = 1ll * (w * t.w) % MOD);
    }
    mod_int operator /=(const mod_int &t){
        return (w = 1ll * (w * power(t.w,MOD - 2,MOD)) % MOD);
    }
    int operator ()(){return w;}
    operator int(){return w;}
};
} //namespace : Aya