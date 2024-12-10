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

    void fixDeletion(Node *&root, Node *x)
    {
        if (x == nullptr)
            return;

        // If the node being deleted is red, the color of the replacement node doesn't matter
        if (x->color == 0)
        {
            return;
        }

        // If the node being replaced is black
        if (x == root)
        {
            // If x is the root, just make it black
            x->color = 1;
            return;
        }

        Node *sibling = getSibling(x);

        if (sibling == nullptr)
        {
            // If x has no sibling, fix the double black recursively
            fixDeletion(root, x->parent);
        }
        else
        {
            if (sibling->color == 0)
            {
                // Case 1: Sibling is red
                // Rotate to make sibling black
                if (x == x->parent->left)
                {
                    leftRotate(root, x->parent);
                }
                else
                {
                    rightRotate(root, x->parent);
                }
                swap(x->parent->color, sibling->color);
                fixDeletion(root, x);
            }
            else
            {
                // Case 2: Sibling is black
                if ((sibling->left == nullptr || sibling->left->color == 1) &&
                    (sibling->right == nullptr || sibling->right->color == 1))
                {
                    // Case 2a: Sibling has no red children
                    sibling->color = 0;
                    if (x->parent->color == 0)
                    {
                        x->parent->color = 1;
                    }
                    else
                    {
                        fixDeletion(root, x->parent);
                    }
                }
                else
                {
                    // Case 2b: Sibling has a red child
                    if (x == x->parent->left && (sibling->right == nullptr || sibling->right->color == 1))
                    {
                        // Left-Left case
                        rightRotate(root, sibling);
                        swap(sibling->color, sibling->left->color);
                    }
                    else if (x == x->parent->right && (sibling->left == nullptr || sibling->left->color == 1))
                    {
                        // Right-Right case
                        leftRotate(root, sibling);
                        swap(sibling->color, sibling->right->color);
                    }

                    // Recolor and rotate
                    if (x == x->parent->left)
                    {
                        leftRotate(root, x->parent);
                    }
                    else
                    {
                        rightRotate(root, x->parent);
                    }
                    x->parent->color = 1;
                    sibling->color = x->parent->color;
                    x->parent->color = 0;
                }
            }
        }
    }

    Node *getSibling(Node *node)
    {
        if (node == nullptr || node->parent == nullptr)
            return nullptr;

        if (node == node->parent->left)
            return node->parent->right;
        else
            return node->parent->left;
    }

    void transplant(Node *&root, Node *u, Node *v)
    {
        if (u->parent == nullptr)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;

        if (v != nullptr)
            v->parent = u->parent;
    }

    Node *minimum(Node *node)
    {
        while (node->left != nullptr)
            node = node->left;
        return node;
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

    void deleteNode(int key)
    {
        deleteNodeHelper(root, key);
    }

    void deleteNodeHelper(Node *&root, int key)
    {
        // Step 1: Perform standard BST deletion
        Node *z = nullptr;
        Node *x, *y;
        Node *current = root;

        while (current != nullptr)
        {
            if (current->key == key)
                z = current;
            if (current->key <= key)
                current = current->right;
            else
                current = current->left;
        }

        if (z == nullptr)
        {
            cout << "Key " << key << " not found in the tree" << endl;
            return;
        }

        y = z;
        int yOriginalColor = y->color;
        if (z->left == nullptr)
        {
            x = z->right;
            transplant(root, z, z->right);
        }
        else if (z->right == nullptr)
        {
            x = z->left;
            transplant(root, z, z->left);
        }
        else
        {
            y = minimum(z->right);
            yOriginalColor = y->color;
            x = y->right;
            if (y->parent == z)
                x->parent = y;
            else
            {
                transplant(root, y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(root, z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }

        // Step 2: Fix Red-Black tree properties if necessary
        if (yOriginalColor == 1)
            fixDeletion(root, x);

        delete z;
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

    // Test with multiple insertions and deletions
    cout << "Inserting keys: 2, 3, 4, 5, 6, 7, 10, 20, 30\n";
    int insertKeys[] = {2, 3, 4, 5, 6, 7, 10, 20, 30};
    for (int key : insertKeys)
    {
        rbt.insert(key);
        cout << "After inserting " << key << ":\n";
        rbt.printTree(rbt.getRoot());
        cout << "\n";
    }

    cout << "Deleting keys: 10, 3, 7, 5, 2, 30, 4\n";
    int deleteKeys[] = {10, 3, 7, 5, 2, 30, 4};
    for (int key : deleteKeys)
    {
        cout << "Deleting " << key << ":\n";
        rbt.deleteNode(key);
        rbt.printTree(rbt.getRoot());
        cout << "\n";
    }

    return 0;
}