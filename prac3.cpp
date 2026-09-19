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

void printPath(int src, int dest, vector<int> &parent)
{
    // dest is unreachable from src
    if (parent[dest] == -1 && dest != src)
    {
        cout << "No path exists\n";
        return;
    }

    vector<int> path;
    for (int v = dest; v != -1; v = parent[v])
        path.push_back(v);

    reverse(path.begin(), path.end()); // walked backward, so reverse to get src -> dest order

    for (int i = 0; i < (int)path.size(); i++)
    {
        cout << path[i];
        if (i != (int)path.size() - 1)
            cout << " -> ";
    }
    cout << endl;
}

void dijkstra(int src, int v, map<int, vector<pair<int, int>>> &adjlist)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    vector<int> dist(v, INT_MAX);
    vector<int> parent(v, -1); // parent[i] = vertex we came from to reach i on the shortest path

    dist[src] = 0;
    pq.push({0, src});

    // pair in adjlist -> v,w
    // priority_queue -> dist(u),u

    while (!pq.empty())
    {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue; // stale entry, skip

        for (auto vertex : adjlist[u])
        {
            int to = vertex.first, w = vertex.second;
            if (dist[to] > dist[u] + w)
            {
                dist[to] = dist[u] + w;
                parent[to] = u; // record: shortest path to `to` currently goes through u
                pq.push({dist[to], to});
            }
        }
    }

    for (int i = 0; i < v; i++)
        cout << "dist[" << i << "] = " << dist[i] << endl;

    cout << "\nPaths from source " << src << ":\n";
    for (int i = 0; i < v; i++)
    {
        cout << src << " to " << i << ": ";
        printPath(src, i, parent);
    }
}

int main()
{
    WeightedGrpah g;

    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 8);
    g.addEdge(1, 4, 6);
    g.addEdge(1, 2, 3);
    g.addEdge(2, 3, 2);
    g.addEdge(3, 4, 10);
   // g.addEdge(4, 3, 2);
    //g.addEdge(4, 5, 5);

    dijkstra(0, 5, g.adjlist);

    return 0;
}