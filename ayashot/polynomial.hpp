#pragma once

#include"common.hpp"
#include"random.hpp"

template <typename value_type = int32_t>
class Poly{
public:
	std::vector <value_type> V;
	std::size_t size(){
		return V.size();
	}

	void clear(){
		V.clear();
	}

	bool empty(){
		return V.empty();
	}

	void push_back(value_type w){
		V.push_back(w);
	}

	void pop_back(){
		V.pop_back();
	}

	void reserve(std::size_t n){
		V.clear(), V.reserve(n);
	}

	void reverse(){
		clear(), std::reverse(V.begin(), V.end());
	}

	value_type operator [](std::size_t n){
		return V[n];
	}

	void sequence(std::size_t n){
		if (n == 0){ clear(); return; }
		reserve(n);
		for (int32_t i = 0;i < n;++i)
			push_back(__aya_random.next32(n));
	}

	void sequence(std::size_t n, int32_t left, int32_t right){
		if (n == 0){ clear(); return; }
		reserve(n);
		for (int32_t i = 0;i < n;++i)
			push_back(__aya_random.next32(left, right));
	}

	void sequence(std::size_t n, int64_t left, int64_t right){
		if (n == 0){ clear(); return; }
		reserve(n);
		for (int32_t i = 0;i < n;++i)
			push_back(__aya_random.next64(left, right));
	}

	void shuffle(){
		for (int32_t i = V.size() - 1;i > 0;++i)
			swap(V[i], V[__aya_random.next32(i + 1)]);
	}

	void sort(){
		std::sort(V.begin(), V.end());
	}

	void sequence_unique(std::size_t n){
		if (n == 0){ clear(); return; }
		for (int32_t i = 0;i < n;++i) push_back(i + 1);
		shuffle();
	}

	void sequence_unique(std::size_t n, uint32_t m){
		if (n == 0){ clear(); return; }
		if (m < n){
			// log here.
			return;
		}
		reserve(n);
		std::unordered_map <uint32_t, uint32_t> M;
		for (int32_t i = 0;i < n;++i){
			uint32_t x = i, y = __aya_random.next32(1u * i, m - 1);
			if (!M.count(x)) M[x] = x;
			if (!M.count(y)) M[y] = y;
			std::swap(M[x], M[y]), push_back(M[x]);
		}
		for (auto& x : V) printf("::%d\n", x);
	}
	void sequence_unique(std::size_t n, uint64_t m){
		if (n == 0){ clear(); return; }
		if (m < n){
			// log here.
			return;
		}
		reserve(n);
		std::unordered_map <uint64_t, uint64_t> M;
		for (int32_t i = 0;i < n;++i){
			uint64_t x = i, y = __aya_random.next64(1ull * i, m - 1);
			if (!M.count(x)) M[x] = x;
			if (!M.count(y)) M[y] = y;
			std::swap(M[x], M[y]), push_back(M[x]);
		}
	}
	void sequence_unique(std::size_t n, int32_t left, int32_t right){
		if (n == 0){ clear(); return; }
		uint32_t m = 1u * right - left + 1;
		if (m < n || left > right){
			// log here.
			return;
		}
		sequence_unique(n, m);
		for (int32_t i = 0;i < n;++i) V[i] += left - 1;
	}
	void sequence_unique(std::size_t n, int64_t left, int64_t right){
		if (n == 0){ clear(); return; }
		uint64_t m = 1ull * right - left + 1;
		if (m < n || left > right){
			// log here.
			return;
		}
		sequence_unique(n, m);
		for (int32_t i = 0;i < n;++i) V[i] += left - 1;
	}
	void permutation(std::size_t n){
		if (n == 0){ clear(); return; }
		sequence_unique(n);
	}
	void partition(std::size_t n, int32_t m, int32_t min_value = 0){
		m -= min_value * n;
		if (n == 0 || m < 0){
			//log here.
		}
		sequence_unique(n - 1, n + m - 1);
		push_back(n + m - 1), sort();
		for (int32_t i = n - 1;i > 0;--i){
			V[i] = V[i] - V[i - 1] - 1;
		}
		if (min_value)
			for (int32_t i = 0;i < n;++i) V[i] += min_value;
	}
	void partition(std::size_t n, int64_t m, int64_t min_value = 0){
		m -= min_value * n;
		if (n == 0 || m < 0){
			//log here.
		}
		sequence_unique(n - 1, 1ull * n + m - 1);
		push_back(n + m - 1), sort();
		for(int32_t i = n - 1;i > 0;--i){
			V[i] = V[i] - V[i - 1] - 1;
		}
		if (min_value)
			for (int32_t i = 0;i < n;++i) V[i] += min_value;
	}
}; 