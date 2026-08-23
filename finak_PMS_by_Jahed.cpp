
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <limits>
using namespace std;


string todayDate() {
    time_t t = time(nullptr);
    tm* local_tm = localtime(&t);
    char buf[11];
    strftime(buf, sizeof(buf), "%Y-%m-%d", local_tm);
    return string(buf);
}

string currentDateTime() {
    time_t t = time(nullptr);
    tm* local_tm = localtime(&t);
    char buf[20];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", local_tm);
    return string(buf);
}

string encrypt(const string &input) {
    string result = input;
    for (char &c : result) c = c + 3; 
    return result;
}

string decrypt(const string &input) {
    string result = input;
    for (char &c : result) c = c - 3;
    return result;
}

bool validDateFormat(const string &d) {
    if (d.size() != 10 || d[4] != '-' || d[7] != '-')
        return false;

    for (size_t i = 0; i < d.size(); ++i) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(static_cast<unsigned char>(d[i])))
            return false;
    }

    int y = stoi(d.substr(0, 4));
    int m = stoi(d.substr(5, 2));
    int day = stoi(d.substr(8, 2));

    if (m < 1 || m > 12) return false;

    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    bool leap = ( (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0) );
    if (leap) daysInMonth[1] = 29;

    if (day < 1 || day > daysInMonth[m - 1]) return false;

    return true;
}

bool isExpired(const string &expiry_date) {
    if (expiry_date.empty()) return false;
    string td = todayDate();
    return expiry_date < td;
}

bool validateExpiry(const string &expiry) {
    if (expiry.empty()) return false;    
    if (!validDateFormat(expiry)) {
        cout << "Invalid expiry format. Use YYYY-MM-DD.\n";
        return false;
    }
    return true;
}

string toLower(string s) {
    for (char &c : s) c = tolower((unsigned char)c);
    return s;
}

bool validateID(int i) {
    if (i <= 0) 
        return false;
    return true;
}

bool validateName(const string &n) {
    if (n.empty()) 
        return false;
    return true;
}

bool validateQuantity(int q) {
    if (q < 0) 
        return false;
    return true;
}

bool validatePrice(double p) {
    if (p < 0.0) 
        return false;
    return true;
}

class Pharmacy;

// ---------- Medicine ----------
class Medicine {
private:
    int id;
    string name;
    int quantity;
    double price;
    string expiry;
    string manufacturer;
    string category;

public:
    Medicine(int i = 0, const string &n = "", int q = 0, double p = 0.0,
             const string &e = "", const string &m = "", const string &c = "")
        : id(i), name(n), quantity(q), price(p), expiry(e), manufacturer(m), category(c)
    {  }

    ~Medicine() = default;

    friend class Pharmacy;  // Pharmacy can directly access private members

    // operator overloads
    Medicine& operator+=(int extra) {
        quantity += extra;
        return *this;
    }
    Medicine& operator-=(int sold) {
        quantity -= sold;
        return *this;
    }
    bool operator==(const Medicine &other) const {
        return id == other.id;
    }

    // Binary + : combine quantities and average price; if ids differ, names are combined.
    Medicine operator+(const Medicine &other) const {
        Medicine res = *this;
        res.quantity = this->quantity + other.quantity;
        res.price = (this->price + other.price) / 2.0;
        if (this->id != other.id) {
            res.name = this->name + "+" + other.name;
            // keep id of left operand
        }
        return res;
    }

    // Binary - : subtract quantities (no negative quantities)
    Medicine operator-(const Medicine &other) const {
        Medicine res = *this;
        int diff = this->quantity - other.quantity;
        res.quantity = (diff >= 0) ? diff : 0;
        // price remains as left operand's price
        return res;
    }

    // Comparison by price (you can change to quantity or id if desired)
    bool operator<=(const Medicine &other) const {
        return this->price <= other.price;
    }

    // Copy assignment
    Medicine& operator=(const Medicine &other) {
        if (this == &other) return *this;
        id = other.id;
        name = other.name;
        quantity = other.quantity;
        price = other.price;
        expiry = other.expiry;
        manufacturer = other.manufacturer;
        category = other.category;
        return *this;
    }

    // Stream insertion: write as pipe-separated line (same format as file)
    friend ostream& operator<<(ostream &os, const Medicine &m) {
        os << m.id << "|" << m.name << "|" << m.quantity << "|" << fixed << setprecision(2) << m.price
           << "|" << m.expiry << "|" << m.manufacturer << "|" << m.category;
        return os;
    }

    // Stream extraction: read a pipe-separated line from stream into Medicine
    friend istream& operator>>(istream &is, Medicine &m) {
        string line;
        if (!getline(is, line)) return is;
        if (line.empty()) return is;
        stringstream ss(line);
        string part;
        vector<string> parts;
        while (getline(ss, part, '|')) parts.push_back(part);
        if (parts.size() >= 1) m.id = stoi(parts[0]);
        if (parts.size() >= 2) m.name = parts[1];
        if (parts.size() >= 3) m.quantity = stoi(parts[2]);
        if (parts.size() >= 4) m.price = stod(parts[3]);
        if (parts.size() >= 5) m.expiry = parts[4];
        if (parts.size() >= 6) m.manufacturer = parts[5];
        if (parts.size() >= 7) m.category = parts[6];
        return is;
    }

    double totalPriceFor(int qty) const {
        return price * qty;
    }

    friend void showMedicine(const Medicine &med);
};

void showMedicine(const Medicine &med) {
    cout << "---------------------------------\n";
    cout << "ID: " << med.id << "\n";
    cout << "Name: " << med.name << "\n";
    cout << "Category: " << med.category << "\n";
    cout << "Quantity: " << med.quantity << "\n";
    cout << fixed << setprecision(2);
    cout << "Price: " << med.price << "\n";
    cout << "Expiry: " << med.expiry << "\n";
    cout << "Manufacturer: " << med.manufacturer << "\n";
    if (!med.expiry.empty() && isExpired(med.expiry)) {
        cout << "*** WARNING: EXPIRED ***\n";
    }
    cout << "---------------------------------\n";
}

// ---------- Pharmacy (with file support) ----------
class Pharmacy {
private:
    Medicine *medicines;
    int capacity;
    int count;

    const string inventoryFile = "AvailableMedicinDetails.txt";
    const string salesFile = "sellhistory.txt";
    int nextSaleSerial;

    void ensureCapacity() {
        if (capacity < 1) capacity = 1;
        if (count < capacity) return;
        int newCap = capacity * 2;
        if (newCap < 1) newCap = 10;
        Medicine *tmp = new Medicine[newCap];
        for (int i = 0; i < count; ++i) tmp[i] = medicines[i];
        delete[] medicines;
        medicines = tmp;
        capacity = newCap;
    }

    // read inventory from AvailableMedicinDetails.txt if it exists
    void loadInventoryFromFile() {
        ifstream fin(inventoryFile.c_str());
        if (!fin.is_open()) return;
        string line;
        int loaded = 0;
        while (getline(fin, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string part;
            string parts[7];
            int idx = 0;
            while (idx < 7 && getline(ss, part, '|')) {
                parts[idx++] = part;
            }
            if (idx < 4) continue; // bad line
            int id = stoi(parts[0]);
            string name = (idx > 1) ? parts[1] : "";
            int qty = (idx > 2) ? stoi(parts[2]) : 0;
            double price = (idx > 3) ? stod(parts[3]) : 0.0;
            string expiry = (idx > 4) ? parts[4] : "";
            string manufacturer = (idx > 5) ? parts[5] : "";
            string category = (idx > 6) ? parts[6] : "";
            Medicine m(id, name, qty, price, expiry, manufacturer, category);
            if (!duplicateID(id)) {
                ensureCapacity();
                medicines[count++] = m;
                ++loaded;
            }
        }
        fin.close();
        if (loaded > 0) cout << "Loaded " << loaded << " medicine(s) from " << inventoryFile << "\n";
    }

    // write inventory to AvailableMedicinDetails.txt
    void saveInventoryToFile() const {
        ofstream fout(inventoryFile.c_str(), ios::trunc);
        if (!fout.is_open()) {
            cerr << "Failed to open " << inventoryFile << " for writing.\n";
            return;
        }
        for (int i = 0; i < count; ++i) {
            // replace '|' in name if any (avoid breaking format)
            string safeName = medicines[i].name;
            for (char &c: safeName) if (c == '|') c = '/';
            fout << medicines[i].id << "|" << safeName << "|" << medicines[i].quantity << "|"
                 << fixed << setprecision(2) << medicines[i].price << "|" << medicines[i].expiry << "|" << medicines[i].manufacturer << "|" << medicines[i].category << "\n";
        }
        fout.close();
    }

    // init serial number from existing sellhistory.txt
    void initSaleSerial() {
        nextSaleSerial = 1;
        ifstream fin(salesFile.c_str());
        if (!fin.is_open()) return;
        string line;
        int maxSL = 0;
        while (getline(fin, line)) {
            // look for lines starting with number + "."
            stringstream ss(line);
            int num;
            if (ss >> num) {
                char dot;
                if (ss >> dot && dot == '.') {
                    if (num > maxSL) maxSL = num;
                }
            }
        }
        fin.close();
        nextSaleSerial = maxSL + 1;
    }

    // Append sold lines to sellhistory.txt with customer info
    void appendSaleLines(const int ids[], const string names[], const int qtys[], const double prices[], int n,
                         double grandTotal, const string &customerName, const string &customerPhone) {
        ofstream fout(salesFile.c_str(), ios::app);
        if (!fout.is_open()) {
            cerr << "Failed to open " << salesFile << " for appending.\n";
            return;
        }

        fout << "Customer: " << customerName << "\tPhone: " << customerPhone << "\n";
        for (int i = 0; i < n; ++i) {
            fout << nextSaleSerial << ".\t";
            fout << setw(8) << ids[i] << "\t";
            fout << left << setw(20) << names[i] << right << "\t";
            fout << setw(6) << qtys[i] << "\t";
            fout << fixed << setprecision(2) << setw(8) << prices[i] << "\t";
            fout << currentDateTime() << "\n";
            ++nextSaleSerial;
        }
        fout << "Grand Total: " << fixed << setprecision(2) << grandTotal << "\n";
        fout << "----------------------------------------" << "\n";
        fout.close();
    }

public:
    static int lowStockThreshold;

    Pharmacy(int cap = 100) {
        capacity = (cap > 0) ? cap : 100;
        count = 0;
        medicines = new Medicine[capacity];
        // load inventory file
        loadInventoryFromFile();
        // init sale serial
        initSaleSerial();
    }
    ~Pharmacy() {
        // save inventory on exit
        saveInventoryToFile();
        delete[] medicines;
    }

    // Copy assignment for Pharmacy
    Pharmacy& operator=(const Pharmacy &other) {
        if (this == &other) return *this;
        delete[] medicines;
        capacity = other.capacity;
        count = other.count;
        medicines = new Medicine[capacity];
        for (int i = 0; i < count; ++i) medicines[i] = other.medicines[i];
        nextSaleSerial = other.nextSaleSerial;
        return *this;
    }

    int getCount() {return count;}

    bool matchID(int id) {
        for (int i = 0; i < count; ++i) {
            if (medicines[i].id == id) {
                return true;
            }
        }
        return false;
    }

    // operator[] to access medicine by index
    Medicine& operator[](int index) {
        if (index < 0 || index >= count) throw out_of_range("Index out of range");
        return medicines[index];
    }
    const Medicine& operator[](int index) const {
        if (index < 0 || index >= count) throw out_of_range("Index out of range");
        return medicines[index];
    }

    // Check for duplicate ID
    bool duplicateID(int id) const {
        for (int i = 0; i < count; ++i) {
            if (medicines[i].id == id) {
                cout << "Medicine with this ID already exists.\n";
                return true;
            }
        }
        return false;
    }

    bool enoughStock(int id,int qty) const {
        for (int i = 0; i < count; ++i) {
            if (medicines[i].id == id) {
                if(qty<=medicines[i].quantity)
                    return true;
            }
        }
        return false;
    }

    // Add medicine
    void addMedicine(const Medicine &m) {
        if (duplicateID(m.id)) return;
        ensureCapacity();
        medicines[count++] = m;
        saveInventoryToFile();
        cout << "Medicine added successfully!\n";
    }

    // Delete by ID
    void deleteMedicine(int id) {
        int idx;
        for (int i = 0; i < count; ++i)
            if (medicines[i].id == id) { idx = i; break; }
        for (int j = idx; j < count - 1; ++j) medicines[j] = medicines[j+1];
        --count;
        saveInventoryToFile();
        cout << "Medicine deleted successfully.\n";
    }

    // Display all
    void displayAll() const {
        if (count == 0) { cout << "No medicines available!\n"; return; }
        for (int i = 0; i < count; ++i) {
            showMedicine(medicines[i]);
            if (medicines[i].quantity < lowStockThreshold) {
                cout << ">>> Low stock alert: ID " << medicines[i].id
                     << " has quantity " << medicines[i].quantity
                     << " < threshold " << lowStockThreshold << "\n";
            }
        }
    }

    // Search by ID
    void searchMedicineByID(int id) const {
        bool found = false;
        for (int i = 0; i < count; ++i) {
            if (medicines[i].id == id) {
                showMedicine(medicines[i]);
                found = true;
            }
        }
        if (!found) cout << "No matching medicines found.\n";
    }

    // Search by Name
    void searchMedicineByName(const string &nameSub) const {
        string subLower = toLower(nameSub);
        bool found = false;
        for (int i = 0; i < count; ++i) {
            if (toLower(medicines[i].name).find(subLower) != string::npos) {
                showMedicine(medicines[i]);
                found = true;
            }
        }
        if (!found) cout << "No matching medicines found.\n";
    }

    // Search by Category
    void searchByCategory(const string &cat) const {
        bool found = false;
        for (int i = 0; i < count; ++i) {
            if (cat.empty() || medicines[i].category == cat) {
                showMedicine(medicines[i]);
                found = true;
            }
        }
        if (!found) cout << "No matching medicines found.\n";
    }

    // Search by Max Price
    void searchByMaxPrice(double maxPrice) const {
        bool found = false;
        for (int i = 0; i < count; ++i) {
            if (medicines[i].price <= maxPrice) {
                showMedicine(medicines[i]);
                found = true;
            }
        }
        if (!found) cout << "No matching medicines found.\n";
    }

    // Update full details (except ID)
    void updateFullDetails(int id, const string &name, int qty, double price,
                           const string &expiry, const string &manufacturer, const string &category) {
        for (int i = 0; i < count; ++i) {
            if (medicines[i].id == id) {
                if (!name.empty()) medicines[i].name = name;
                medicines[i].quantity = qty;
                medicines[i].price = price;
                if (!expiry.empty()) medicines[i].expiry = expiry;
                if (!manufacturer.empty()) medicines[i].manufacturer = manufacturer;
                if (!category.empty()) medicines[i].category = category;
                saveInventoryToFile();
                cout << "Medicine details updated.\n";
                return;
            }
        }
    }

    void updateID(int id, int new_id) {
        for (int i = 0; i < count; ++i) {
            if (medicines[i].id == id) {
                medicines[i].id = new_id;
                saveInventoryToFile();
                cout << "New ID set!\n";
                return;
            }
        }
    }

    void updateName(int id, string name) {
        for (int i = 0; i < count; ++i) {
            if (medicines[i].id == id) {
                medicines[i].name = name;
                saveInventoryToFile();
                cout << "Medicine renamed!\n";
                return;
            }
        }
    }

    void updateCategory(int id, string category) {
        for (int i = 0; i < count; ++i) {
            if (medicines[i].id == id) {
                medicines[i].category = category;
                saveInventoryToFile();
                cout << "Category updated!\n";
                return;
            }
        }
    }

    void updateQuantity(int id, int q) {
        for (int i = 0; i < count; ++i) {
            if (medicines[i].id == id) {
                medicines[i].quantity = q;
                saveInventoryToFile();
                cout << "Quantity updated!\n";
                if (medicines[i].quantity < lowStockThreshold) {
                    cout << ">>> Low stock alert: ID " << medicines[i].id
                        << " has quantity " << medicines[i].quantity
                        << " < threshold " << lowStockThreshold << "\n";
                }
                return;
            }
        }
    }

    void updatePrice(int id, double p) {
        for (int i = 0; i < count; ++i) {
            if (medicines[i].id == id) {
                medicines[i].price = p;
                saveInventoryToFile();
                cout << "Price updated!\n";
                return;
            }
        }
    }

    void updateExpiry(int id, string expiry) {
        for (int i = 0; i < count; ++i) {
            if (medicines[i].id == id) {
                medicines[i].expiry = expiry;
                saveInventoryToFile();
                cout << "Expiry updated!\n";
                return;
            }
        }
    }

    void updateManufacturer(int id, string manu) {
        for (int i = 0; i < count; ++i) {
            if (medicines[i].id == id) {
                medicines[i].manufacturer = manu;
                saveInventoryToFile();
                cout << "Manufacturer updated!\n";
                return;
            }
        }
    }

    // Restock
    void restockMedicine(int id, int qty) {
        for (int i = 0; i < count; ++i) {
            if (medicines[i].id == id) {
                medicines[i] += qty;
                saveInventoryToFile();
                cout << "Medicine restocked!\n";
                if (medicines[i].quantity < lowStockThreshold) {
                    cout << ">>> Low stock alert: ID " << medicines[i].id
                        << " has quantity " << medicines[i].quantity
                        << " < threshold " << lowStockThreshold << "\n";
                }
                return;
            }
        }
    }

    // Buy single (now with customer info)
    double buyMedicine(int id, int qty, const string &customerName, const string &customerPhone) {
        for (int i = 0; i < count; ++i) {
            if (medicines[i].id == id) {
                double cost = medicines[i].totalPriceFor(qty);
                medicines[i] -= qty;
                cout << "Medicine sold!\n";
                cout << "Customer: " << customerName << " | Phone: " << customerPhone << "\n";

                int ids[1]; string names[1]; int qtys[1]; double prices[1];
                ids[0] = medicines[i].id;
                names[0] = medicines[i].name;
                qtys[0] = qty;
                prices[0] = cost;
                appendSaleLines(ids, names, qtys, prices, 1, cost, customerName, customerPhone);

                saveInventoryToFile();
                return cost;
            }
        }
    }

    // Buy multiple (with customer info)
    double buyMedicine(int ids[], int qtys[], int n, const string &customerName, const string &customerPhone) {
        double total = 0.0;

        // --- Step 1: Validation pass ---
        for (int i = 0; i < n; ++i) {
            bool found = false;
            for (int j = 0; j < count; ++j) {
                if (medicines[j].id == ids[i]) {
                    found = true;
                    break;
                }
            }
        
        }

        // --- Step 2: Execution pass ---
        string namesArr[n]; // temporary names (limit sane number) — will only use first n entries
        double pricesArr[n];
        for (int i = 0; i < n; ++i) namesArr[i] = "";
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < count; ++j) {
                if (medicines[j].id == ids[i]) {
                    double itemCost = medicines[j].totalPriceFor(qtys[i]);
                    total += itemCost;
                    namesArr[i] = medicines[j].name;
                    pricesArr[i] = itemCost;
                    medicines[j] -= qtys[i];
                    break;
                }
            }
        }

        cout << "Multiple medicines sold. Total bill: " << fixed << setprecision(2) << total << "\n";
        cout << "Customer: " << customerName << " | Phone: " << customerPhone << "\n";

        // prepare arrays for appendSaleLines
        string namesForAppend[50];
        for (int i = 0; i < n; ++i) namesForAppend[i] = namesArr[i];
        // convert namesForAppend and pricesArr into required arrays for appendSaleLines
        // appendSaleLines expects names[] as string array and prices[] as double array; we already have that.
        appendSaleLines(ids, namesForAppend, qtys, pricesArr, n, total, customerName, customerPhone);

        saveInventoryToFile();
        return total;
    }

    // Sorting
    void sortByID() {
        for (int i = 0; i < count - 1; ++i)
            for (int j = i + 1; j < count; ++j)
                if (medicines[i].id > medicines[j].id) swap(medicines[i], medicines[j]);
        saveInventoryToFile();
        cout << "Sorted by ID.\n";
    }

    void sortByName() {
        for (int i = 0; i < count - 1; ++i)
            for (int j = i + 1; j < count; ++j)
                if (medicines[i].name > medicines[j].name) swap(medicines[i], medicines[j]);
        saveInventoryToFile();
        cout << "Sorted by name.\n";
    }

    void sortByPrice() {
        for (int i = 0; i < count - 1; ++i)
            for (int j = i + 1; j < count; ++j)
                if (medicines[i].price > medicines[j].price) swap(medicines[i], medicines[j]);
        saveInventoryToFile();
        cout << "Sorted by price.\n";
    }

    void sortByQuantity() {
        for (int i = 0; i < count - 1; ++i)
            for (int j = i + 1; j < count; ++j)
                if (medicines[i].quantity > medicines[j].quantity) swap(medicines[i], medicines[j]);
        saveInventoryToFile();
        cout << "Sorted by quantity.\n";
    }

    void displayByID(int id) const {
        bool found = false;
        for (int i = 0; i < count; ++i) {
            if (medicines[i].id == id) {
                showMedicine(medicines[i]);
                found = true;
            }
        }
        if (!found) cout << "No medicines found with ID : " << id << "\n";
    }   

    void displayByCategory(const string &cat) const {
        bool found = false;
        for (int i = 0; i < count; ++i) {
            if (medicines[i].category == cat) {
                showMedicine(medicines[i]);
                found = true;
            }
        }
        if (!found) cout << "No medicines found in category: " << cat << "\n";
    }
};

int Pharmacy::lowStockThreshold = 10;

string getStoredPassword() {
        ifstream fin("admin_pass.dat");
        if (!fin.is_open()) {
            // If no password file, create one
            ofstream fout("admin_pass.dat");
            string defaultPass = "1234";
            fout << encrypt(defaultPass);
            fout.close();
            cout << "Default admin password set to 1234.\n";
            return defaultPass;
        } else {
            string encrypted;
            getline(fin, encrypted);
            fin.close();
            return decrypt(encrypted);
        }
    }

    void changeAdminPassword() {
        string oldPass, newPass, confirmPass;
        string current = getStoredPassword();

        cout << "Enter current password: ";
        cin >> oldPass;
        if (oldPass != current) {
            cout << "Incorrect current password.\n";
            return;
        }

        cout << "Enter new password: ";
        cin >> newPass;
        cout << "Confirm new password: ";
        cin >> confirmPass;

        if (newPass != confirmPass) {
            cout << "Passwords do not match.\n";
            return;
        }

        ofstream fout("admin_pass.dat", ios::trunc);
        fout << encrypt(newPass);
        fout.close();
        cout << "Admin password updated successfully.\n";
    }

// ---------- Helper UI ----------
string selectCategoryMenu() {
    int opt;
    while (true) {
        cout << "\nSelect Medicine Category:\n";
        cout << "1. Tablet\n2. Syrup\n3. Injection\n4. Capsule\n5. Ointment\n";
        cout << "Choice: ";
        if (!(cin >> opt)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue; }

        switch (opt) {
            case 1: return "Tablet";
            case 2: return "Syrup";
            case 3: return "Injection";
            case 4: return "Capsule";
            case 5: return "Ointment";
            default:
                cout << "Invalid choice. Please select 1-5.\n";
        }
    }
}

// ---------- Main ----------
int main() {
    Pharmacy ph;
    cout << "Welcome to Pharmacy Management System\n";
    cout << "Today's date: " << todayDate() << "\n";
    int choice;
    do{
        cout << "\n===== Pharmacy Management Menu =====\n";
        cout << "1. Display Medicine\n";
        cout << "2. Search Medicine \n";
        cout << "3. Buy Medicine \n";
        cout << "4. Sort Medicine\n";
        cout << "5. Admin Login \n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin>>choice;

        if(choice==1) {
            int display_choice;
            do{
                cout << "\n===== Display Medicine Menu =====\n";
                cout << "1. Display All Medicines\n";
                cout << "2. Display by ID\n";
                cout << "3. Display by Category\n";
                cout << "4. Previous\n";
                cout << "0. Main Menu\n";
                cout << "Enter choice: ";
                cin>>display_choice;

                if (display_choice == 1) {
                    ph.displayAll();
                }
                else if (display_choice == 2) {
                    int id; cout << "Enter Medicine ID to display: "; cin >> id;
                    ph.displayByID(id);
                }
                else if (display_choice == 3) {
                    string category;
                    category=selectCategoryMenu();
                    ph.displayByCategory(category);
                }
                else if (display_choice == 3) {
                    cout << "Returned to Previous Page\n";
                    break;
                }
                else if (display_choice == 0) {
                    cout << "Returning to Main Menu!\n";
                    break;
                }
                else if (display_choice != 0) {
                    cout << "Invalid option. Try again.\n";
                }
            } while(true);
        }

        else if(choice==2) {
            int search_choice;
            do{
                cout << "\n===== Search Medicine Menu =====\n";
                cout << "1. Search by ID\n";
                cout << "2. Search by Name\n";
                cout << "3. Search by Category\n";
                cout << "4. Search by Max Price\n";
                cout << "5. Previous\n";
                cout << "0. Main Menu\n";
                cout << "Enter choice: ";
                cin>>search_choice;

                if (search_choice == 1) {
                    int id; cout << "Enter Medicine ID to search: "; cin >> id;
                    ph.searchMedicineByID(id);
                }
                else if (search_choice == 2) {
                    string nm; cout << "Enter substring for Name search: "; cin >> ws; getline(cin, nm);
                    ph.searchMedicineByName(nm);
                }
                else if (search_choice == 3) {
                    string category;
                    category=selectCategoryMenu();
                    ph.searchByCategory(category);
                }
                else if (search_choice == 4) {
                    double mp;
                    cout << "Enter max price: "; cin >> mp;
                    ph.searchByMaxPrice(mp);
                }
                else if (search_choice == 5) {
                    cout << "Returned to Previous Page\n";
                    break;
                }
                else if (search_choice == 0) {
                    cout << "Returning to Main Menu!\n";
                    break;
                }
                else if (search_choice != 0) {
                    cout << "Invalid option. Try again.\n";
                }
            } while(true);
        }
        else if(choice==3) {
            int buy_choice;
            do {
                cout << "\n===== Buy Medicine Menu =====\n";
                cout << "1. Buy Single Medicine\n";
                cout << "2. Buy Multiple Medicines\n";
                cout << "3. Previous\n";
                cout << "0. Main Menu\n";
                cout << "Enter choice: ";
                cin>>buy_choice;

                if (buy_choice == 1) {
                    int id, qty; cout << "Enter Medicine ID: "; cin >> id;
                    if(!ph.matchID(id)) {
                        cout<<"Medicine not found to buy."<<endl;
                        continue;
                    }
                    cout << "Enter quantity to sell: "; cin >> qty;
                    if(qty<=0) {
                        cout<<"Quantity must be positive."<<endl;
                        continue;
                    }
                    if(!ph.enoughStock(id,qty)) {
                        cout<<"Not enough stock in inventory."<<endl;
                        continue;
                    }
                    string custName, custPhone;
                    cout << "Enter Customer Name: "; cin >> ws; getline(cin, custName);
                    cout << "Enter Customer Phone: "; cin >> ws; getline(cin, custPhone);
                    double bill = ph.buyMedicine(id, qty, custName, custPhone);
                    cout << "Bill amount: " << fixed << setprecision(2) << bill << "\n";
                }
                else if (buy_choice == 2) {
                    int n,flag=0,x=0,y=0; cout << "How many different medicines in this sale? "; cin >> n;
                    if (n <= 0) { cout << "Invalid count for multiple sell."; continue; }
                    if (n>ph.getCount()) { cout << "Not enough medicines in inventory."; continue; }
                    int *ids = new int[n];
                    int *qtys = new int[n];
                    for (int i = 0; i < n; ++i) {
                        cout << "Enter ID #" << i+1 << ": "; cin >> ids[i];
                        if(!ph.matchID(ids[i])) {
                            cout<<"Medicine not found to buy."<<endl;
                            qtys[i]=0;
                            x++;
                            if(x==n)
                                flag=1;
                            continue;
                        }
                        cout << "Enter Qty #" << i+1 << ": "; cin >> qtys[i];
                        if(qtys[i]<0) {
                            cout<<"Quantity must be positive."<<endl;
                            x++;
                            if(x==n)
                                flag=1;
                            continue;
                        }
                        if(!ph.enoughStock(ids[i],qtys[i])) {
                            cout<<"Not enough stock in inventory."<<endl;
                            x++;
                            if(x==n)
                                flag=1;
                            continue;
                        }
                    }
                    if(flag==1)
                        continue;
                    string custName, custPhone;
                    cout << "Enter Customer Name: "; cin >> ws; getline(cin, custName);
                    cout << "Enter Customer Phone: "; cin >> ws; getline(cin, custPhone);
                    double total = ph.buyMedicine(ids, qtys, n, custName, custPhone);
                    cout << "Total bill: " << fixed << setprecision(2) << total << "\n";
                    delete[] ids;
                    delete[] qtys;
                }
                else if (buy_choice == 3) {
                    cout << "Returned to Previous Page\n";
                    break;
                }
                else if (buy_choice == 0) {
                    cout << "Returning to Main Menu!\n";
                    break;
                }
                else if (buy_choice != 0) {
                    cout << "Invalid option. Try again.\n";
                }
            } while(true);
        }
        else if(choice==4) {
            int sort_choice;
            do {
                cout << "\n===== Sort Medicine Menu =====\n";
                cout << "1. Sort by ID\n";
                cout << "2. Sort by Name\n";
                cout << "3. Sort by Price\n";
                cout << "4. Sort by Quantity\n";
                cout << "5. Previous\n";
                cout << "0. Main Menu\n";
                cout << "Enter choice: ";
                cin>>sort_choice;

                if (sort_choice == 1) {
                    ph.sortByID();
                }
                else if (sort_choice == 2) {
                    ph.sortByName();
                }
                else if (sort_choice == 3) {
                    ph.sortByPrice();
                }
                else if (sort_choice == 4) {
                    ph.sortByQuantity();
                }
                else if (sort_choice == 5) {
                    cout << "Returned to Previous Page\n";
                    break;
                }
                else if (sort_choice == 0) {
                    cout << "Returning to Main Menu!\n";
                    break;
                }
                else if (sort_choice != 0) {
                    cout << "Invalid option. Try again.\n";
                }
            } while(true);
        }
        else if(choice==5) {
            string inputPass;
            string storedPass = getStoredPassword();

            cout << "Enter Admin Password: ";
            cin >> inputPass;

            if (inputPass == storedPass) {
                int admin_choice;
                do{
                    cout << "\n===== Admin Section Menu =====\n";
                    cout << "1. Add Medicine\n";
                    cout << "2. Update Medicine Details\n";
                    cout << "3. Delete Medicine\n";
                    cout << "4. Restock Medicine\n";
                    cout << "5. Set Low Stock Threshold (current: " << Pharmacy::lowStockThreshold << ")\n";
                    cout << "6. Change Admin Password\n";
                    cout << "0. Main Menu\n";
                    cout << "Enter choice: ";
                    cin>>admin_choice;

                    if (admin_choice == 1) {
                        int id, quantity; double price;
                        string name, expiry, manu, category;
                        cout << "Enter ID: "; cin >> id;
                        if(!validateID(id)) {
                            cout<<"ID must be positive."<<endl;
                            continue;
                        }
                        if(ph.duplicateID(id))
                            continue;
                        cout << "Enter Name: "; cin >> ws; getline(cin, name);
                        if(!validateName(name)) {
                            cout<<"Name cannot be empty."<<endl;
                            continue;
                        }
                        cout << "Enter Quantity: "; cin >> quantity;
                        if(!validateQuantity(quantity)) {
                            cout<<"Quantity must be positive."<<endl;
                            continue;
                        }
                        cout << "Enter Price: "; cin >> price;
                        if(!validatePrice(price)) {
                            cout<<"Price must be positive."<<endl;
                            continue;
                        }
                        cout << "Enter Expiry (YYYY-MM-DD) : "; cin >> ws; getline(cin, expiry);
                        if (!validateExpiry(expiry)) {
                            cout << "Invalid expiry format. Use YYYY-MM-DD.\n";
                            continue;
                        }
                        cout << "Enter Manufacturer: "; cin >> ws; getline(cin, manu);
                        category = selectCategoryMenu();
                        Medicine m(id, name, quantity, price, expiry, manu, category);
                        if (isExpired(expiry)) {
                            cout << "Warning: this medicine is expired. Add anyway? (y/n): ";
                            char yn; cin >> yn;
                            if (yn != 'y' && yn != 'Y') {
                                cout << "Medicine not added.\n";
                            } else {
                                ph.addMedicine(m); // allow adding expired if user insists
                            }
                        } else {
                            ph.addMedicine(m);
                        }
                    }
                    else if(admin_choice==2) {
                        int update_choice;
                        bool mainmenu=false;
                        do {
                            cout << "\n===== Update Medicine Menu =====\n";
                            cout << "1. Update Full Details\n";
                            cout << "2. Update ID\n";
                            cout << "3. Update Name\n";
                            cout << "4. Update Category\n";
                            cout << "5. Update Quantity\n";
                            cout << "6. Update Price\n";
                            cout << "7. Update Expiry\n";
                            cout << "8. Update Manufacturer\n";
                            cout << "9. Previous\n";
                            cout << "0. Main Menu\n";
                            cout << "Enter choice: ";
                            cin>>update_choice;

                            if(update_choice==1) {
                                int id; cout << "Enter ID to update: "; cin >> id;
                                if(!ph.matchID(id)) {
                                    cout<<"Medicine not found to update."<<endl;
                                    continue;
                                }
                                string name, expiry, manu, category; int qty; double price;
                                cout << "Enter new Name : "; cin >> ws; getline(cin, name);
                                cout << "Enter new Quantity: "; cin >> qty;
                                cout << "Enter new Price: "; cin >> price;
                                cout << "Enter new Expiry (YYYY-MM-DD): "; cin >> ws; getline(cin, expiry);
                                cout << "Enter new Manufacturer : "; getline(cin, manu);
                                cout << "Select new Category :\n";
                                category = selectCategoryMenu();
                                if (!validateExpiry(expiry)) {
                                    cout << "Invalid expiry format.\n";
                                    continue;
                                }
                                ph.updateFullDetails(id, name, qty, price, expiry, manu, category);
                            }
                            else if(update_choice==2) {
                                int id,new_id; cout << "Enter Medicine ID: "; cin >> id;
                                if(!ph.matchID(id)) {
                                    cout<<"Medicine not found to update."<<endl;
                                    continue;
                                }
                                cout << "Enter new ID: "; cin >> new_id;
                                if(ph.matchID(new_id)) {
                                    cout<<"New ID already exists."<<endl;
                                    continue;
                                }
                                ph.updateID(id, new_id);
                            }
                            else if(update_choice==3) {
                                int id; string name; cout << "Enter Medicine ID: "; cin >> id;
                                if(!ph.matchID(id)) {
                                    cout<<"Medicine not found to update."<<endl;
                                    continue;
                                }
                                cout << "Enter new Name: "; cin >> ws; getline(cin, name);
                                ph.updateName(id, name);
                            }
                            else if(update_choice==4) {
                                int id; string category; cout << "Enter Medicine ID: "; cin >> id;
                                if(!ph.matchID(id)) {
                                    cout<<"Medicine not found to update."<<endl;
                                    continue;
                                }
                                category = selectCategoryMenu();
                                ph.updateCategory(id, category);
                            }
                            else if(update_choice==5) {
                                int id, qty; cout << "Enter Medicine ID: "; cin >> id;
                                if(!ph.matchID(id)) {
                                    cout<<"Medicine not found to update."<<endl;
                                    continue;
                                }
                                cout << "Enter new quantity: "; cin >> qty;
                                ph.updateQuantity(id, qty);
                            }
                            else if(update_choice==6) {
                                int id; double price; cout << "Enter Medicine ID: "; cin >> id;
                                if(!ph.matchID(id)) {
                                    cout<<"Medicine not found to update."<<endl;
                                    continue;
                                }
                                cout << "Enter new price: "; cin >> price;
                                ph.updatePrice(id, price);
                            }
                            else if(update_choice==7) {
                                int id; string expiry; cout << "Enter Medicine ID: "; cin >> id;
                                if(!ph.matchID(id)) {
                                    cout<<"Medicine not found to update."<<endl;
                                    continue;
                                }
                                cout << "Enter new Expiry (YYYY-MM-DD): "; cin >> ws; getline(cin, expiry);
                                if (!validateExpiry(expiry)) {
                                    cout << "Invalid expiry format.\n";
                                    continue;
                                }
                                ph.updateExpiry(id, expiry);
                            }
                            else if(update_choice==8) {
                                int id; string manu; cout << "Enter Medicine ID: "; cin >> id;
                                if(!ph.matchID(id)) {
                                    cout<<"Medicine not found to update."<<endl;
                                    continue;
                                }
                                cout << "Enter new Manufacturer: "; cin >> ws; getline(cin, manu);
                                ph.updateManufacturer(id, manu);
                            }
                            else if (update_choice == 9) {
                                cout << "Returned to Previous Page\n";
                                break;
                            }
                            else if (update_choice == 0) {
                                cout << "Returning to Main Menu!\n";
                                mainmenu=true;
                                break;
                            }
                            else if (update_choice != 0) {
                                cout << "Invalid option. Try again.\n";
                            }
                        } while(true);
                        if(mainmenu) break;
                    }
                    else if (admin_choice == 3) {
                        int id; cout << "Enter ID to delete: "; cin >> id;
                        if(!ph.matchID(id)) {
                            cout<<"Medicine not found to delete."<<endl;
                            continue;
                        }
                        cout << "Are you sure? (y/n): "; char yn; cin >> yn;
                        if (yn == 'y' || yn == 'Y') ph.deleteMedicine(id);
                        else cout << "Delete cancelled.\n";
                    }
                    else if (admin_choice == 4) {
                        int id, qty; cout << "Enter Medicine ID: "; cin >> id;
                        if(!ph.matchID(id)) {
                            cout<<"Medicine not found to restock."<<endl;
                            continue;
                        }
                        cout << "Enter quantity to restock: "; cin >> qty;
                        if(qty<=0) {
                            cout<<"Quantity must be positive."<<endl;
                            continue;
                        }
                        ph.restockMedicine(id, qty);
                    }
                    else if (admin_choice == 5) {
                        int thr; cout << "Enter new low stock threshold: "; cin >> thr;
                        if (thr < 0) cout << "Threshold cannot be negative.\n";
                        else {
                            Pharmacy::lowStockThreshold = thr;
                            cout << "Low stock threshold set to " << Pharmacy::lowStockThreshold << "\n";
                        }
                    }
                    else if (admin_choice == 6) {
                        changeAdminPassword();
                    }
                    else if (admin_choice == 0) {
                        cout << "Returning to Main Menu!\n";
                        break;
                    }
                    else if (admin_choice != 0) {
                        cout << "Invalid option. Try again.\n";
                    }
                } while(true);
            }
            else {
                cout<<"Wrong Password"<<endl;
            }
        }
        else if (choice != 0) {
            cout << "Invalid option. Try again.\n";
        }

    } while (choice != 0);
    if(choice==0)
        cout << "Exiting. Goodbye!\n";
    return 0;
}
