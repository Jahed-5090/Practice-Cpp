#include <iostream>
#include <queue> 
#include <stack> 
using namespace std;

const int n = 7;

void BFS(int src, int admat[][n], bool vis[])
{
     queue<int> q;

     q.push(src);
     vis[src] = true;

     while (q.size() > 0)
     {
          int u = q.front();  
          q.pop();

          cout << u << " ";

          // FIXED: Iterate through all possible column indices (0 to n-1)
          for (int i = 0; i < n; i++)
          {
               // Check if there is an edge (1) AND the node is unvisited
               if (admat[u][i] == 1 && !vis[i])
               {
                    q.push(i);       // Push the node index 'i', not the value '1'
                    vis[i] = true;   // Mark node 'i' as visited
               }
          }
     }
}

void DFS(int src, int admat[][n], bool vis[])
{
     // 1. Visit the current node
     cout << src << " ";
     vis[src] = true;

     // 2. Iterate through all possible adjacent nodes (0 to n-1)
     for (int i = 0; i < n; i++)
     {
          // 3. Check if an edge exists (value is 1) AND the node is unvisited
          if (admat[src][i] == 1 && !vis[i])
          {
               // 4. Recursively call DFS for the unvisited neighbor
               DFS(i, admat, vis);
          }
     }
}

int main()
{
     // Initialize the adjacency matrix with 0s
     int admat[n][n] = {0};

     // Initialize the visited array with false
     bool vis[n] = {false};

     // Let's build a sample undirected graph:
     //         0
     //       /   \
     //      1     2
     //     / \   / \
     //    3   4 5   6

     // Edges connected to 0
     admat[0][1] = 1;
     admat[1][0] = 1;
     admat[0][2] = 1;
     admat[2][0] = 1;

     // Edges connected to 1
     admat[1][3] = 1;
     admat[3][1] = 1;
     admat[1][4] = 1;
     admat[4][1] = 1;

     // Edges connected to 2
     admat[2][5] = 1;
     admat[5][2] = 1;
     admat[2][6] = 1;
     admat[6][2] = 1;

     cout << "DFS Traversal starting from node 0: ";
     DFS(0, admat, vis);
     cout << endl;

     for(int i=0;i<n;i++) vis[i]=false ;

     cout << "BFS Traversal starting from node 0: ";
     BFS(0, admat, vis);
     cout << endl;

     return 0;
}