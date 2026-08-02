#include <iostream>

using namespace std;

// Similar implementation to std::map based on a Red-Black Tree.

struct Node {
    int key;
    bool isRed;
    Node *left, *right, *parent;

    Node(int key) : key(key), isRed(true), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    Node* root;
    Node* NIL;  // Leaf node

    void deleteTree(Node* node);
    void leftRotate(Node* x);
    void rightRotate(Node* y);
    void fixInsertViolation(Node* z);
    void fixDeleteViolation(Node* x);
    void transplant(Node* u, Node* v);
    Node* minimumByNode(Node* node);
    Node* maximumByNode(Node* node);
    void printHorizontalHelper(Node* node, int indent);

public:
    RedBlackTree();
    ~RedBlackTree();
    Node* minimum();
    Node* maximum();
    Node* predecessor(Node* x);
    Node* successor(Node* x);
    void insert(int key);
    void remove(int key);
    Node* search(int key);
    void printHorizontal();
};

// Initializes RedBlackTree
RedBlackTree::RedBlackTree() {
    NIL = new Node(0);
    NIL->isRed = false;
    root = NIL;
}

RedBlackTree::~RedBlackTree() {
    deleteTree(root);
    delete NIL;
}

void RedBlackTree::deleteTree(Node* node) {
    if(node == NIL)
        return;

    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

void RedBlackTree::leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != NIL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NIL) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void RedBlackTree::rightRotate(Node* y) {
    Node* x = y->left;
    y->left = x->right;
    if (x->right != NIL) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == NIL) {
        root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
}

// Restores Red-Black Tree properties after insertion
void RedBlackTree::fixInsertViolation(Node* z) {
    while (z->parent->isRed) { // If the parent is red
        if (z->parent == z->parent->parent->left) {
            Node *y = z->parent->parent->right;
            if (y->isRed) { // If the uncle is red
                z->parent->isRed = false; // Parent becomes black
                y->isRed = false; // Uncle becomes black
                z->parent->parent->isRed = true; // Grandparent becomes red
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->isRed = false;
                z->parent->parent->isRed = true;
                rightRotate(z->parent->parent);
            }
        } else {
            Node *y = z->parent->parent->left;
            if (y->isRed) {
                z->parent->isRed = false;
                y->isRed = false;
                z->parent->parent->isRed = true;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->isRed = false;
                z->parent->parent->isRed = true;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->isRed = false;
}

// Restores Red-Black Tree properties after deletion
void RedBlackTree::fixDeleteViolation(Node* x) {
    Node* w;
    while (x != root && x->isRed == false) {
        if (x == x->parent->left) {
            w = x->parent->right;
            if (w->isRed == true) { // Case 1
                w->isRed = false;
                x->parent->isRed = true;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if (w->left->isRed == false && w->right->isRed == false) { // Case 2
                w->isRed = true;
                x = x->parent;
            } else {
                if (w->right->isRed == false) { // Case 3
                    w->left->isRed = false;
                    w->isRed = true;
                    rightRotate(w);
                    w = x->parent->right;
                }
                w->isRed = x->parent->isRed; // Case 4
                x->parent->isRed = false;
                w->right->isRed = false;
                leftRotate(x->parent);
                x = root;
            }
        } else {
            w = x->parent->left;
            if (w->isRed == true) { // Case 1
                w->isRed = false;
                x->parent->isRed = true;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            if (w->right->isRed == false && w->right->isRed == false) { // Case 2
                w->isRed = true;
                x = x->parent;
            } else {
                if (w->left->isRed == false) { // Case 3
                    w->right->isRed = false;
                    w->isRed = true;
                    leftRotate(w);
                    w = x->parent->left;
                }
                w->isRed = x->parent->isRed; // Case 4
                x->parent->isRed = false;
                w->left->isRed = false;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->isRed = false;
}

// Replaces node u with node v
void RedBlackTree::transplant(Node* u, Node* v) {
    if (u->parent == NIL) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

// Finds the minimum node starting from the given node (used in remove)
Node* RedBlackTree::minimumByNode(Node* node) {
    while (node->left != NIL) {
        node = node->left;
    }
    return node;
}

// Finds the maximum node starting from the given node
Node* RedBlackTree::maximumByNode(Node* node) {
    while (node->right != NIL) {
        node = node->right;
    }
    return node;
}

Node* RedBlackTree::minimum() {
    return minimumByNode(root);
}

Node* RedBlackTree::maximum() {
    return maximumByNode(root);
}

Node* RedBlackTree::predecessor(Node* x) {
    if (x->left != NIL) {
        return maximumByNode(x->left);
    }
    Node* y = x->parent;
    while (y != NIL && x == y->left) {
        x = y;
        y = y->parent;
    }
    return y;
}

Node* RedBlackTree::successor(Node* x) {
    if (x->right != NIL) {
        return minimumByNode(x->right);
    }
    Node* y = x->parent;
    while (y != NIL && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}

void RedBlackTree::insert(int key) {
    Node* newNodo = new Node(key);
    Node* parentNewNodo = NIL;
    Node* posNewNodo = root;

    while (posNewNodo != NIL) {
        parentNewNodo = posNewNodo;
        if (newNodo->key < posNewNodo->key) {
            posNewNodo = posNewNodo->left;
        } else {
            posNewNodo = posNewNodo->right;
        }
    }

    newNodo->parent = parentNewNodo;
    if (parentNewNodo == NIL) {
        root = newNodo;
    } else if (newNodo->key < parentNewNodo->key) {
        parentNewNodo->left = newNodo;
    } else {
        parentNewNodo->right = newNodo;
    }

    newNodo->left = NIL;
    newNodo->right = NIL;
    newNodo->isRed = true;

    fixInsertViolation(newNodo);
}

void RedBlackTree::remove(int key) {
    Node* z = search(key);

    Node* y = z;
    Node* x;
    bool yOriginalColor = y->isRed;

    if (z->left == NIL) {
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == NIL) {
        x = z->left;
        transplant(z, z->left);
    } else {
        y = minimumByNode(z->right);
        yOriginalColor = y->isRed;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->isRed = z->isRed;
    }

    if (yOriginalColor == false) {
        fixDeleteViolation(x);
    }
    delete z;
}

Node* RedBlackTree::search(int key) {
    Node* x = root;
    while (x != NIL && key != x->key) {
        if (key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    return x;
}

#include <iomanip>
// Helper function to print the Red-Black Tree with indentation
void RedBlackTree::printHorizontalHelper(Node* node, int indent) {
    // Do nothing if the node is NIL
    if (node == NIL) {
        return;
    }

    // Print the right subtree
    if (node->right != NIL) {
        printHorizontalHelper(node->right, indent + 4);
    }

    // Print the current node
    if (indent > 0) {
        cout << setw(indent) << ' ';
    }
    cout << (node->isRed ? "R" : "B") << node->key << "\n";

    // Print the left subtree
    if (node->left != NIL) {
        printHorizontalHelper(node->left, indent + 4);
    }
}

void RedBlackTree::printHorizontal() {
    cout << endl << endl;
    printHorizontalHelper(root, 0);
}

int main() {
    RedBlackTree tree;
    tree.insert(10);
    tree.insert(20);

    tree.printHorizontal();

    tree.insert(30);

    tree.printHorizontal();

    tree.insert(15);

    tree.printHorizontal();

    tree.remove(20);

    tree.printHorizontal();

    return 0;
}