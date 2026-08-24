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

void Dijkstra(vector<edge> edgelist, int src, int v)
{

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    vector<int> dist(v, INT_MAX);

    dist[src] = 0;

    pq.push({dist[src], src});

    while (!pq.empty())
    {
        auto edge = pq.top();
        pq.pop();
        for (auto &e : edgelist)
        {
            if (dist[e.v] > dist[e.u] + e.w)
            {
                dist[e.v] = dist[e.u] + e.w;
                pq.push({dist[e.v], e.v});
            }
        }
    }
    for (int i = 0; i < v; i++)
        cout << dist[i] << " ";
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

    bellmanFord(g.edgelist,1,4) ;
    

    return 0;
}