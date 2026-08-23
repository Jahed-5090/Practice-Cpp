#include <iostream>
#include <vector>
using namespace std;

void merge(int arr[], int st, int mid, int end)
{

     int i = st, j = mid + 1;

     vector<int> tmp;

     while (i <= mid && j <= end)
     {

          if (arr[i] <= arr[j])
          {
               tmp.push_back(arr[i]);
               i++;
          }
          else
          {
               tmp.push_back(arr[j]);
               j++;
          }
     }

     while (i <= mid)
     {
          tmp.push_back(arr[i]);
          i++;
     }

     while (j <= end)
     {
          tmp.push_back(arr[j]);
          j++;
     }

     for (int i = 0; i < tmp.size(); i++)
     {
          arr[st + i] = tmp[i];
     }
}

void mergeSort(int arr[], int st, int end)
{
     if (st < end)
     {
          int mid = st + (end - st) / 2;

          mergeSort(arr, st, mid);
          mergeSort(arr, mid + 1, end);

          merge(arr, st, mid, end);
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
     mergeSort(arr, 0, 8);
     display(arr, 9);

     return 0;
}