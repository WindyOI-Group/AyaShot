#ifndef AYA_RANDOM_H
#define AYA_RANDOM_H

#include"common.h"

class random_t{
    private:
        u64 seed1,seed2;
        static const u64 multiplier=0x5DEECE66DL;
        static const u64 addend    =0xBL;
        static const u64 mask      =(1LL << 48) - 1;

        u64 xor_shift_64(){
            seed1 ^= seed1 << 43;
            seed1 ^= seed1 >> 29;
            seed1 ^= seed1 << 34;
            return seed1;
        }

        u64 linear_next_64(){
            seed2 =(seed2 * multiplier + addend) & mask;
            return seed2;
        }

        u64 next(){
            return xor_shift_64() ^ linear_next_64();
        }

        u64 next_bits(const int n){
            return next()>>(64 - n);
        }

        f64 nextf(){
            return (double)(((long long)(next_bits(26)) << 27) + next_bits(27)) / (double)(1LL << 53);
        }
    
    public:
        random_t():seed1(0xA2B4C6D8E7F5A3B1),seed2(0x1B2D3F4B5D6F7B){}

        void set_seed(const u64 _seed){seed1=seed2=_seed;}
        void set_seed(const std::string _seed){seed1=seed2=__aya_hash_string(_seed);}
        
        int next_int   (){return next() & 0x7FFFFFFF;}
        int next_llong (){return next() & 0x7FFFFFFFFFFFFFFF;}
        u32 next_uint  (){return next() & 0xFFFFFFFF;}
        u64 next_ullong(){return next();}
        f64 next_double(){return nextf();}

        template <typename T>
        T next(const T n){
            return next() % (n + 1);
        }

        template <typename T>
        T nextf(const T n){
            return nextf() * n;
        }

        template <typename T>
        T next(const T left,const T right){
            if(left <= 0 && 0<= right) return -next(-left) + next(right);
            return left + next(right - left + 1);
        }

        template <typename T>
        T nextf(const T left,const T right){
            return left + nextf(right - left);
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