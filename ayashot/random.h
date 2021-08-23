#ifndef AYA_RANDOM_H
#define AYA_RANDOM_H

#include"common.h"


#define random __random_deprecated
#include <stdlib.h>
#include <cstdlib>
#include <climits>
#include <algorithm>
#undef random

class random_t{
private:
    static inline __aya_u32 rotl(const __aya_u32 x, __aya_i32 k) {
        return (x << k) | (x >> (32 - k));
    }
    __aya_u32 seed[2];
public:
    // Return a 32bits unsigned integer.
    __aya_u32 next32() {
        const __aya_u32 s0 = seed[0]; __aya_u32 s1 = seed[1];
        const __aya_u32 result = rotl(s0 * 0x9E3779BB, 5) * 5;
        s1 ^= s0;
        seed[0] = rotl(s0, 26) ^ s1 ^ (s1 << 9);
        seed[1] = rotl(s1, 13);
        return result;
    }

    // Return a 64bits unsigned integer.
    __aya_u64 next64(){
        return (__aya_u64) next32() << 32 | next32();
    }

    // Return a double in [0,1)
    __aya_f64 next(){
        return (__aya_f64)(((__aya_i64)(next_bits(26)) << 27)
            + next_bits(27)) / (__aya_f64)(1LL << 53);
    }

    // Return a 64bits unsigned integer in [0,2^n).
    __aya_u64 next_bits(const __aya_i32 n){
        return next64() >> (64 - n);
    }

    // Return a 32bits unsigned integer in [0,n).
    __aya_u32 next32(const __aya_u32 n){
        return 1ull * n * next32() >> 32;
    }

    // Return a 64bits unsigned integer in [0,n).
    __aya_u64 next64(const __aya_u64 n){
        __aya_u64 limit = ULLONG_MAX / n * n,val;
        while((val = next64()) > limit);
        return val % n;
    }

    // Return a double in [0,n)
    __aya_f64 next  (const __aya_f64 n){
        return n * next();
    }

    // Return a 32bits unsigned integer in [l,r].
    __aya_u32 next32(const __aya_u32 l,const __aya_u32 r){
        return l + next32(r - l + 1);
    }

    // Return a 64bits unsigned integer in [l,r].
    __aya_u64 next64(const __aya_u64 l,const __aya_u64 r){
        return l + next64(r - l + 1);
    }

    // Return a 32bits integer in [l,r].
    __aya_i32 next32(const __aya_i32 l,const __aya_i32 r){
        return l + next32(r - l + 1);
    }

    // Return a 64bits integer in [l,r].
    __aya_i64 next64(const __aya_i64 l,const __aya_i64 r){
        return l + next64(r - l + 1);
    }

    // Return a double in [l,r];
    __aya_f64 next  (const __aya_f64 l,const __aya_f64 r){
        return l + next(r - l);
    }

    random_t():seed{0x11111111,0x77777777}{}

    // Set the seed with a 64bits unsigned integer.
    void set_seed(const __aya_u64 _seed){
        seed[0] =_seed & 0xFFFFFFFF;
        seed[1] =_seed >> 32;
    }
    void set_seed(const std::string _seed){
        __aya_u64 _seed0 = __aya_hash_string(_seed);
        seed[0] =_seed0 & 0xFFFFFFFF;
        seed[1] =_seed0 >> 32;
    }

    template <typename C>
    typename C::value_type any(const C& c){
        return *(c.begin() + next(c.size() - 1));
    }

    template <typename I>
    typename I::value_type any(const I& left,const I& right){
        return *(left + next(right - left - 1));
    }
}__aya_random;

#endif