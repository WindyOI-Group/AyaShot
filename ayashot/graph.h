#ifndef AYA_GRAPH_H
#define AYA_GRAPH_H

std::unordered_map <     u64          ,bool         > __aya_map_id   ;
std::unordered_map <std::pair<u64,u64>,bool,HashPair> __aya_map_edges;
struct Node{
    u64 UUID; int id; std::vector<int> value;
    Node():UUID(__aya_random.next64()){}
    Node(int _id):id(_id),UUID(__aya_random.next64()){
        __aya_map_id[UUID] = _id;
    }
};
struct Edge{
    u64 UUID; std::vector<int> value;
    int from , to ,id;
    Edge():UUID(__aya_random.next64()){}
    Edge(int _id,int _from,int _to):
        id(_id),from(_from),to(_to),UUID(__aya_random.next64()){
        __aya_map_id[UUID] = _id;
        __aya_map_edges[std::make_pair(_from,_to)] = true;
    }
};

class Graph{
    private:
        std::vector<Node> V;
        std::vector<Edge> E, F;
        std::size_t node_size, edge_size;
    public:
        int get_node_size(){return node_size;}
        int get_edge_size(){return edge_size;}
        void clear(){node_size = edge_size = 0; V.clear() , E.clear();}

        void tree_nodes(int n){
            int start = node_size +1;
            node_size += n;
            up(0,n - 1,i){
                V.push_back(Node(i + 1));
            }
        }

        void chain(int n , bool directed = true){
            int start_nodes = node_size + 1;
            int start_edges = edge_size + 1;
            tree_nodes(n), edge_size += n - 1;
            up(0,n - 1,i){
                E.push_back(Edge(start_edges + i,
                    start_nodes + i,start_nodes + i + 1));
                F.push_back(Edge(start_edges + i,
                    start_nodes + i + 1,start_nodes + i));
            }
            if(!directed){
                edge_size += n - 1 ,start_edges += n - 1;
                up(0,n - 1,i){
                    E.push_back(Edge(start_edges + i,
                        start_nodes + i + 1,start_nodes + i));
                    F.push_back(Edge(start_edges + i,
                        start_nodes + i,start_nodes + i + 1));
                }
            }
        }

        void tree_balanced(int n , bool directed = true){
            int start_nodes = node_size + 1;
            int start_edges = edge_size + 1;
            tree_nodes(n),edge_size += n - 1;
            if(!directed) edge_size += n - 1;
            up(1,n - 1,i){
                E.push_back(Edge(start_edges + i,
                    start_nodes + i,start_nodes + __aya_random.next32(i) - 1));
            }
        }

        void tree_sqrted(int n){

        }
};

#endif