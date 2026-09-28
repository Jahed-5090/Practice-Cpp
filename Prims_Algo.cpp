#include <bits/stdc++.h>
using namespace std;

class Graph
{
public:
    map<int, vector<pair<int, int>>> adjlist;

    void addEdge(int u, int v, int w)
    {
        adjlist[u].push_back({v, w});
        adjlist[v].push_back({u, w});
    }
};

void MST(int V, int src, map<int, vector<pair<int, int>>> &adjlist)
{

    unordered_map<int, int> parent;
    unordered_map<int, int> key;
    unordered_map<int, bool> visited;

    for (auto &[vertex, neighbours] : adjlist)
    {
        key[vertex] = INT_MAX;
        parent[vertex] = -1;
        visited[vertex] = false;
    }

    int mstcost = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    key[src] = 0;

    pq.push({0, src}); // weight, vertex

    while (!pq.empty())
    {

        int u = pq.top().second;
        pq.pop();

        if (visited[u])
            continue;

        visited[u] = true;
        mstcost += key[u];

        for (auto x : adjlist[u])
        {
            int v = x.first;
            int w = x.second;

            if (!visited[v] && w < key[v])
            {
                pq.push({w, v});
                parent[v] = u;
                key[v] = w;
            }
        }
    }
    cout << "MST Cost : " << mstcost << endl;

    cout << "Printing the path : \n";

    for (int i = 0; i < V; i++)
    {
        if (parent[i] != -1)
        {
            cout << "Path : " << parent[i] << "-" << i << " W : " << key[i] << endl;
        }
    }
    cout << endl;
}

int main()
{

    Graph g;
    int v = 4;
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 15);
    g.addEdge(0, 3, 30);
    g.addEdge(1, 3, 40);
    g.addEdge(3, 2, 50);
    MST(v, 0, g.adjlist);

    return 0;
}