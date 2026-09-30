#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

void PrimsMST(int V, int src, map<int, vector<pair<int, int>>> &adjlist)
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
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    key[src] = 0;
    pq.push({0, src});

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
        if (parent[i] != -1)
            cout << "Path : " << parent[i] << "-" << i << " W : " << key[i] << endl;
    cout << endl;
}

void maxST(int V, int src, map<int, vector<pair<int, int>>> &adjlist)
{
    unordered_map<int, bool> visited;
    unordered_map<int, int> parent, key;
    priority_queue<pii> pq;

    for (auto &[vertex, neighbours] : adjlist)
    {
        parent[vertex] = -1;
        visited[vertex] = false;
        key[vertex] = INT_MIN;
    }

    key[src] = 0;
    pq.push({0, src});

    int mstcost = 0;

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if (visited[u])
            continue;

        mstcost += key[u];
        visited[u] = true;

        for (auto &x : adjlist[u])
        {
            int v = x.first;
            int w = x.second;

            if (!visited[v] && w > key[v])
            {
                key[v] = w;
                parent[v] = u;
                pq.push({w, v});
            }
        }
    }

    cout << "MST Cost : " << mstcost << endl;
    cout << "Printing the path : \n";
    for (int i = 0; i < V; i++)
        if (parent[i] != -1)
            cout << "Path : " << parent[i] << "-" << i << " W : " << key[i] << endl;
    cout << endl;
}

map<int, vector<pair<int, int>>> randomgraph(int n, int edges)
{
    map<int, vector<pair<int, int>>> adj;
    set<pair<int, int>> used;

    while ((int)used.size() < edges)
    {
        int u = rand() % n;
        int v = rand() % n;

        // FIX: also check the reverse pair {v,u}, since the graph is now
        // undirected -- otherwise {u,v} and {v,u} could both be picked
        // as if they were different edges, wasting loop iterations.
        if (u == v || used.count({u, v}) || used.count({v, u}))
            continue;

        used.insert({u, v});

        int weight = rand() % 15 ; // range: -5 to 9 (negative weights are fine for MST, not a bug)

        // FIX: original code only inserted adj[u].push_back({v, weight}),
        // making the graph directed. Prim's / maxST treat adjlist[u] as
        // "u's neighbors" in an UNDIRECTED sense, so without this second
        // line, most vertices had no edges pointing back to them and
        // were unreachable from src -- causing near-empty MST output.
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight}); // <-- added: reverse direction
    }
    return adj;
}

int main()
{
    int n;


    cin >> n;

    int edges = n * (n - 1) / 2; 

    map<int, vector<pair<int, int>>> adjlist = randomgraph(n, edges);

   
    PrimsMST(n, 0, adjlist);
    maxST(n, 0, adjlist);
}