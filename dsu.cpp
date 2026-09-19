#include <bits/stdc++.h>
using namespace std;

class DSU
{

public:
     int n;
     vector<int> parent, rank;

     DSU(int n)
     {
          this->n = n;
          parent.resize(n, 0);
          rank.resize(n, 0);

          for (int i = 0; i < n; i++)
               parent[i] = i;
     }

     void UnionByRank(int a, int b)
     {

          int parA = findParent(a);
          int parB = findParent(b);

          if (parA == parB)
               return;

          if (rank[parA] == rank[parB])
          {
               parent[parB] = parA;
               rank[parA]++;
          }
          else if (rank[parA] > rank[parB])
          {
               parent[parB] = parA;
          }
          else
          {
               parent[parA] = parB;
          }
     }

     int findParent(int x)
     {
          if (parent[x] == x)
          {
               return parent[x];
          }
          return parent[x] = findParent(parent[x]);
     }

     void printParent()
     {
          cout << "Parent : ";
          for (int i = 0; i < n; i++)
          {
               cout << parent[i] << " ";
          }
          cout << endl;
          cout << "Rank : ";
          for (int i = 0; i < n; i++)
          {
               cout << rank[i] << " ";
          }
          cout << endl;
     }
};

int main()
{

     DSU dsu1(5);

     dsu1.UnionByRank(0, 2);
     dsu1.UnionByRank(0, 1);

     dsu1.printParent();

     return 0;
}