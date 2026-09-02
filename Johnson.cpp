#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

struct edge
{
     int u, v, w;
};

class weightedGraph
{
public:
     vector<edge> edgelist;

     void addEdge(int u, int v, int w)
     {
          edgelist.push_back({u, v, w});
     }
};

vector<int> Dijkstra(int V, int src, map<int, vector<pair<int, int>>> adjlist)
{

     vector<int> dist(V, INF);
     dist[src] = 0;

     priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

     pq.push({dist[src], src});

     while (!pq.empty())
     {
          int u = pq.top().second;
          pq.pop();
          for (auto &e : adjlist[u])
          {
               int v = e.first;
               int w = e.second;
               if (dist[u] != INF && dist[v] > dist[u] + w)
               {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
               }
          }
     }

     return dist;
}

vector<int> BellmanFord(int V, vector<edge> &edgelist, bool &hasCycle)
{

     vector<int> h(V + 1, INF);
     h[V] = 0;

     vector<edge> new_edgelist = edgelist;

     for (int i = 0; i < V; i++)
     {
          new_edgelist.push_back({V, i, 0});
     }

     for (int i = 0; i < V; i++)
     {
          for (auto &e : new_edgelist)
          {
               int u = e.u, v = e.v, w = e.w;
               if (h[u] != INF && h[u] + w < h[v])
               {
                    h[v] = h[u] + w;
               }
          }
     }
     hasCycle = false;

     for (auto &e : edgelist)
     {
          int u = e.u, v = e.v, w = e.w;
          if (h[u] != INF && h[u] + w < h[v])
          {
               hasCycle = true;
               break;
          }
     }

     h.pop_back();
     return h;
}

void Johnson(int V, vector<edge> &edgelist)
{

     bool hasCycle;

     vector<int> h = BellmanFord(V, edgelist, hasCycle);

     if (hasCycle)
     {
          cout << "Negative Weight Cycyle Detected!\n";
          return;
     }

     map<int, vector<pair<int, int>>> adjlist;

     for (auto &e : edgelist)
     {
          int u = e.u, v = e.v, w = e.w;
          adjlist[u].push_back({v, w + h[u] - h[v]}); // rewighted edges in the new adjlist
     }

     vector<vector<int>> resultMat(V, vector<int>(V));

     for (int s = 0; s < V; s++)
     {
          vector<int> dprime = Dijkstra(V, s, adjlist);
          for (int v = 0; v < V; v++)
          {
               if (dprime[v] == INF)
               {
                    resultMat[s][v] = INF;
               }
               else
               {
                    resultMat[s][v] = dprime[v] + h[v] - h[s];
               }
          }
     }

     cout << "Shortest Distance Matrix:\n";
     for (int i = 0; i < V; i++)
     {
          for (int j = 0; j < V; j++)
          {
               if (resultMat[i][j] >= INF / 2)
                    cout << setw(7) << "INF";
               else
                    cout << setw(7) << resultMat[i][j];
          }
          cout << endl;
     }
}

int main()
{

     weightedGraph G;

     G.addEdge(0, 1, 2);
     G.addEdge(0, 2, 4);

     G.addEdge(1, 2, 1);
     G.addEdge(1, 2, 7);

     G.addEdge(2, 4, 3);
     G.addEdge(3, 5, 1);

     G.addEdge(4, 3, 2);
     G.addEdge(4, 5, 5);

     Johnson(6, G.edgelist);

     return 0;
}