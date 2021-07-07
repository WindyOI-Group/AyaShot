#ifndef AYA_COMMON_H
#define AYA_COMMON_H

#define i64 __aya_i64
#define u32 __aya_u32
#define u64 __aya_u64
#define f32 __aya_f32
#define f64 __aya_f64
#define f80 __aya_f80

typedef long long          __aya_i64;
typedef unsigned int       __aya_u32;
typedef unsigned long long __aya_u64;
typedef float              __aya_f32;
typedef double             __aya_f64;
typedef long double        __aya_f80;

#define up(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define dn(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)

std::hash <u64> __aya_hash_ullong;

std::hash <std::string> __aya_hash_string;

struct HashPair{
    std::size_t operator() (const std::pair<u64,u64> &p) const{
        return __aya_hash_ullong(p.first)^__aya_hash_ullong(p.second);
    }
};


#endif