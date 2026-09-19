#include <bits/stdc++.h>
using namespace std;

class DSU
{

public:
     int n;
     vector<int> parent, rank;

     DSU(int n)
     {
          this->n = n;
          parent.resize(n, 0);
          rank.resize(n, 0);

          for (int i = 0; i < n; i++)
               parent[i] = i;
     }

     void UnionByRank(int a, int b)
     {

          int parA = findParent(a);
          int parB = findParent(b);

          if (parA == parB)
               return;

          if (rank[parA] == rank[parB])
          {
               parent[parB] = parA;
               rank[parA]++;
          }
          else if (rank[parA] > rank[parB])
          {
               parent[parB] = parA;
          }
          else
          {
               parent[parA] = parB;
          }
     }

     int findParent(int x)
     {
          if (parent[x] == x)
          {
               return parent[x];
          }
          return parent[x] = findParent(parent[x]);
     }

     void printParent()
     {
          cout << "Parent : ";
          for (int i = 0; i < n; i++)
          {
               cout << parent[i] << " ";
          }
          cout << endl;
          cout << "Rank : ";
          for (int i = 0; i < n; i++)
          {
               cout << rank[i] << " ";
          }
          cout << endl;
     }
};

struct edge
{
     int u, v, w;
};

class Graph
{
public:
     int V;
     vector<edge> edgelist;

     Graph(int v)
     {
          V = v;
     }

     void addEdge(int u, int v, int w)
     {
          edgelist.push_back({u, v, w});
     }

     void Krushkal()
     {
          sort(edgelist.begin(), edgelist.end(), [](edge &a, edge &b)
               { return a.w < b.w; }); 

          DSU dsu(V);

          int mstwt = 0;

          vector<int> parent(V);

          for (auto &it : edgelist)
          {
               int u = it.u;
               int v = it.v;
               int w = it.w;

               int parU = dsu.findParent(u);
               int parV = dsu.findParent(v);

               if (parU != parV)
               {
                    mstwt += w;
                    cout << u << "->" << v <<" w : " << w <<  endl;
                    dsu.UnionByRank(u, v);
               }
          }
          cout << mstwt << endl;
     }
};

int main()
{
     int v = 9;
     Graph g(v);
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

     g.Krushkal();

     return 0;
}