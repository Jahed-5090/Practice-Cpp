#include <bits/stdc++.h>
using namespace std;

const int INF = INT_MAX / 2;

// ==========================================
// 1. DATA STRUCTURES (Pure Data Representation)
// ==========================================

struct Edge {
    int u, v, w;
};

class WeightedGraph {
public:
    int V;
    vector<Edge> edgelist;

    WeightedGraph(int V) : V(V) {}

    void addEdge(int u, int v, int w) {
        edgelist.push_back({u, v, w});
    }
};

// ==========================================
// 2. ALGORITHMS (Decoupled Operations)
// ==========================================

namespace GraphAlgorithms {

    // Helper function to recursively print the path
    void printPath(int v, const vector<int>& parent) {
        if (v == -1) return;
        printPath(parent[v], parent);
        cout << v << " ";
    }

    // Standard Bellman-Ford (returns false if negative cycle exists)
    bool bellmanFord(int V, const vector<Edge>& edges, int src, vector<int>& h) {
        h.assign(V, INF);
        h[src] = 0;

        for (int i = 0; i < V - 1; i++) {
            for (const auto& e : edges) {
                if (h[e.u] != INF && h[e.u] + e.w < h[e.v]) {
                    h[e.v] = h[e.u] + e.w;
                }
            }
        }

        for (const auto& e : edges) {
            if (h[e.u] != INF && h[e.u] + e.w < h[e.v]) {
                return false;
            }
        }
        return true;
    }

    // Standard Dijkstra (modified to track parent nodes)
    void dijkstra(int V, const vector<vector<pair<int,int>>>& adj, int src, vector<int>& dist, vector<int>& parent) {
        dist.assign(V, INF);
        parent.assign(V, -1);
        dist[src] = 0;

        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        pq.push({0, src});

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            
            if (d > dist[u]) continue;

            for (const auto& edge : adj[u]) {
                int v = edge.first;
                int weight = edge.second;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u; // Track where we came from
                    pq.push({dist[v], v});
                }
            }
        }
    }

    // The core Johnson's logic coordinating the subroutines
    void johnson(const WeightedGraph& g) {
        int V = g.V;
        int virtual_src = V; 

        // Step 1: Augment graph
        vector<Edge> augmented = g.edgelist;
        for (int i = 0; i < V; i++) {
            augmented.push_back({virtual_src, i, 0});
        }

        // Step 2: Bellman-Ford
        vector<int> h;
        if (!bellmanFord(V + 1, augmented, virtual_src, h)) {
            cout << "Graph contains a negative weight cycle. Johnson's algorithm cannot proceed.\n";
            return;
        }

        // Step 3: Reweight edges & build adjacency list
        vector<vector<pair<int,int>>> reweightedAdj(V);
        for (const auto& e : g.edgelist) {
            int newW = e.w + h[e.u] - h[e.v];
            reweightedAdj[e.u].push_back({e.v, newW});
        }

        // Step 4 & 5: Dijkstra and Matrix Construction
        vector<vector<int>> shortest_dists(V, vector<int>(V, INF));
        vector<vector<int>> all_parents(V, vector<int>(V, -1));

        for (int src = 0; src < V; src++) {
            vector<int> dist, parent;
            dijkstra(V, reweightedAdj, src, dist, parent);

            for (int dst = 0; dst < V; dst++) {
                if (dist[dst] < INF) {
                    shortest_dists[src][dst] = dist[dst] - h[src] + h[dst];
                }
            }
            all_parents[src] = parent;
        }

        // --- Output Generation ---
        
        cout << "1. All-Pairs Shortest Distances:\n\n";
        cout << setw(6) << " ";
        for (int j = 0; j < V; j++) cout << setw(6) << j;
        cout << "\n";    
        for (int i = 0; i < V; i++) {
            cout << setw(6) << i;
            for (int j = 0; j < V; j++) {
                if (shortest_dists[i][j] >= INF) cout << setw(6) << "INF";
                else cout << setw(6) << shortest_dists[i][j];
            }
            cout << "\n";
        }

        cout << "\n\n2. Shortest Paths Routing:\n\n";
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (i != j && shortest_dists[i][j] < INF) {
                    cout << "Path " << i << " -> " << j << " (cost: " << setw(2) << shortest_dists[i][j] << ") : ";
                    printPath(j, all_parents[i]);
                    cout << "\n";
                }
            }
        }
    }
}

// ==========================================
// 3. MAIN EXECUTION
// ==========================================

int main() {
    WeightedGraph g(4);
    g.addEdge(0, 1, -5);
    g.addEdge(0, 2, 2);
    g.addEdge(0, 3, 3);
    g.addEdge(1, 2, 4);
    g.addEdge(2, 3, 1);
    g.addEdge(3, 1, 6);

    GraphAlgorithms::johnson(g);

    return 0;
}