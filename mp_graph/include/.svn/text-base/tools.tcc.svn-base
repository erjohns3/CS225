/**
 * @file tools.tcc
 * Definition of utility functions on graphs.
 */

#include <limits>
#include <queue>

#include "tools.h"
#include "dsets.h"

namespace cs225
{
namespace tools
{

template <class Graph>
typename Graph::edge_weight_type min_weight_edge(Graph& g)
{
    using weight_t = typename Graph::edge_weight_type;
    weight_t min = std::numeric_limits<weight_t>::max();
    edge min_edge{g.start_vertex(), g.start_vertex()};

    vertex_map<vertex_state> vtx_mark;
    for (const auto& v : g.vertices())
        vtx_mark[v] = vertex_state::UNEXPLORED;

    /// @todo your code here

    for (const auto& v : g.edges())
        g.edge_label(v, edge_state::UNEXPLORED);

    std::queue<vertex> q;
    vertex u = g.start_vertex();
    q.push(u);
    vtx_mark[u] = vertex_state::VISITED;

    while(!q.empty()){
        u = q.front();
        q.pop();
        for(const auto& v : g.adjacent(u)){
            if(vtx_mark[v] == vertex_state::UNEXPLORED){
                q.push(v);
                vtx_mark[v] = vertex_state::VISITED;
            }
            if(g.edge_weight(u, v) < min){
                min = g.edge_weight(u, v);
                edge tmp_edge{u, v};
                min_edge = tmp_edge;
            }
        }
    }
    g.edge_label(min_edge, edge_state::MIN);
    return min;
}

template <class Graph>
uint64_t shortest_path_length(Graph& g, vertex start, vertex end)
{
    /// @todo your code here

    vertex_map<vertex_state> vtx_mark;
    for (const auto& v : g.vertices())
        vtx_mark[v] = vertex_state::UNEXPLORED;

    for (const auto& v : g.edges())
        g.edge_label(v, edge_state::UNEXPLORED);


    vertex_map<vertex> parent;

    std::queue<vertex> q;
    vertex u = start;
    q.push(u);
    vtx_mark[u] = vertex_state::VISITED;

    while(!q.empty() && q.front() != end){
        u = q.front();
        q.pop();
        for(const auto& v : g.adjacent(u)){
            if(vtx_mark[v] == vertex_state::UNEXPLORED){
                parent[v] = u;
                q.push(v);
                vtx_mark[v] = vertex_state::VISITED;
            }
        }
    }

    u = end;
    int num = 0;

    while(u != start){
        g.edge_label(u, parent[u], edge_state::MINPATH);
        u = parent[u];
        num++;
    }

    return num;

}

template <class Graph>
void mark_mst(Graph& g)
{
    for (const auto& e : minimum_spanning_tree(g))
        g.edge_label(e, edge_state::MST);
}

template <class Graph>
edge_set minimum_spanning_tree(const Graph& g)
{
    // sort all the edges
    struct weighted_edge
    {
        edge arc; 
        typename Graph::edge_weight_type weight;
    };
    std::vector<weighted_edge> pq;
    for (const auto& e : g.edges())
        pq.push_back({e, g.edge_weight(e)});
    std::sort(pq.begin(), pq.end(), [&](const weighted_edge& e1, const weighted_edge& e2){
        return e1.weight < e2.weight;
    });

    /// @todo your code here

    int num = 0;
    edge_set set;
    dsets sets;

    vertex_map<vertex_state> vtx_mark;
    for (const auto& v : g.vertices())
        num++;

    sets.add_elements(num);

    for(size_t i=0; i<pq.size(); i++){
        if(num<1)
            break;
        if(sets.find(pq[i].arc.source) != sets.find(pq[i].arc.dest)){
            sets.merge(pq[i].arc.source, pq[i].arc.dest);
            num--;
            set.insert(pq[i].arc);
        }
    }
    return set;
}
}
}
