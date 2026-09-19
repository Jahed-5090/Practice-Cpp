#include <bits/stdc++.h>
using namespace std;

/*
Dijkstra's Algorithm -> Adjacency List way better than edgelist .
defualt priority_queue  in cpp is max_heap.
normal max priority_queue : priority_queue<data_type> pq ;
min priority_queue :        priority_queue<int,vector<int>,greater<int>> pq
*/

class WeightedGrpah
{
public:
    map<int, vector<pair<int, int>>> adjlist;

    void addEdge(int u, int v, int w, bool directed = false)
    {
        adjlist[u].push_back({v, w});
        if (!directed)
            adjlist[v].push_back({u, w});
    }

    void print()
    {
        cout << endl;
        for (auto [vertex, neighbours] : adjlist)
        {
            cout << vertex << "->" << endl;
            for (auto [neighbour, w] : neighbours)
            {
                cout << "( " << neighbour << "," << w << " )" << endl;
            }
            cout << endl;
        }
    }
};

void dijkstra(int src, int v, map<int, vector<pair<int, int>>> &adjlist)
{

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    vector<int> dist(v, INT_MAX);
    vector<int> par(v, -1);

    dist[src] = 0;

    pq.push({0, src});

    // pair in adjlist -> v,w
    // priority_queue -> dist(u),u

    while (!pq.empty())
    {

        int u = pq.top().second;
        pq.pop();

        for (auto vertex : adjlist[u])
        {
            if (dist[vertex.first] > dist[u] + vertex.second)
            {
                dist[vertex.first] = dist[u] + vertex.second;
                pq.push({dist[vertex.first], vertex.first});
                par[vertex.first] = u;
            }
        }
    }

    for (int i = 0; i < v; i++)
        cout << dist[i] << " ";
    cout << endl;
   
    for (int i = 0; i < v; i++)
        cout << par[i] << " ";
    cout << endl;
}

int main()
{
    WeightedGrpah g;

    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 7);
    g.addEdge(2, 4, 3);
    g.addEdge(3, 5, 1);
    g.addEdge(4, 3, 2);
    g.addEdge(4, 5, 5);

    dijkstra(0, 6, g.adjlist);

    return 0;
}
