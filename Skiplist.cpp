#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

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
        int level = 0;
        while ((rand() % 2) == 0 && level < maxLevel) {
            level++;
        }
        return level;
    }


    void insert(T value) {
        vector<Node<T>*> update(maxLevel + 1, nullptr);
        Node<T>* current = header;

        // Traverse all levels to find the position for insertion
        for (int i = currentLevel; i >= 0; i--) {
            while (current->next[i] != nullptr && current->next[i]->value < value) {
                current = current->next[i];
            }
            update[i] = current;
        }

        current = current->next[0];

        // If the element already exists, we don't insert
        if (current != nullptr && current->value == value) {
            return;
        }

        // Create a new node with a random level
        int newLevel = randomLevel();
        if (newLevel > currentLevel) {
            for (int i = currentLevel + 1; i <= newLevel; i++) {
                update[i] = header;
            }
            currentLevel = newLevel;
        }

        // Create the new node
        Node<T>* newNode = new Node<T>(value, newLevel);

        // Update the pointers of the affected levels
        for (int i = 0; i <= newLevel; i++) {
            newNode->next[i] = update[i]->next[i];
            update[i]->next[i] = newNode;
        }
    }

    // Deletion of an element from the skip list
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

    // Searching for an element in the skip list
    bool search(T value) {
        Node<T>* current = header;
        for (int i = currentLevel; i >= 0; i--) {
            while (current->next[i] != nullptr && current->next[i]->value < value) {
                current = current->next[i];
            }
        }

        current = current->next[0];

        return current != nullptr && current->value == value;
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
    srand(time(0));

    SkipList<int> skipList(4);

    cout << "Inserting values: 5, 10, 15, 20, 25" << endl;
    skipList.insert(5);
    skipList.insert(10);
    skipList.insert(15);
    skipList.insert(20);
    skipList.insert(25);

    skipList.printList();

    cout << "Searching for 15: " << (skipList.search(15) ? "Found" : "Not Found") << endl;
    cout << "Searching for 30: " << (skipList.search(30) ? "Found" : "Not Found") << endl;

    cout << "Deleting 15" << endl;
    skipList.remove(15);

    skipList.printList();

    cout << "Searching for 15 after deletion: " << (skipList.search(15) ? "Found" : "Not Found") << endl;

    return 0;
}
