// Bellman-Ford - Edge List

#include <bits/stdc++.h>
using namespace std;

const int INF = INT_MAX;

struct edge {
    int u, v, w;
};

class WeightedGraph {
public:
    vector<edge> edgeList;

    void addEdge(int u, int v, int w, bool directed = true) {
        edgeList.push_back({u, v, w});
        // If undirected, you would uncomment the next line:
        // if (!directed) edgeList.push_back({v, u, w});
    }

    void printGraph() {
        for (auto &edge : edgeList) {
            cout << "src: " << edge.u << " dest: " << edge.v << " weight: " << edge.w << endl;
        }
    }
};

void BellmanFord(int V, int src, const vector<edge> &edgeList) {
    vector<int> dist(V, INF);
    dist[src] = 0;

    // Step 1: Relax all edges (V - 1) times
    for (int i = 0; i < V - 1; i++) {
        for (const auto &edge : edgeList) {
            int u = edge.u;
            int v = edge.v;
            int w = edge.w;
            
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    // Step 2: Check for negative-weight cycles
    // If we can still relax an edge, then a negative cycle exists
    for (const auto &edge : edgeList) {
        int u = edge.u;
        int v = edge.v;
        int w = edge.w;
        
        if (dist[u] != INF && dist[u] + w < dist[v]) {
            cout << "\nGraph contains a negative weight cycle!" << endl;
            return; 
        }
    }

    cout << "\nPrinting distance from source : " << src << endl;
    for (int i = 0; i < V; i++) {
        if (dist[i] == INF) cout << "INF ";
        else cout << dist[i] << " ";
    }
    cout << endl;
}

int main() {
    WeightedGraph G;
    int V = 6;

    G.addEdge(0, 1, -100);
    G.addEdge(0, 2, 4);

    G.addEdge(1, 2, 1);
    G.addEdge(1, 2, 7);

    G.addEdge(2, 4, 3);
    G.addEdge(3, 5, 1);

    G.addEdge(4, 3, 2);
    G.addEdge(4, 5, 5);

    // Try modifying one of the weights to a large negative number 
    // e.g., G.addEdge(4, 3, -10); to see the negative cycle detection trigger.

    BellmanFord(V, 0, G.edgeList);

    return 0;
} 

// BelmanFord-Matrix 

#include <bits/stdc++.h>
using namespace std;

const int INF = INT_MAX;

class WeightedGraph {
public:
    int V;
    vector<vector<int>> adjMatrix;

    WeightedGraph(int V) {
        this->V = V;
        // INF represents no edge between vertices
        adjMatrix.assign(V, vector<int>(V, INF)); 
    }

    void addEdge(int u, int v, int w, bool directed = true) {
        adjMatrix[u][v] = w;
        if (!directed) {
            adjMatrix[v][u] = w;
        }
    }
};

void BellmanFordMatrix(int V, int src, const vector<vector<int>> &adjMatrix) {
    vector<int> dist(V, INF);
    dist[src] = 0;

    // Step 1: Relax all edges (V - 1) times
    for (int i = 0; i < V - 1; i++) {
        for (int u = 0; u < V; u++) {
            for (int v = 0; v < V; v++) {
                int w = adjMatrix[u][v];
                if (w != INF && dist[u] != INF && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                }
            }
        }
    }

    // Step 2: Check for negative-weight cycles
    for (int u = 0; u < V; u++) {
        for (int v = 0; v < V; v++) {
            int w = adjMatrix[u][v];
            if (w != INF && dist[u] != INF && dist[u] + w < dist[v]) {
                cout << "\nGraph contains a negative weight cycle!" << endl;
                return;
            }
        }
    }

    // Step 3: Print distances
    cout << "\nPrinting distance from source (Matrix) : " << src << endl;
    for (int i = 0; i < V; i++) {
        if (dist[i] == INF) cout << "INF ";
        else cout << dist[i] << " ";
    }
    cout << endl;
}

int main() {
    int V = 6;
    WeightedGraph G(V);

    G.addEdge(0, 1, 2);
    G.addEdge(0, 2, 4);
    G.addEdge(1, 2, 1);
    G.addEdge(1, 2, 7); 
    G.addEdge(2, 4, 3);
    G.addEdge(3, 5, 1);
    G.addEdge(4, 3, 2);
    G.addEdge(4, 5, 5);

    BellmanFordMatrix(V, 0, G.adjMatrix);

    return 0;
}


// BellmanFord-AdjacencyList 

#include <bits/stdc++.h>
using namespace std;

const int INF = INT_MAX;

class WeightedGraph {
public:
    int V;
    // pair stores {destination, weight}
    vector<vector<pair<int, int>>> adjList;

    WeightedGraph(int V) {
        this->V = V;
        adjList.resize(V);
    }

    void addEdge(int u, int v, int w, bool directed = true) {
        adjList[u].push_back({v, w});
        if (!directed) {
            adjList[v].push_back({u, w});
        }
    }
};

void BellmanFordList(int V, int src, const vector<vector<pair<int, int>>> &adjList) {
    vector<int> dist(V, INF);
    dist[src] = 0;

    // Step 1: Relax all edges (V - 1) times
    for (int i = 0; i < V - 1; i++) {
        for (int u = 0; u < V; u++) {
            for (auto &edge : adjList[u]) {
                int v = edge.first;
                int w = edge.second;
                
                if (dist[u] != INF && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                }
            }
        }
    }

    // Step 2: Check for negative-weight cycles
    for (int u = 0; u < V; u++) {
        for (auto &edge : adjList[u]) {
            int v = edge.first;
            int w = edge.second;
            
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                cout << "\nGraph contains a negative weight cycle!" << endl;
                return;
            }
        }
    }

    // Step 3: Print distances
    cout << "\nPrinting distance from source (List) : " << src << endl;
    for (int i = 0; i < V; i++) {
        if (dist[i] == INF) cout << "INF ";
        else cout << dist[i] << " ";
    }
    cout << endl;
}

int main() {
    int V = 6;
    WeightedGraph G(V);

    G.addEdge(0, 1, 2);
    G.addEdge(0, 2, 4);
    G.addEdge(1, 2, 1);
    G.addEdge(1, 2, 7); 
    G.addEdge(2, 4, 3);
    G.addEdge(3, 5, 1);
    G.addEdge(4, 3, 2);
    G.addEdge(4, 5, 5);

    BellmanFordList(V, 0, G.adjList);

    return 0;
}
