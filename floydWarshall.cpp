#include <bits/stdc++.h>
using namespace std;

const int INF = INT_MAX / 2; // safe sentinel: large enough to mean "no path", but won't overflow when added

class weightedGraph {
public:
    map<int, vector<pair<int, int>>> adjlist;

    void addEdge(int u, int v, int w) {
        this->adjlist[u].push_back({v, w});
    }
};

void floydWarshall(const map<int, vector<pair<int, int>>>& adjlist, int V) {
    vector<vector<int>> dist(V, vector<int>(V, INF));

    // distance from a vertex to itself is 0
    for (int i = 0; i < V; i++) {
        dist[i][i] = 0;
    }

    // load direct edges into dist[][]
    for (auto &[vertex, neighbors] : adjlist) {
        for (auto &e : neighbors) {
            int to = e.first;
            int w  = e.second;
            dist[vertex][to] = min(dist[vertex][to], w); // min(), in case of duplicate edges
        }
    }

    // core Floyd-Warshall relaxation
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] < INF && dist[k][j] < INF) // guard against overflow
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    // print result with vertex labels as row/column headers
    cout << "All-pairs shortest distances:\n\n";

    cout << setw(6) << " ";
    for (int j = 0; j < V; j++)
        cout << setw(6) << j;
    cout << "\n";

    for (int i = 0; i < V; i++) {
        cout << setw(6) << i; // row label
        for (int j = 0; j < V; j++) {
            if (dist[i][j] >= INF)
                cout << setw(6) << "INF";
            else
                cout << setw(6) << dist[i][j];
        }
        cout << "\n";
    }
}

int main() {
    weightedGraph g;
    g.addEdge(0, 1, 3);
    g.addEdge(0, 2, 8);
    g.addEdge(0, 4, -4);
    g.addEdge(1, 3, 1);
    g.addEdge(1, 4, 7);
    g.addEdge(2, 1, 4);
    g.addEdge(3, 0, 2);
    g.addEdge(3, 2, -5);
    g.addEdge(4, 3, 6);

    floydWarshall(g.adjlist, 5);

    return 0;
}