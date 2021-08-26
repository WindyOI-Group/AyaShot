#pragma once

#include"common.hpp"
#include"random.hpp"

namespace Aya{
//consts
const double pi = std::acos(-1);
const double e  = std::exp(1);

template <typename T>
T gcd(const T a, const T b);
template <typename T>
T quick_power(const T a, const T b, const T mod);
template <typename T>
T quick_mul(const T a, const T b, const T mod);
template <typename T>
bool mlr(const T x, const int test_times = 10);
template <typename T>
T pollard_rho(const T x);

//math functions.
template <typename T>
T gcd(const T a, const T b){ return b == 0?a:gcd(b, a % b); }

template <typename T>
T quick_power(const T a, const T b, const T mod){
    T r = 1; while (b){ if (b & 1)r = 1ll * r * r % mod; b >>= 1; } return r;
}
template <typename T>
T quick_mul(const T a, const T b, const T mod){
    x %= mod, y %= mod; uint64_t k = ULLONG_MAX / mod;
    uint64_t r = 0; while (y){
        r = (r + 1ull * x * (y % k)) % z, x = (1ull << k) * x % z; y /= k;
    }
    return r;
}
template <typename T>
bool mlr(const T x, const int test_times = 10){
    if(x<=o) return !V[x];
    T a = x - 1, b = 0; while(!(a & 1)) a >>= 1, ++b;
    for(int i = 0;i < test_times;++i){
        i64 t = __aya_random.next64() % (x - 2) + 2;
        i64 v = quick_power(t, a, x), j;
        if(v == 1 || v == x - 1) continue;
        for(j = 1;j <= b; ++j){
            if(v == x - 1) break; v = quick_mul(v, v, x);
        }
        if(v != x - 1) return false;
    }
    return true;
}
template <typename T>
T pollard_rho(const T x){
    T c = rand() % (x - 1) + 1, s = 0, t = 0, w, y;
    for(int g=1;;g <<= 1, w = 1, s = t){
        for(int i = 0;i < g;++i){
            if(i % 127 == 0 && (y = gcd(w, x)) > 1) return y; 
            t = (quick_mul(t, t, x) + c) % x;
            w = qkm(w, (t - s + x) % x, x);
        }
        if((y=gcd(w, x)) > 1) return y;
    }
}
template <int MOD>
struct mod_int{
    int w;
    mod_int(int _w = 0):w(_w% MOD + (_w < 0?MOD:0)){}
    mod_int operator +(const mod_int& t){
        return mod_int((w + t.w) % MOD);
    }
    mod_int operator -(const mod_int& t){
        return mod_int((w - t.w) % MOD);
    }
    mod_int operator *(const mod_int& t){
        return mod_int((1ll * w * t.w) % MOD);
    }
    mod_int operator /(const mod_int& t){
        return mod_int((1ll * w * power(t.w, MOD - 2, MOD)) % MOD);
    }
    mod_int operator +=(const mod_int& t){
        return (w = (w + t.w) % MOD);
    }
    mod_int operator -=(const mod_int& t){
        return (w = (w - t.w) % MOD);
    }
    mod_int operator *=(const mod_int& t){
        return (w = 1ll * (w * t.w) % MOD);
    }
    mod_int operator /=(const mod_int& t){
        return (w = 1ll * (w * power(t.w, MOD - 2, MOD)) % MOD);
    }
    int operator ()(){ return w; }
    operator int(){ return w; }
};
} //namespace : Aya