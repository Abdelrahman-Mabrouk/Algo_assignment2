#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int key;
    bool color; // 0 is red, 1 is black
    Node *left, *right, *parent;

    Node(int k) : key(k), color(0), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree
{
private:
    Node *root;

    void leftRotate(Node *&root, Node *x)
    {
        Node *y = x->right;
        x->right = y->left;

        if (y->left != nullptr)
            y->left->parent = x;

        y->parent = x->parent;

        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node *&root, Node *y)
    {
        Node *x = y->left;
        y->left = x->right;

        if (x->right != nullptr)
            x->right->parent = y;

        x->parent = y->parent;

        if (y->parent == nullptr)
            root = x;
        else if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;

        x->right = y;
        y->parent = x;
    }

    void fixInsertion(Node *&root, Node *node)
    {
        Node *parent = nullptr;
        Node *grandparent = nullptr;

        while (node != root && node->color == 0 && node->parent->color == 0)
        {
            parent = node->parent;
            grandparent = parent->parent;

            if (parent == grandparent->left)
            {
                Node *uncle = grandparent->right;

                // Case 1: Uncle is red - recolor
                if (uncle && uncle->color == 0)
                {
                    grandparent->color = 0; // Red
                    parent->color = 1;      // Black
                    uncle->color = 1;       // Black
                    node = grandparent;
                }
                else
                {
                    // Case 2: Uncle is black or null
                    if (node == parent->right)
                    {
                        // Left-Right case
                        leftRotate(root, parent);
                        node = parent;
                        parent = node->parent;
                    }

                    // Left-Left case
                    rightRotate(root, grandparent);
                    swap(parent->color, grandparent->color);
                    node = parent;
                }
            }
            else
            {
                // Mirror cases for right child
                Node *uncle = grandparent->left;

                // Case 1: Uncle is red - recolor
                if (uncle && uncle->color == 0)
                {
                    grandparent->color = 0; // Red
                    parent->color = 1;      // Black
                    uncle->color = 1;       // Black
                    node = grandparent;
                }
                else
                {
                    // Case 2: Uncle is black or null
                    if (node == parent->left)
                    {
                        // Right-Left case
                        rightRotate(root, parent);
                        node = parent;
                        parent = node->parent;
                    }

                    // Right-Right case
                    leftRotate(root, grandparent);
                    swap(parent->color, grandparent->color);
                    node = parent;
                }
            }
        }

        // Ensure root is always black
        root->color = 1;
    }

    void deleteTree(Node *node)
    {
        if (node == nullptr)
            return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

public:
    RedBlackTree() : root(nullptr) {}

    ~RedBlackTree()
    {
        deleteTree(root);
    }

    void insert(int key)
    {
        // First, perform standard BST insertion
        Node *newNode = new Node(key);

        // If tree is empty
        if (root == nullptr)
        {
            root = newNode;
            root->color = 1; // Root is always black
            return;
        }

        // Find insertion point
        Node *current = root;
        Node *parent = nullptr;

        while (current != nullptr)
        {
            parent = current;
            if (key < current->key)
                current = current->left;
            else if (key > current->key)
                current = current->right;
            else
                return; // Duplicate keys not allowed
        }

        // Attach the new node
        newNode->parent = parent;
        if (key < parent->key)
            parent->left = newNode;
        else
            parent->right = newNode;

        // Fix Red-Black tree properties
        fixInsertion(root, newNode);
    }

    void printTree(Node *node, string prefix = "", bool isLeft = true)
    {
        if (node == nullptr)
            return;

        // Print the right subtree first
        printTree(node->right, prefix + (isLeft ? "|   " : "    "), false);

        // Print current node
        cout << prefix;
        cout << (isLeft ? "+-- " : "\\-- ");

        // Print node key and color
        cout << node->key
             << (node->color ? "(B)" : "(R)")
             << '\n';

        // Print the left subtree
        printTree(node->left, prefix + (isLeft ? "    " : "|   "), true);
    }

    Node *getRoot() { return root; }
};

int main()
{
    RedBlackTree rbt;

    // Test with multiple insertions
    cout << "Inserting keys: 8, 18, 5, 15, 17, 25, 40, 80\n";
    int keys[] = {8, 18, 5, 15, 17, 25, 40, 80};

    for (int key : keys)
    {
        rbt.insert(key);
        cout << "After inserting " << key << ":\n";
        rbt.printTree(rbt.getRoot());
        cout << "\n";
    }

    return 0;
}