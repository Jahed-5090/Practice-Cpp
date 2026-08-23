#include <iostream>
#include <vector>
using namespace std;

int partition(int arr[], int st, int end)
{

     int idx = st-1;
     int pivot = arr[end];

     for (int j = st; j < end; j++)
     {
          if (arr[j] <= pivot)
          {
               idx++;
               swap(arr[j], arr[idx]);
          }
     }

     idx++;
     swap(arr[idx], arr[end]);

     return idx;
}

void quickSort(int arr[], int st, int end)
{

     if (st < end)
     {
          int pi = partition(arr, st, end);

          quickSort(arr, st, pi - 1);
          quickSort(arr, pi + 1, end);

     }
} 

void display(int arr[], int sz)
{
     for (int i = 0; i < sz; i++)
     {
          cout << arr[i] << " ";
     }
     cout << endl;
}

int main()
{ 

     int arr[] = {9, 8, 7, 6, 5, 4, 1, 2, 3};
     quickSort(arr, 0, 8);
     display(arr, 9);

     return 0;
}