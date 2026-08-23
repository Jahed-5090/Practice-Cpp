#include <iostream>
#include <vector>
using namespace std;   

struct edge {
    int u, v , w ; 
};

class weightedGraph {
public: 
    vector<edge> edgelist;  
    
    void addEdge(int u, int v, int w) {
        this->edgelist.push_back({u, v, w}); 
    }
    
    void printEdges() {
        cout << "Edge List (u -> v : weight)\n";
        for(const auto& e : edgelist) {
            cout << e.u << " -> " << e.v << " : " << e.w << "\n";
        }
    }
}; 

int main() { 
    weightedGraph g;
    
    g.addEdge(0, 1, 10);
    g.addEdge(1, 2, 20);
    g.addEdge(2, 0, 30);
    g.addEdge(2, 3, 40);
    
    g.printEdges();

    return 0;
}