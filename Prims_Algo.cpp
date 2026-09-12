#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii; // (weight, vertex)

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

void MST(int src, int V, map<int, vector<pair<int, int>>> &adjlist)
{
     vector<bool> visited(V, false);
     vector<int> key(V, INT_MAX); // best known edge weight into each vertex
     vector<int> parent(V, -1);   // vertex that gives that best edge

     priority_queue<pii, vector<pii>, greater<pii>> pq;

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

               // relax: only update if v is unvisited and this edge beats its current best
               if (!visited[v] && w < key[v])
               {
                    key[v] = w;
                    parent[v] = u;
                    pq.push({w, v});
               }
          }
     }

     cout << "\n\nMinimum Cost from source : " << src << " is -> " << mstCost << endl
          << endl;

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
     Graph g;
     int v = 4;
     g.addEdge(0, 1, 10);
     g.addEdge(0, 2, 15);
     g.addEdge(0, 3, 30);
     g.addEdge(1, 3, 40);
     g.addEdge(3, 2, 50);
     MST(0, v, g.adjlist);

     return 0;
}