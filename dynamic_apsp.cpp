// dynamic_apsp.cpp
//
// Dynamic All-Pairs Shortest Path (APSP) using Floyd-Warshall as the base
// algorithm, plus:
//   1) Static build          -> classic Floyd-Warshall,               O(V^3)
//   2) Incremental update    -> edge insertion / weight decrease,     O(V^2)
//   3) Decremental update    -> edge deletion   / weight increase,    O(V^3) worst case
//                                (find affected pairs, then re-derive them)
//
// Compile:  g++ -std=c++17 -O2 -o dynamic_apsp dynamic_apsp.cpp
// Run:      ./dynamic_apsp

#include <bits/stdc++.h>
using namespace std;

static const long long INF = LLONG_MAX / 4; // "infinity" that is safe to add without overflow

class DynamicAPSP {
public:
    int n;                                  // number of vertices (1..n)
    vector<vector<long long>> D;            // D[i][j] = current shortest distance i -> j
    vector<vector<long long>> W;            // W[i][j] = current direct edge weight (INF if no edge)

    explicit DynamicAPSP(int n_) : n(n_),
        D(n_ + 1, vector<long long>(n_ + 1, INF)),
        W(n_ + 1, vector<long long>(n_ + 1, INF)) {
        for (int i = 1; i <= n; ++i) { D[i][i] = 0; W[i][i] = 0; }
    }

    // ---------------------------------------------------------------
    // 1) STATIC BUILD: classic Floyd-Warshall, O(V^3)
    //    Call this once after loading all initial edges into W.
    // ---------------------------------------------------------------
    void build() {
        D = W; // start from raw edge weights
        for (int k = 1; k <= n; ++k)
            for (int i = 1; i <= n; ++i) {
                if (D[i][k] >= INF) continue;          // small pruning, not required for correctness
                for (int j = 1; j <= n; ++j)
                    if (D[i][k] + D[k][j] < D[i][j])
                        D[i][j] = D[i][k] + D[k][j];
            }
    }

    // ---------------------------------------------------------------
    // 2) INCREMENTAL UPDATE: edge (u,v) inserted, or its weight decreased
    //    to w_new.  Only ONE relaxation pass over all (i,j) is needed,
    //    because k is fixed to the single changed edge instead of being
    //    looped 1..n like in full Floyd-Warshall.                O(V^2)
    // ---------------------------------------------------------------
    void incrementalUpdate(int u, int v, long long w_new) {
        if (w_new < W[u][v]) W[u][v] = w_new;   // remember the new raw edge weight too
        if (w_new < D[u][v]) D[u][v] = w_new;

        for (int i = 1; i <= n; ++i) {
            if (D[i][u] >= INF) continue;
            for (int j = 1; j <= n; ++j) {
                long long newDist = D[i][u] + w_new + D[v][j];
                if (newDist < D[i][j]) D[i][j] = newDist;
            }
        }
    }

    // ---------------------------------------------------------------
    // 3) DECREMENTAL UPDATE: edge (u,v) deleted (or its weight increased
    //    so much that it may no longer lie on any shortest path).
    //
    //    Step 1: find every pair (i,j) whose *current* shortest path is
    //            exactly routed through edge (u,v).
    //    Step 2: remove the edge from W, then re-derive the true shortest
    //            distance for each affected pair using the remaining graph
    //            (a bounded Floyd-Warshall pass restricted to those pairs).
    //    Step 3: everything else is left untouched.
    //
    //    Worst case this touches O(V^2) pairs, each re-derived in O(V),
    //    giving O(V^3) worst case -- but in practice far fewer pairs are
    //    affected, which is the whole point of doing it this way instead
    //    of rerunning build() from scratch every time.
    // ---------------------------------------------------------------
    void decrementalUpdate(int u, int v) {
        long long oldW = W[u][v];
        if (oldW >= INF) return; // edge did not exist, nothing to do

        // Step 1: identify affected pairs BEFORE removing the edge.
        // (i,j) is affected iff its shortest path used edge (u,v) directly:
        //   D[i][u] + oldW + D[v][j] == D[i][j]
        vector<pair<int,int>> affected;
        for (int i = 1; i <= n; ++i) {
            if (D[i][u] >= INF) continue;
            for (int j = 1; j <= n; ++j) {
                if (D[v][j] >= INF) continue;
                if (D[i][u] + oldW + D[v][j] == D[i][j])
                    affected.push_back({i, j});
            }
        }

        // Step 2a: remove the edge from the raw weight matrix.
        W[u][v] = INF;

        // Step 2b: for the removed edge itself, and for every affected pair,
        // invalidate the old (now-wrong) distance so it does not
        // incorrectly seed the recomputation below.
        for (auto &pr : affected) D[pr.first][pr.second] = INF;
        if (D[u][v] == oldW) D[u][v] = INF; // direct pair too, if not already covered

        // Step 2c: rebuild the raw single-edge baseline for affected rows
        // (needed so recomputation can "see" direct edges again), then
        // re-derive affected distances via a restricted relaxation:
        // try every vertex k as an intermediate for each affected pair.
        // (This is Floyd-Warshall's relaxation, but restricted to the
        // pairs we know can possibly have changed.)
        for (auto &pr : affected) {
            int i = pr.first, j = pr.second;
            D[i][j] = W[i][j]; // direct edge, if any survives, is a valid candidate
        }
        for (int k = 1; k <= n; ++k) {
            for (auto &pr : affected) {
                int i = pr.first, j = pr.second;
                if (D[i][k] < INF && D[k][j] < INF && D[i][k] + D[k][j] < D[i][j])
                    D[i][j] = D[i][k] + D[k][j];
            }
        }
    }

    void addEdge(int u, int v, long long w) { W[u][v] = w; }

    void printMatrix(const string &title) const {
        cout << "\n" << title << "\n";
        cout << "     ";
        for (int j = 1; j <= n; ++j) cout << setw(6) << j;
        cout << "\n";
        for (int i = 1; i <= n; ++i) {
            cout << setw(4) << i << " ";
            for (int j = 1; j <= n; ++j) {
                if (D[i][j] >= INF) cout << setw(6) << "INF";
                else cout << setw(6) << D[i][j];
            }
            cout << "\n";
        }
    }
};

int main() {
    // ---- Same 5-vertex example graph used in the lab report ----
    // Edges: 1->2(3), 1->3(8), 2->4(1), 2->5(7), 3->2(4), 4->1(2), 4->3(5), 5->4(6)
    DynamicAPSP g(5);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 8);
    g.addEdge(2, 4, 1);
    g.addEdge(2, 5, 7);
    g.addEdge(3, 2, 4);
    g.addEdge(4, 1, 2);
    g.addEdge(4, 3, 5);
    g.addEdge(5, 4, 6);

    // 1) Static build
    g.build();
    g.printMatrix("D0: Initial APSP matrix (Floyd-Warshall)");

    // 2) Incremental update: w(1,3): 8 -> 2
    g.incrementalUpdate(1, 3, 2);
    g.printMatrix("D1: After incremental update w(1,3): 8 -> 2");

    // 3) Decremental update: delete edge (2,4)
    g.decrementalUpdate(2, 4);
    g.printMatrix("D2: After decremental update - edge (2,4) deleted");

    return 0;
}
