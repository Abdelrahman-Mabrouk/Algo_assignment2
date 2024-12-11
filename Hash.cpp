#include <bits/stdc++.h>
using namespace std;
//------------------------------Hashing Techniques---------------------------------
// Division Method
int divisionMethod(int key, int tableSize) {
    return key % tableSize;
}

// Multiplication Method
int multiplicationMethod(int key, int tableSize) {
    double A = 0.618033;
    return floor(tableSize * (key * A));
}

// Mid Square Method
int midSquareMethod(int key, int tableSize) {
    int squared = key * key;
    string squaredStr = to_string(squared);
    int numDigits = to_string(tableSize).length();

    int start = (squaredStr.length() - numDigits) / 2;
    string midDigits = squaredStr.substr(start, numDigits);

    return stoi(midDigits) % tableSize;
}

// Folding Method
int foldingMethod(int key, int tableSize) {
    string keyStr = to_string(key);
    int sum = 0;
    for (size_t i = 0; i < keyStr.length(); i += 2) {
        int part = stoi(keyStr.substr(i, 2)); // Take two digits at a time
        sum += part;
    }
    return sum % tableSize;
}

//---------------------------Collision Resolution Techniques-----------------------------
// Chaining Method
void chainingMethod(vector<list<int>> &hashTable, vector <int> key, int tableSize) {
    for(int k : key) {
        int index = divisionMethod(k, tableSize);
        hashTable[index].push_back(k);
    }
}

// Open Addressing Method (Linear Probing)
void openAddressingMethod(vector<int> &hashTable, vector <int> key, int tableSize) {
    for (int k: key) {
        int index = divisionMethod(k, tableSize);
        int originalIndex = index;
        while (hashTable[index] != -1) {
            index = (index + 1) % tableSize;
            if (index == originalIndex) {
                throw runtime_error("Hash table is full");
            }
        }
        hashTable[index] = k;
    }
}

// Double Hashing
void doubleHashing(vector<int> &hashTable, vector <int> key, int tableSize) {
    for (int k: key) {
        unordered_set<int>s;
        int index1 = divisionMethod(k, tableSize);
        int index2 = multiplicationMethod(k, tableSize);
        int index = index1;
        int i = 0;
        while (hashTable[index] != -1) {
            index = (index + i * index2) % tableSize;
            if(s.size()==tableSize){
                throw runtime_error("Hash table is full");
            }
            if(index>=0 && index<tableSize)s.insert(index);
            ++i;
        }
        hashTable[index] = k;
    }
}
int main() {
    const int tableSize = 10;
    vector<int>keys={1024, 56, 823, 7, 56, 9876, 214, 53, 10001, 12345};

    cout << "Division Method: " << divisionMethod(123, tableSize) << endl;
    cout << "Multiplication Method: " << multiplicationMethod(123, tableSize) << endl;
    cout << "Mid Square Method: " << midSquareMethod(123, tableSize) << endl;
    cout << "Folding Method: " << foldingMethod(123456, tableSize) << endl;

    // ---------------------------Example for Chaining Method------------------------------------------------
    vector<list<int>> hashTableChaining(tableSize);
    chainingMethod(hashTableChaining, keys, tableSize);
    cout << "-----------------------Chaining Method-----------------------\n";
    for (int i = 0; i < tableSize; ++i) {
        cout << "Index " << i << ": ";
        for (int val : hashTableChaining[i]) {
            cout << val << " ";
        }
        cout << endl;
    }

    //-------------------------Example for Open Addressing Method----------------------------------------------
    vector<int> hashTableOpenAddressing(tableSize, -1);
    openAddressingMethod(hashTableOpenAddressing, keys, tableSize);
    cout << "-------------------Open Addressing Method-----------------------\n";
    for (int i = 0; i < tableSize; ++i) {
        cout << "Index " << i << ": "<<hashTableOpenAddressing[i] << endl;
    }

    //------------------------Example for Double Hashing---------------------------------------------------------
    vector<int> hashTableDoubleHashing(tableSize, -1);
    doubleHashing(hashTableDoubleHashing,keys, tableSize);
    cout << "------------------Double Hashing-------------------------------\n";
    for (int i = 0; i < tableSize; ++i) {
        cout << "Index " << i << ": "<<hashTableDoubleHashing[i]<<endl ;
    }

    return 0;
}
