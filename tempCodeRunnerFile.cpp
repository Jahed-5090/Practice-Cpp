#include <bits/stdc++.h>
using namespace std;

class WeightedGraph {
    map<int, vector<pair<int,int>>> adj;

public:
    void addEdge(int u, char v, int w, bool directed = false) {
        adj[u].push_back({v, w});
        if (!directed)
            adj[v].push_back({u, w});
    }

    void print() {
        for (auto &[vertex, neighbors] : adj) {
            cout << vertex << ": ";
            for (auto [neighbor, w] : neighbors)
                cout << "(" << neighbor << ", w=" << w << ") ";
            cout << "\n";
        }
    }
};

int main() {
   
    WeightedGraph g;
    g.addEdge(0, 1, 4);
    g.addEdge(0, 4, 1);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 2);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 3, 7);
    g.addEdge(3, 4, 6);

    g.print();
    return 0;
}