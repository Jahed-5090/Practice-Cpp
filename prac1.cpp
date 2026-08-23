#include <iostream>
#include <vector>
using namespace std;   

struct edge {
    int u, v, w;
};

class weightedGraph {
public: 
    vector<edge> edgelist;  
    
    void addEdge(int u, int v, int w) {
        // Fix 1: Using braces {} to construct the 'edge' struct on the fly
        this->edgelist.push_back({u, v, w}); 
    }
    
    // Related Example: A method to print the edge list
    void printEdges() {
        cout << "Edge List (u -> v : weight)\n";
        for(const auto& e : edgelist) {
            cout << e.u << " -> " << e.v << " : " << e.w << "\n";
        }
    }
}; // Fix 2: Semicolon added here

int main() { 
    weightedGraph g;
    
    // Adding some sample edges
    g.addEdge(0, 1, 10);
    g.addEdge(1, 2, 20);
    g.addEdge(2, 0, 30);
    g.addEdge(2, 3, 40);
    
    // Print to verify
    g.printEdges();

    return 0;
}