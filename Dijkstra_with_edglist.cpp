#include <bits/stdc++.h>
using namespace std;

struct Edge
{
     int u, v, w;
};

class WeightedGraphEdgeList
{
     int V;
     vector<Edge> edges;

public:
     WeightedGraphEdgeList(int V) : V(V) {}

     void addEdge(int u, int v, int w, bool directed = false)
     {
          edges.push_back({u, v, w});
          if (!directed)
               edges.push_back({v, u, w});
     }

     void print()
     {
          for (auto &e : edges)
               cout << e.u << " -- " << e.v << " (w=" << e.w << ")\n";
     }

     void dijkstra(int src)
     {
          vector<int> dist(V, INT_MAX);
          dist[src] = 0;

          priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
          pq.push({0, src});

          while (!pq.empty())
          {
               auto [d, u] = pq.top();
               pq.pop();

               if (d > dist[u])
                    continue; // stale entry, skip

               // scan the WHOLE edge list to find u's neighbors -- O(E) per vertex
               for (auto &e : edges)
               {
                    if (e.u == u)
                    {
                         int to = e.v, w = e.w;
                         if (dist[u] + w < dist[to])
                         {
                              dist[to] = dist[u] + w;
                              pq.push({dist[to], to});
                         }
                    }
               }
          }

          for (int i = 0; i < V; i++)
               cout << dist[i] << " ";
          cout << endl;
     }
};

int main()
{
     WeightedGraphEdgeList g(5);
     g.addEdge(0, 1, 4);
     g.addEdge(0, 4, 1);
     g.addEdge(1, 2, 3);
     g.addEdge(1, 3, 2);
     g.addEdge(1, 4, 5);
     g.addEdge(2, 3, 7);
     g.addEdge(3, 4, 6);

     g.print();
     cout << "\nShortest distances from 0:\n";
     g.dijkstra(0);

     return 0;
}