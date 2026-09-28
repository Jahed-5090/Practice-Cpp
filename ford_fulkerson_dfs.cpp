#include <bits/stdc++.h>
using namespace std;

int V = 4;

bool dfs(vector<vector<int>> &rgraph, int u, int sink, vector<bool> &visited, vector<int> &parent)
{
     if (u == sink)
          return true;

     visited[u] = true;

     for (int v = 1; v <= V; v++)
     {
          if (rgraph[u][v] > 0 && !visited[v])
          {
               parent[v] = u;

               if (dfs(rgraph, v, sink, visited, parent))
                    return true;
          }
     }

     return false;
}

int maxFlow(vector<vector<int>> &edgelist)
{

     vector<vector<int>> graph(V + 1, vector<int>(V + 1, 0));
     vector<int> parent(V + 1);

     int src = 1;
     int sink = V;

     for (auto &edge : edgelist)
     {

          int u = edge[0];
          int v = edge[1];
          int cap = edge[2];

          graph[u][v] = cap;
     }

     int maxflow = 0;

     vector<vector<int>> rgraph = graph;

     while (true)
     {
          vector<bool> visited(V + 1, false);
          fill(parent.begin(), parent.end(), -1);

          if (!dfs(rgraph, src, sink, visited, parent))
               break;

          int pathflow = INT_MAX;

          for (int v = sink; v != src; v = parent[v])
          {
               int u = parent[v];
               pathflow = min(pathflow, rgraph[u][v]);
          }
          for (int v = sink; v != src; v = parent[v])
          {
               int u = parent[v];
               rgraph[u][v] -= pathflow;
               rgraph[v][u] += pathflow;
          }

          maxflow += pathflow;
     }

     return maxflow;
}

int main()
{

     vector<vector<int>> edges = {
         {1, 2, 10},
         {1, 3, 10},
         {2, 3, 10},
         {2, 4, 10},
         {3, 4, 10}};

     cout << maxFlow(edges) << endl;

     return 0;
}