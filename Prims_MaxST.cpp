#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii; // (weight, vertex)

void maxSpanningTree(int src, int V, map<int, vector<pair<int, int>>> &adjlist)
{
    vector<bool> visited(V, false);
    vector<int> key(V, INT_MIN); // CHANGED: start at -infinity, since we now want the MAXIMUM edge
    vector<int> parent(V, -1);

    priority_queue<pii> pq; // CHANGED: default priority_queue is already a max-heap, so drop the greater<> comparator

    key[src] = 0;
    pq.push({0, src});

    int mstCost = 0;

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        if (visited[u])
            continue;

        visited[u] = true;
        mstCost += key[u];

        for (auto edge : adjlist[u])
        {
            int v = edge.first;
            int w = edge.second;

            // CHANGED: w > key[v] instead of w < key[v] -- we want the LARGEST edge into v
            if (!visited[v] && w > key[v])
            {
                key[v] = w;
                parent[v] = u;
                pq.push({w, v});
            }
        }
    }

    cout << "\n\nMaximum Cost from source: " << src << " is -> " << mstCost << endl << endl;

    cout << "Edge \tWeight\n";
    for (int i = 0; i < V; i++)
    {
        if (parent[i] != -1)
            cout << parent[i] << " - " << i << " \t" << key[i] << " \n";
    }
    cout << endl;
}

int main()
{
    map<int, vector<pair<int,int>>> adjlist;
    auto addEdge = [&](int u, int v, int w) {
        adjlist[u].push_back({v, w});
        adjlist[v].push_back({u, w});
    };

    int v = 4;
    addEdge(0, 1, 10);
    addEdge(0, 2, 15);
    addEdge(0, 3, 30);
    addEdge(1, 3, 40);
    addEdge(3, 2, 50);

    maxSpanningTree(2, v, adjlist);

    return 0;
}