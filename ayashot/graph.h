#ifndef AYA_GRAPH_H
#define AYA_GRAPH_H

#include "common.h"
#include "random.h"

typedef std::pair<__aya_u64,__aya_u64> __aya_u64_u64;

std::unordered_map <__aya_u64,bool> __aya_map_id   ;
std::unordered_map <__aya_u64,bool> __aya_map_edges;

template <typename value_type>
struct basic_node{
    __aya_u64 UUID; int num; value_type value;
    basic_node(){}
    basic_node(int _id,int _num):num(_num),UUID(1ull*_id << 32 | _num){
        __aya_map_id[UUID] = _num;
    }
};
template <typename value_type>
struct basic_edge{
    __aya_u64 UUID; int num; value_type value;
    int from, to;
    basic_edge(){}
    basic_edge(int _id, int _num, int _from, int _to){
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
    std::vector<std::vector<int> > X;
    std::size_t node_size, edge_size, edge_size_real;

    __aya_u32 UUID;

    bool direct;
    
public:
    int get_node_size(){return node_size;}
    int get_edge_size(){return edge_size;}
    bool is_direct(){return direct;}

    void set_direct(bool _direct){
        direct = _direct;
    }

    void clear(){node_size = edge_size = 0; V.clear() , E.clear();}

    void add_directed_edge(int from, int to){
        E.push_back(edge_t(UUID, from, to, ++edge_size));
        X[from].push_back(edge_size);
        edge_size_real++;
    }

    void add_indirected_edge(int from, int to){
        E.push_back(edge_t(UUID, from, to, ++edge_size));
        X[from].push_back(edge_size);
        X[to  ].push_back(edge_size);
        edge_size_real+=2;
    }

    int add_edge(int from, int to){
        if(direct) add_directed_edge  (from, to);
        else       add_indirected_edge(from, to);
        return edge_size;
    }

    int add_node(){
        V.push_back(node_t(UUID, ++node_size));
        return node_size;
    }

    void add_nodes(int n){
        __aya_up(0, n-1, i) add_node();
    }

    void chain(int n){
        add_node(); __aya_up(0, n - 1, i){
            int u = add_node(); add_edge(u - 1, u);
        }
    }

    void flower(int n){
        add_node(); __aya_up(0, n - 1, i){
            int u = add_node(); add_edge(u - 1 - i, u);
        }
    }

    void tree_balanced(int n){
        add_node(); __aya_up(0, n - 1, i){
            int u = add_node();
            add_edge(__aya_random.next32(u - i, u), u);
        }
    }

    void tree_sqrted(int n){

    }
};

#endif