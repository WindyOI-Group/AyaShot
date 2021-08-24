#pragma once

#include"common.hpp"

namespace Aya{
    
class random_t{
private:
    static inline uint32_t rotl(const uint32_t x, int32_t k) {
        return (x << k) | (x >> (32 - k));
    }
    uint32_t seed[2];
public:
    // Return a 32bits unsigned integer.
    uint32_t next32() {
        const uint32_t s0 = seed[0]; uint32_t s1 = seed[1];
        const uint32_t result = rotl(s0 * 0x9E3779BB, 5) * 5;
        s1 ^= s0;
        seed[0] = rotl(s0, 26) ^ s1 ^ (s1 << 9);
        seed[1] = rotl(s1, 13);
        return result;
    }

    // Return a 64bits unsigned integer.
    uint64_t next64(){
        return (uint64_t) next32() << 32 | next32();
    }

    // Mix a 64bits unsigned integer.
    // More details see http://xorshift.di.unimi.it/splitmix64.c
    uint64_t mix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    // Return a double in [0,1)
    double_t next(){
        return (double_t)(((int64_t)(next_bits(26)) << 27)
            + next_bits(27)) / (double_t)(1LL << 53);
    }

    // Return a 64bits unsigned integer in [0,2^n).
    uint64_t next_bits(const int32_t n){
        return next64() >> (64 - n);
    }

    // Return a 32bits unsigned integer in [0,n).
    uint32_t next32(const uint32_t n){
        return 1ull * n * next32() >> 32;
    }

    // Return a 64bits unsigned integer in [0,n).
    uint64_t next64(const uint64_t n){
        uint64_t limit = ULLONG_MAX / n * n,val;
        while((val = next64()) > limit);
        return val % n;
    }

    // Return a double in [0,n)
    double_t next  (const double_t n){
        return n * next();
    }

    // Return a 32bits unsigned integer in [l,r].
    uint32_t next32(const uint32_t l,const uint32_t r){
        return l + next32(r - l + 1);
    }

    // Return a 64bits unsigned integer in [l,r].
    uint64_t next64(const uint64_t l,const uint64_t r){
        return l + next64(r - l + 1);
    }

    // Return a 32bits integer in [l,r].
    int32_t next32(const int32_t l,const int32_t r){
        return l + next32(r - l + 1);
    }

    // Return a 64bits integer in [l,r].
    int64_t next64(const int64_t l,const int64_t r){
        return l + next64(r - l + 1);
    }

    // Return a double in [l,r];
    double_t next  (const double_t l,const double_t r){
        return l + next(r - l);
    }

    random_t():seed{0x11111111,0x77777777}{}

    // Set the seed with a 64bits unsigned integer.
    void set_seed(const uint64_t _seed){
        seed[0] =_seed & 0xFFFFFFFF;
        seed[1] =_seed >> 32;
    }
    void set_seed(const std::string _seed){
        uint64_t _seed0 = Aya::__aya_hash_str(_seed);
        seed[0] =_seed0 & 0xFFFFFFFF;
        seed[1] =_seed0 >> 32;
    }

    template <typename C>
    typename C::value_type any(const C& c){
        return *(c.begin() + next32(c.size()));
    }

    template <typename I>
    typename I::value_type any(const I& left,const I& right){
        return *(left + next32(right - left));
    }
}__aya_random;
void set_global_seed(uint64_t seed){
    __aya_random.set_seed(seed);
}
void set_global_seed(std::string seed){
    __aya_random.set_seed(seed);
}
} //namespace : Aya