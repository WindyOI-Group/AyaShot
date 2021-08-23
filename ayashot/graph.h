#pragma once

#include "common.h"
#include "random.h"

typedef std::pair<uint64_t, uint64_t> __aya_u64_u64;

std::unordered_map <uint64_t, bool> __aya_map_id;
std::unordered_map <uint64_t, bool> __aya_map_edges;

template <typename value_type>
struct basic_node{
    uint64_t UUID; int32_t num; value_type value;
    basic_node(){}
    basic_node(int32_t _id, int32_t _num):num(_num), UUID(1ull * _id << 32 | _num){
        __aya_map_id[UUID] = _num;
    }
};
template <typename value_type>
struct basic_edge{
    uint64_t UUID; int32_t num; value_type value;
    int32_t from, to;
    basic_edge(){}
    basic_edge(int32_t _id, int32_t _num, int32_t _from, int32_t _to){
        from = _from, to = _to, num = _num;
        __aya_map_id[UUID] = _num;
    }
};

template <typename value_type>
class graph_t{
private:
    using node_t = basic_node<value_type>;
    using edge_t = basic_edge<value_type>;
    std::vector<node_t> V;
    std::vector<edge_t> E;
    std::vector<std::vector<int32_t> > X;
    std::size_t node_size, edge_size, edge_size_real;

    uint32_t UUID;

    bool direct;

public:
    int32_t get_node_size(){ return node_size; }
    int32_t get_edge_size(){ return edge_size; }
    bool is_direct(){ return direct; }

    void set_direct(bool _direct){
        direct = _direct;
    }

    void clear(){ node_size = edge_size = 0; V.clear(), E.clear(); }

    void add_directed_edge(int32_t from, int32_t to){
        E.push_back(edge_t(UUID, from, to, ++edge_size));
        X[from].push_back(edge_size);
        edge_size_real++;
    }

    void add_indirected_edge(int32_t from, int32_t to){
        E.push_back(edge_t(UUID, from, to, ++edge_size));
        X[from].push_back(edge_size);
        X[to].push_back(edge_size);
        edge_size_real += 2;
    }

    int32_t add_edge(int32_t from, int32_t to){
        if (direct) add_directed_edge(from, to);
        else       add_indirected_edge(from, to);
        return edge_size;
    }

    int32_t add_node(){
        V.push_back(node_t(UUID, ++node_size));
        return node_size;
    }

    void add_nodes(size_t n){
        for(int32_t i = 0;i < n;++i) add_node();
    }

    void chain(int32_t n){
        add_node(); for(int32_t i = 0;i < n;++i){
            int32_t u = add_node(); add_edge(u - 1, u);
        }
    }

    void flower(int32_t n){
        add_node(); for(int32_t i = 0;i < n;++i){
            int32_t u = add_node(); add_edge(u - 1 - i, u);
        }
    }

    void tree_balanced(int32_t n){
        add_node(); for(int32_t i = 0;i < n;++i){
            int32_t u = add_node();
            add_edge(__aya_random.next32(u - i, u), u);
        }
    }

    void tree_sqrted(int32_t n){

    }
}; 