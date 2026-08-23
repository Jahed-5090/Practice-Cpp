#include <iostream>
using namespace std;

class BIT {
private:
    int n;
    int tree[1001];

public:
    BIT(int arr[], int size) {
        n = size;
        for (int i = 0; i <= n; i++) tree[i] = 0;
        for (int i = 0; i < n; i++)
            update(i + 1, arr[i]);
    }

    void update(int i, int delta) {
        while (i <= n) {
            tree[i] += delta;
            i += (i & -i);
        }
    }

    int query(int i) {
        int sum = 0;
        while (i > 0) {
            sum += tree[i];
            i -= (i & -i);
        }
        return sum;
    }

    int rangeQuery(int l, int r) {
        return query(r) - query(l - 1);
    }

    // ── POINT SET: finds old value on its own, sets index i to newVal ──
    void pointSet(int i, int newVal) {
        int oldVal = query(i) - query(i - 1);  // extract current value at i
        int delta  = newVal - oldVal;           // calculate how much to add
        update(i, delta);                       // apply the change
    }

    void printTree() {
        cout << "BIT Array: ";
        for (int i = 1; i <= n; i++)
            cout << "tree[" << i << "]=" << tree[i] << "  ";
        cout << endl;
    }
};

int main() { 

    cout << endl ;
    
    int arr[] = {1, 3, 5, 7, 9, 11, 13, 15};
    int n = sizeof(arr) / sizeof(arr[0]);

    BIT bit(arr, n);
    bit.printTree();

    cout << "\nPrefix Sum [1..6]  = " << bit.query(6) << endl;       // 36
    cout << "Range  Sum [3..6]  = " << bit.rangeQuery(3, 6) << endl; // 32

    // pointSet: programmer only gives index and new value
    cout << "\nPointSet: Set arr[5] to 20 (old value was 9)" << endl;
    bit.pointSet(5, 20);
    bit.printTree();
    cout << "Prefix Sum [1..8] after pointSet = " << bit.query(8) << endl; // 75 (64+11)

    cout << "\nPointSet: Set arr[3] to 1 (old value was 5)" << endl;
    bit.pointSet(3, 1);
    bit.printTree();
    cout << "Prefix Sum [1..6] after pointSet = " << bit.query(6) << endl; // 32 (36-4)

    return 0;
}