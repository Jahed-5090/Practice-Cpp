// Dijkstra - Adjacency Matrix


#include <bits/stdc++.h>
using namespace std;

const int INF = INT_MAX;

class weightedGraph
{
public:
     int V;

     vector<vector<int>> adjmatrix;

     weightedGraph(int x) : V(x)
     {
          adjmatrix.assign(V, vector<int>(V, 0));
     }

     void addEdge(int u, int v, int w)
     {
          adjmatrix[u][v] = w;
     }

     void print()
     {
     }
};

void Dijkstra(int V,
              int src, vector<vector<int>> &adjMatrix)
{

     vector<int> dist(V, INF);

     priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

     dist[src] = 0;
     pq.push({dist[src], src});

     while (!pq.empty())
     {
          int u = pq.top().second;
          pq.pop();
          for (int v = 0; v < V; v++)
          {
               int w = adjMatrix[u][v];
               if (w != 0 && dist[u] != INF && dist[u] + w < dist[v])
               {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
               }
          }
     }
     cout << "\nPrinting distance from source: " << src << endl;
     for (int i = 0; i < V; i++)
     {
          if (dist[i] == INF)
               cout << "INF ";
          else
               cout << dist[i] << " ";
     }
     cout << endl;
}

int main()
{

     int V = 6;
     weightedGraph G(V);

     G.addEdge(0, 1, 2);
     G.addEdge(0, 2, 4);

     G.addEdge(1, 2, 1);

     G.addEdge(2, 4, 3);
     G.addEdge(3, 5, 1);

     G.addEdge(4, 3, 2);
     G.addEdge(4, 5, 5);

     Dijkstra(V, 0, G.adjmatrix);

     return 0;
} 



// Dijkstra-EdgeList

#include <bits/stdc++.h>
using namespace std ; 

const int INF = INT_MAX ;

struct edge{
     int u,v,w ;
} ;

class WeightedGraph{
public:  
 vector<edge> edgeList ; 

 void addEdge(int u,int v,int w,bool directed=false) {
     edgeList.push_back({u,v,w}) ;
 } 

  void printGraph() {
     for(auto &edge: edgeList) {
          cout << "src: " << edge.u << " dest: "<< edge.v << " weight: " << edge.w << endl ;
     }
  } 

};


void Dijkstra(int V,int src,vector<edge> &edgeList){

     vector<int>dist(V,INF) ; 

     priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq ; 

     dist[src]=0 ;
     pq.push({dist[src],src}) ; 

     while(!pq.empty()) {
          int v = pq.top().second ;
          pq.pop() ; 

          for(auto &edge:edgeList) {
               if(edge.u==v) { 
                    int u = edge.u ;
                    int v = edge.v;
                    int w = edge.w ;
                    if(dist[u]!=INF && dist[u]+w<dist[v]) {
                         dist[v]=dist[u]+w ; 
                         pq.push({dist[v],v}) ;
                    }
               }
          }
     }
     cout << "\nprinting distance from source : " << src << endl;

     for (int i = 0; i < V; i++)
     {
          cout << dist[i] << " ";
     }
     cout << endl;


}

int main()
{

     WeightedGraph G;

     G.addEdge(0, 1, 2);
     G.addEdge(0, 2, 4);

     G.addEdge(1, 2, 1);
     G.addEdge(1, 2, 7);

     G.addEdge(2, 4, 3);
     G.addEdge(3, 5, 1);

     G.addEdge(4, 3, 2);
     G.addEdge(4, 5, 5);

     Dijkstra(6, 0, G.edgeList);

     return 0;
}



// Dijkstra-AdjacencyList

#include <bits/stdc++.h>
using namespace std;

const int INF = INT_MAX;

class WeightedGraph
{
public:
     map<int, vector<pair<int, int>>> adjlist;

     void addEdge(int u, int v, int w, bool directed = true)
     {
          adjlist[u].push_back({v, w});
          if (!directed)
          {
               adjlist[v].push_back({u, w});
          }
     }

     void print()
     {
          cout << endl;
          for (auto [vertex, neighbours] : adjlist)
          {
               cout << vertex << "->" << endl;
               for (auto [neighbour, w] : neighbours)
               {
                    cout << "( " << neighbour << "," << w << " )" << endl;
               }
               cout << endl;
          }
     }
};

void Dijkstra(int V, int src, map<int, vector<pair<int, int>>> &adjlist)
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

               if (dist[u] != INF && (dist[u] + w) < dist[v])
               {
                    dist[v] = dist[u] + w;
                    pq.push({dist[u] + w, v});
               }
          }
     }

     cout << "\nprinting distance from source : " << src << endl;

     for (int i = 0; i < V; i++)
     {
          cout << dist[i] << " ";
     }
     cout << endl;
}

int main()
{

     WeightedGraph G;

     G.addEdge(0, 1, 2);
     G.addEdge(0, 2, 4);

     G.addEdge(1, 2, 1);
     G.addEdge(1, 2, 7);

     G.addEdge(2, 4, 3);
     G.addEdge(3, 5, 1);

     G.addEdge(4, 3, 2);
     G.addEdge(4, 5, 5);

     Dijkstra(6, 0, G.adjlist);

     return 0;
}