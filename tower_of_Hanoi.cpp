#include <iostream>

using namespace std;

// Procedure 6.9: TOWER(N, BEG, AUX, END)
void TOWER(int N, char BEG, char AUX, char END) {
    // 1. If N = 1, then:
    if (N == 1) {
        // (a) Write: BEG -> END.
        cout << BEG << " -> " << END << endl;
        // (b) Return.
        return;
    }
    
    // 2. Call TOWER(N - 1, BEG, END, AUX)
    TOWER(N - 1, BEG, END, AUX);
    
    // 3. Write: BEG -> END
    cout << BEG << " -> " << END << endl;
    
    // 4. Call TOWER(N - 1, AUX, BEG, END)
    TOWER(N - 1, AUX, BEG, END);
    
    // 5. Return
    return;
}

int main() {
    int disks = 4; // Let's use n=3 to match the textbook's list of 7 moves
    
    cout << "Moves for " << disks << " disks:" << endl;
    
    // Initial call: Moving from Peg A to Peg C, using Peg B as auxiliary
    TOWER(disks, 'A', 'B', 'C');
    
    return 0;
}