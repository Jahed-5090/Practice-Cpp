#include <bits/stdc++.h>
using namespace std;

struct Edge
{
     int u, v, w;
};

class DSU
{
public:
     vector<int> parent, rank;

     DSU(int n)
     {
          parent.resize(n);
          rank.assign(n, 0);

          for (int i = 0; i < n; i++)
               parent[i] = i;
     }

     int findParent(int x)
     {
          if (parent[x] == x)
               return x;

          return parent[x] = findParent(parent[x]);
     }

     void unionByRank(int a, int b)
     {
          int pa = findParent(a);
          int pb = findParent(b);

          if (pa == pb)
               return;

          if (rank[pa] < rank[pb])
               swap(pa, pb);

          parent[pb] = pa;

          if (rank[pa] == rank[pb])
               rank[pa]++;
     }
};

class Graph
{
public:
     int V;
     vector<Edge> edges;

     Graph(int v)
     {
          V = v;
     }

     void addEdge(int u, int v, int w)
     {
          edges.push_back({u, v, w});
     }

     void kruskalMST()
     {
          sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b)
               { return a.w < b.w; });

          DSU dsu(V);
          int mstWeight = 0;

          cout << "Edges in MST:\n";
          for (auto &edge : edges)
          {
               int u = edge.u;
               int v = edge.v;
               int w = edge.w;

               if (dsu.findParent(u) != dsu.findParent(v))
               {
                    dsu.unionByRank(u, v);
                    mstWeight += w;
                    cout << u << " -> " << v << " (weight " << w << ")\n";
               }
          }

          cout << "Total MST weight: " << mstWeight << endl;
     }
};

int main()
{
     int V = 9;
     Graph g(V);

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