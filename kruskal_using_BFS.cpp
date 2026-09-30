#include <bits/stdc++.h>
using namespace std;

struct Edge
{
     int u, v, w;
};

class Graph
{
public:
     int V;
     vector<Edge> edges;

     Graph(int v) : V(v) {}

     void addEdge(int u, int v, int w)
     {
          edges.push_back({u, v, w});
     }

     // BFS on the partial MST: is dest reachable from src?
     bool isConnected(int src, int dest, vector<vector<int>> &mstAdj)
     {
          vector<bool> visited(V, false);
          queue<int> q;

          visited[src] = true;
          q.push(src);

          while (!q.empty())
          {
               int node = q.front();
               q.pop();

               if (node == dest)
                    return true;

               for (int nb : mstAdj[node])
               {
                    if (!visited[nb])
                    {
                         visited[nb] = true;
                         q.push(nb);
                    }
               }
          }
          return false;
     }

     void kruskalMST()
     {
          stable_sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b)
                      { return a.w < b.w; });

          vector<vector<int>> mstAdj(V); // adjacency list of the MST built so far
          int mstWeight = 0;
          int count = 0;

          cout << "Edges in MST:\n";
          for (auto &e : edges)
          {
               // if u and v are already connected in the partial MST, the edge makes a cycle
               if (!isConnected(e.u, e.v, mstAdj))
               {
                    mstAdj[e.u].push_back(e.v);
                    mstAdj[e.v].push_back(e.u); // undirected
                    mstWeight += e.w;
                    count++;
                    cout << e.u << " -> " << e.v << " (weight " << e.w << ")\n";

                    if (count == V - 1)
                         break; // tree complete
               }
          }

          cout << "Total MST weight: " << mstWeight << endl;
     }
};

int main()
{
     Graph g(9);

     g.addEdge(0, 1, 4);
     g.addEdge(0, 7, 8);
     g.addEdge(1, 2, 8);
     g.addEdge(1, 7, 11);
     g.addEdge(2, 3, 7);
     g.addEdge(2, 8, 2);
     g.addEdge(2, 5, 4);
     g.addEdge(3, 4, 9);
     g.addEdge(3, 5, 14);
     g.addEdge(4, 5, 10);
     g.addEdge(5, 6, 2);
     g.addEdge(6, 7, 1);
     g.addEdge(6, 8, 6);
     g.addEdge(7, 8, 7);

     g.kruskalMST();

     return 0;
}