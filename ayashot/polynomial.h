#ifndef AYA_POLY_H
#define AYA_POLY_H

#include"common.h"
#include"random.h"

template <typename value_type = __aya_i32>
class Poly{
	public:
		std::vector <value_type> V;
		std::size_t size(){return V.size();}
		void clear(){	   V.clear();}
		bool empty(){return V.empty();}
		void push_back(value_type w){V.push_back(w);}
		void pop_back (			){V.pop_back ( );}
		void reserve(std::size_t n){V.clear() , V.reserve(n);}
		void reverse(){
			clear(), std::reverse(V.begin(), V.end());
		}
		value_type operator [](int n){
			return V[n];
		}

		void sequence(std::size_t n){
			if(n == 0){clear(); return;}
			reserve(n);
			__aya_up(0, n-1, i)
				push_back(__aya_random.next32(n));
		}
		void sequence(std::size_t n,__aya_i32 left,__aya_i32 right){
			if(n == 0){clear(); return;}
			reserve(n);
			__aya_up(0, n-1, i)
				push_back(__aya_random.next32(left, right));
		}
		void sequence(std::size_t n,__aya_i64 left,__aya_i64 right){
			if(n == 0){clear(); return;}
			reserve(n);
			__aya_up(0, n - 1, i)
				push_back(__aya_random.next64(left, right));
		}
		void shuffle(){
			__aya_dn(V.size() - 1, 0, i)
				swap(V[i], V[__aya_random.next32(i + 1)]);
		}
		void sort(){
			std::sort(V.begin(), V.end());
		}
		void sequence_unique(std::size_t n){
			if(n == 0){clear(); return;}
			__aya_up(0, n - 1, i) push_back(i + 1);
			shuffle();
		}
		void sequence_unique(std::size_t n, __aya_u32 m){
			if(n == 0){clear(); return;}
			if(m < n){
				// log here.
				return ;
			}
			reserve(n);
			std::unordered_map <__aya_u32,__aya_u32> M;
			__aya_up(0, n - 1, i){
				__aya_u32 x = i, y = __aya_random.next32(1u * i, m - 1);
				if(!M.count(x)) M[x] = x;
				if(!M.count(y)) M[y] = y;
				std::swap(M[x], M[y]) , push_back(M[x]);
			}
			for(auto &x : V) printf("::%d\n",x);
		}
		void sequence_unique(std::size_t n, __aya_u64 m){
			if(n == 0){clear(); return;}
			if(m < n){
				// log here.
				return ;
			}
			reserve(n);
			std::unordered_map <__aya_u64,__aya_u64> M;
			__aya_up(0, n - 1, i){
				__aya_u64 x = i, y = __aya_random.next64(1ull * i, m - 1);
				if(!M.count(x)) M[x] = x;
				if(!M.count(y)) M[y] = y;
				std::swap(M[x], M[y]) , push_back(M[x]);
			}
		}
		void sequence_unique(std::size_t n, __aya_i32 left,__aya_i32 right){
			if(n == 0){clear(); return;}
			__aya_u32 m = 1u * right - left + 1;
			if(m < n || left > right){
				// log here.
				return ;
			}
			sequence_unique(n, m);
			__aya_up(0, n - 1, i) V[i] += left - 1;
		}
		void sequence_unique(std::size_t n, __aya_i64 left,__aya_i64 right){
			if(n == 0){clear(); return;}
			__aya_u64 m = 1ull * right - left + 1;
			if(m < n || left > right){
				// log here.
				return ;
			}
			sequence_unique(n, m);
			__aya_up(0, n - 1, i) V[i] += left - 1;
		}
		void permutation(std::size_t n){
			if(n == 0){clear(); return;}
			sequence_unique(n);
		}
		void partition(std::size_t n, __aya_i32 m, __aya_i32 min_value = 0){
			m -= min_value * n;
			if(n == 0 || m < 0){
				//log here.
			}
			sequence_unique(n - 1, n + m - 1);
			push_back(n + m - 1), sort();
			__aya_dn(n - 1, 1, i){
				V[i] = V[i] - V[i - 1] - 1;
			}
			if(min_value)
				up(0, n - 1, i) V[i] += min_value;
		}
		void partition(std::size_t n, __aya_i64 m, __aya_i64 min_value = 0){
			m -= min_value * n;
			if(n == 0 || m < 0){
				//log here.
			}
			sequence_unique(n - 1, 1ull * n + m - 1);
			push_back(n + m - 1), sort();
			__aya_dn(n - 1, 1, i){
				V[i] = V[i] - V[i - 1] - 1;
			}
			if(min_value)
				up(0, n - 1, i) V[i] += min_value;
		}
};

#endif