#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;

template<typename T>
struct Node {
    T value;
    vector<Node<T>*> next;

    Node(T val, int level) {
        value = val;
        next.resize(level + 1, nullptr);
    }
};

//------------------------------------ SkipList class --------------------------------------------------\\

template<typename T>
class SkipList {
private:
    int maxLevel;
    Node<T>* header;
    int currentLevel;
public:
    SkipList(int maxLvl = 16) {
        maxLevel = maxLvl;
        currentLevel = 0;
        header = new Node<T>(T(), maxLevel);  // Initialize the header node
    }

    int randomLevel() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, maxLevel);
        return dis(gen);
    }

    void insert(T value) {
        vector<Node<T>*> update(maxLevel + 1, nullptr);
        Node<T>* current = header;

        for (int i = currentLevel; i >= 0; i--) {
            while (current->next[i] != nullptr && current->next[i]->value < value) {
                current = current->next[i];
            }
            update[i] = current;
        }

        current = current->next[0];

        if (current != nullptr && current->value == value) {
            cout << "This item is Already exists, we don't insert\n";
            return;
        }

        int newLevel = randomLevel();
        if (newLevel > currentLevel) {
            for (int i = currentLevel + 1; i <= newLevel; i++) {
                update[i] = header;
            }
            currentLevel = newLevel;
        }

        Node<T>* newNode = new Node<T>(value, newLevel);

        for (int i = 0; i <= newLevel; i++) {
            newNode->next[i] = update[i]->next[i];
            update[i]->next[i] = newNode;
        }
    }

    void remove(T value) {
        vector<Node<T>*> update(maxLevel + 1, nullptr);
        Node<T>* current = header;

        // Traverse all levels to find the node to delete
        for (int i = currentLevel; i >= 0; i--) {
            while (current->next[i] != nullptr && current->next[i]->value < value) {
                current = current->next[i];
            }
            update[i] = current;
        }

        current = current->next[0];

        // If the element doesn't exist, nothing to delete
        if (current == nullptr || current->value != value) {
            cout<<"The element doesn't exist, nothing to delete";
            return;
        }

        // Update the pointers of the affected levels
        for (int i = 0; i <= currentLevel; i++) {
            if (update[i]->next[i] != current) {
                break;
            }
            update[i]->next[i] = current->next[i];
        }

        // Reduce the level if necessary
        while (currentLevel > 0 && header->next[currentLevel] == nullptr) {
            currentLevel--;
        }

        delete current;
    }

    Node<T>* search(T value) {
        Node<T>* current = header;
        for (int i = currentLevel; i >= 0; i--) {
            while (current->next[i] != nullptr && current->next[i]->value <= value) {
                current = current->next[i];
                if(current->value == value)break;
            }
            if(current->value == value)break;
        }

        // إذا كانت القيمة موجودة، نرجع النود، وإذا لم تكن موجودة نرجع nullptr
        if (current != nullptr && current->value == value) {
            return current;  // إذا تم العثور على النود
        } else {
            return nullptr;  // إذا لم يتم العثور على النود
        }
    }

    void update(T oldValue, T newValue) {
        remove(oldValue);
        insert(newValue);
    }

    void printList() {
        cout << "Skip List: " << endl;
        for (int i = currentLevel; i >= 0; i--) {
            Node<T>* current = header->next[i];
            cout << "Level " << i << ": ";
            while (current != nullptr) {
                cout << current->value << " ";
                current = current->next[i];
            }
            cout << endl;
        }
    }


};


int main() {
    SkipList<int> skipList(4);

    cout << "Inserting values: 5, 10, 15, 20, 25" << endl;
    skipList.insert(5);
    skipList.insert(10);
    skipList.insert(20);
    skipList.insert(15);

    skipList.printList();

    cout << "Searching for 15: " <<( (skipList.search(15) != nullptr) ? "Found\n" : "Not Found\n") ;
    cout<<(skipList.search(5))<<endl;
    cout << "Searching for 30: " << ( (skipList.search(15) != nullptr) ? "Found\n" : "Not Found\n")<< endl;


    skipList.update(5,12);
    skipList.printList();
    cout << "Deleting 15" << endl;
    skipList.remove(15);

    return 0;
}
