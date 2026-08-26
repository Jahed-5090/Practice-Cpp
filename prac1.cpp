#include <bits/stdc++.h>
using namespace std;

struct edge
{
    int u, v, w;
};

class weightedGraph
{
public:
    vector<edge> edgelist;

    void addEdge(int u, int v, int w)
    {
        this->edgelist.push_back({u, v, w});
    }

    void printEdges()
    {
        cout << "Edge List (u -> v : weight)\n";
        for (const auto &e : edgelist)
        {
            cout << e.u << " -> " << e.v << " : " << e.w << "\n";
        }
    }
};

void Dijkstra(const vector<edge> &edgelist, int src, int v)
{
    // adj[u] holds the (neighbour, weight) pairs of the edges leaving u
    vector<vector<pair<int, int>>> adj(v);
    for (const auto &e : edgelist)
        adj[e.u].push_back({e.v, e.w});

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    vector<int> dist(v, INT_MAX);

    dist[src] = 0;

    pq.push({dist[src], src});

    while (!pq.empty())
    {
        auto [d, u] = pq.top();
        pq.pop();

        // stale entry: u was already settled through a shorter path
        if (d > dist[u])
            continue;

        // relax only u's own neighbours; d is finite, so d + w cannot overflow
        for (const auto &[to, w] : adj[u])
        {
            if (d + w < dist[to])
            {
                dist[to] = d + w;
                pq.push({dist[to], to});
            }
        }
    }

    cout << "Distance of vertices from source: " << src << endl;

    for (int i = 0; i < v; i++)
    {
        if (dist[i] == INT_MAX)
            cout << i << " : INF" << endl;
        else
            cout << i << " : " << dist[i] << endl;
    }
    cout << endl;
}
 
void bellmanFord(vector<edge> edgelist,int src,int v) {


    vector<int> dist(v,INT_MAX) ; 
    
    dist[src] = 0 ; 

    for(int i=0;i<v-1;i++) {
        for(auto &e : edgelist) {
            if(dist[e.u] != INT_MAX && dist[e.v]>dist[e.u]+e.w){
                dist[e.v] = dist[e.u]+e.w ; 
            }
        }
    } 

    for(int i=0;i<v-1;i++) {
        for(auto &e : edgelist) {
            if(dist[e.u] != INT_MAX && dist[e.v]>dist[e.u]+e.w){
                dist[e.v] = dist[e.u]+e.w ; 
            }
        }
    } 

    cout << "Distance of vertices from source: " << src << endl ;

    for(int i=0;i<dist.size();i++) {
       cout << dist[i] << endl ; 
    } cout << endl ;

}

int main()
{

    weightedGraph g ;
    g.addEdge(1,2, 6);
    g.addEdge(1, 3, 2);
    g.addEdge(3, 2, -2);
    g.addEdge(2, 4, -1);
    g.addEdge(3, 5, 3);
    g.addEdge(3, 4, 4);
    g.addEdge(4, 5, 3);

    // vertices are labelled 1..5, so size the arrays for 6 slots (index 0 unused).
    // NOTE: this graph has negative weights, which Dijkstra does not support --
    // use bellmanFord for it, or make every weight non-negative.
    Dijkstra(g.edgelist, 1, 6);


    return 0;
}