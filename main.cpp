#include <bits/stdc++.h>
using namespace std;

struct edge
{
    int src, dst, w;
};

void bellmanFord(vector<edge> &edgelist, int v, int src)
{
    vector<int> dist(v, INT_MAX);
    dist[src] = 0;

    // Relax all edges v-1 times
    for (int i = 0; i < v - 1; i++)
    {
        for (auto e : edgelist)
        {
            // FIX 1: Check dist[e.src] instead of dist[src]
            // Also good practice to check != INT_MAX first before doing addition
            if (dist[e.src] != INT_MAX && dist[e.src] + e.w < dist[e.dst])
            {
                dist[e.dst] = dist[e.src] + e.w;
            }
        }
    }

    // Check for negative weight cycles
    for (auto e : edgelist)
    {
        if (dist[e.src] != INT_MAX && dist[e.src] + e.w < dist[e.dst])
        {
            cout << "Negative Cycle!\n";
            return;
        }
    }

    // Print distances
    cout << "Vertex distances from source: " << src << ":\n";
    for (int i = 1; i < v; i++)
    { // Starting loop at 1 since your nodes are 1-indexed
        if (dist[i] == INT_MAX)
            cout << "INF ";
        else
            cout << dist[i] << " ";
    }
    cout << endl;
}

int main()
{
    // 6 is enough since vertices are 1 to 5 (size 6 allows indices 0 to 5)
    int n = 6;
    vector<edge> edgelist = {{1, 2, 6}, {1, 3, 2}, {3, 2, -2}, {2, 4, -1}, {3, 5, 3}, {3, 4, 4}, {4, 5, 3}};

    // FIX 2: Start from node 1, as node 0 doesn't exist in your edge list
    bellmanFord(edgelist, n, 0);

    return 0;
}