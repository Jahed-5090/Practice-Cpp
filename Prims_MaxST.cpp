#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

class Graph
{
public:
    int V;
    unordered_map<int, vector<pair<int, int>>> adjlist;

    Graph(int v) : V(v) {}

    void addEdge(int u, int v, int w)
    {
        adjlist[u].push_back({v, w});
        adjlist[v].push_back({u, w});
    }

    void maxST(int src)
    {
        unordered_map<int, bool> visited;
        unordered_map<int, int> parent, key;

        priority_queue<pii> pq;

        for (auto &[vertex, weight] : adjlist)
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
        {
            if (parent[i] != -1)
            {
                cout << "Path : " << parent[i] << "-" << i << " W : " << key[i] << endl;
            }
        }
        cout << endl;
    }
};

int main()
{

    int v = 4;
    Graph g(v);

    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 15);
    g.addEdge(0, 3, 30);
    g.addEdge(1, 3, 40);
    g.addEdge(3, 2, 50);
    g.maxST(2);

    return 0;
}
