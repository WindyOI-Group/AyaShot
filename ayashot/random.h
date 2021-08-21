#ifndef AYA_RANDOM_H
#define AYA_RANDOM_H

#include"common.h"

class random_t{
    private:
        static inline u32 rotl(const u32 x, int k) {
            return (x << k) | (x >> (32 - k));
        }
        u32 seed[2];
    public:
        // Return a 32bits unsigned integer.
        u32 next32() {
            const u32 s0 = seed[0]; u32 s1 = seed[1];
            const u32 result = rotl(s0 * 0x9E3779BB, 5) * 5;
            s1 ^= s0;
            seed[0] = rotl(s0, 26) ^ s1 ^ (s1 << 9);
            seed[1] = rotl(s1, 13);
            return result;
        }

        // Return a 64bits unsigned integer.
        u64 next64(){
            return (u64) next32() << 32 | next32();
        }

        // Return a 64bits unsigned integer in [0,2^n).
        u64 next_bits(const int n){
            return next64() >> (64 - n);
        }

        // Return a 32bits unsigned integer in [0,n).
        u32 next32(const u32 n){
            return 1ull * n * next32() >> 32;
        }
        
        // Return a 64bits unsigned integer in [0,n).
        u64 next64(const u64 n){
            u64 limit = ULLONG_MAX / n * n,val;
            while((val = next64()) > limit);
            return val % n;
        }

        // Return a 32bits unsigned integer in [l,r].
        u32 next32(u32 l,u32 r){
            return l + next32(r - l + 1);
        }

        // Return a 64bits unsigned integer in [l,r].
        u64 next64(u64 l,u64 r){
            return l + next64(r - l + 1);
        }

        // Return a 32bits integer in [l,r].
        int next32(int l,int r){
            return l + next32(r - l + 1);
        }

        // Return a 64bits integer in [l,r].
        i64 next64(i64 l,i64 r){
            return l + next64(r - l + 1);
        }

        random_t():seed{0x11111111,0x77777777}{}

        // Set the seed with a 64bits unsigned integer.
        void set_seed(const u64 _seed){
            seed[0] =_seed & 0xFFFFFFFF;
            seed[1] =_seed >> 32;
        }
        void set_seed(const std::string _seed){
            u64 _seed0 = __aya_hash_string(_seed);
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