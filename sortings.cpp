#include <iostream>
#include <vector>
using namespace std;

// 1. Bubble Sort
// Idea: Repeatedly swap adjacent elements if they are in the wrong order. 
// The largest elements "bubble" to the end of the array first.
void bubbleSort(int arr[], int n) {
     for (int i = 0; i < n - 1; i++) {
          bool swapped = false;
          
          // The last 'i' elements are already sorted, so we don't check them
          for (int j = 0; j < n - i - 1; j++) {
               if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                    swapped = true;
               }
          }
          // Optimization: If no elements were swapped in the inner loop, the array is sorted
          if (!swapped) break; 
     }
}

// 2. Selection Sort
// Idea: Find the minimum element in the unsorted portion of the array 
// and swap it with the first unsorted element.
void selectionSort(int arr[], int n) {
     for (int i = 0; i < n - 1; i++) {
          int min_idx = i;
          
          // Scan the rest of the array to find the smallest element
          for (int j = i + 1; j < n; j++) {
               if (arr[j] < arr[min_idx]) {
                    min_idx = j;
               }
          }
          // Swap the found minimum element with the first element of the unsorted part
          if (min_idx != i) {
               swap(arr[i], arr[min_idx]);
          }
     }
}

// 3. Insertion Sort
// Idea: Build the sorted array one element at a time by taking the next element 
// and inserting it into its correct position among the already sorted elements.
void insertionSort(int arr[], int n) {
     for (int i = 1; i < n; i++) {
          int key = arr[i]; // The element we want to insert
          int j = i - 1;

          // Move elements of arr[0..i-1], that are greater than key,
          // to one position ahead of their current position
          while (j >= 0 && arr[j] > key) {
               arr[j + 1] = arr[j];
               j = j - 1;
          }
          // Place the key in its correct location
          arr[j + 1] = key;
     }
} 

// quick sort start

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

// Merge Sort starting 
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

void display(int arr[], int sz) {
     for (int i = 0; i < sz; i++) {
          cout << arr[i] << " ";
     }
     cout << endl;
}

int main() {
     // Test arrays
     int arr1[] = {9, 8, 7, 6, 5, 4, 1, 2, 3};
     int arr2[] = {9, 8, 7, 6, 5, 4, 1, 2, 3};
     int arr3[] = {9, 8, 7, 6, 5, 4, 1, 2, 3};
     int arr4[] = {9, 8, 7, 6, 5, 4, 1, 2, 3};
     int arr5[] = {9, 8, 7, 6, 5, 4, 1, 2, 3};
     int sz = 9;

     cout << "--- Bubble Sort ---" << endl;
     bubbleSort(arr1, sz);
     display(arr1, sz);

     cout << "\n--- Selection Sort ---" << endl;
     selectionSort(arr2, sz);
     display(arr2, sz);

     cout << "\n--- Insertion Sort ---" << endl;
     insertionSort(arr3, sz);
     display(arr3, sz);

     cout << "\n--- Quick Sort ---" << endl;
     quickSort(arr3,0,sz-1);
     display(arr3, sz);

     cout << "\n--- Merge Sort ---" << endl;
     mergeSort(arr3,0,sz-1);
     display(arr3, sz);

     return 0;
}