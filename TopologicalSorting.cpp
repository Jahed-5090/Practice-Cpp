#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>

using namespace std;

// Using unordered_map for O(1) lookups
unordered_map<char, vector<char>> adj;
unordered_map<char, bool> visited;
stack<char> stk;

void DFS(char u) {
    visited[u] = true;

    // Range-based for loop directly accesses neighbors without checking a matrix
    for(char neighbor : adj[u]) {
        if(!visited[neighbor]) {
            DFS(neighbor);
        }
    }

    // Push the current node to the stack only after all its neighbors are explored
    stk.push(u); 
}

void topologicalSort(const vector<char>& all_nodes) {
    for(char node : all_nodes) {
        // If a node doesn't exist in the visited map, it defaults to false
        if(!visited[node]) {
            DFS(node);
        }
    }
}

int main() {
    // 1. Define all nodes in the graph
    // (This guarantees we check isolated nodes or nodes with no outgoing edges)
    vector<char> nodes = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

    // 2. Build the Adjacency List directly with characters
    adj['A'] = {'D'};
    adj['B'] = {'A', 'C'};
    adj['C'] = {'E'};
    adj['D'] = {}; 
    adj['E'] = {'F'};
    adj['F'] = {};
    adj['G'] = {'D', 'F'};
    adj['H'] = {'G'};

    topologicalSort(nodes);

    // 3. Print the sorted results
    cout << "Topological Sort Order: ";
    while(!stk.empty()) {
        cout << stk.top() << " ";
        stk.pop();
    }
    cout << endl;

    return 0;
}