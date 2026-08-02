#include <iostream>

using namespace std;

struct Node {
    int key, data;
    Node *left, *right;

    Node(int key, int data, Node* left = nullptr, Node* right = nullptr):
        key(key), data(data), left(left), right(right) {}   
};

class BST {
private:
    Node* root;
    void deleteTree(Node* node);
    Node* remove(Node* node, int key);
    Node* minimum(Node* node);
    void printTree(Node* node);

public:
    BST();
    ~BST();
    void insert(int key, int data);
    Node* search(int key);
    void remove(int key);
    void printTree();
};

BST::BST() {
    root = nullptr;
}

BST::~BST() {
    deleteTree(root);
}

void BST::deleteTree(Node* node) {
    if(node == nullptr)
        return;

    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

void BST::insert(int key, int data) {
    if(root == nullptr) {
        root = new Node(key, data);
        return;
    }

    Node* currentNode = root;
    Node* prevNode = nullptr;

    while(currentNode != nullptr) {
        prevNode = currentNode;

        if(key < currentNode->key)
            currentNode = currentNode->left;
        else if(key > currentNode->key)
            currentNode = currentNode->right;
        else
            return;
    }
    
    if(key < prevNode->key)
        prevNode->left = new Node(key, data);
    else
        prevNode->right = new Node(key, data);
}

Node* BST::search(int key) {
    Node* currentNode = root;

    while(currentNode != nullptr && currentNode->key != key) {
        if(key < currentNode->key)
            currentNode = currentNode->left;
        else if(key > currentNode->key)
            currentNode = currentNode->right;
    }
    return currentNode;
}

void BST::remove(int key) {
    root = remove(root, key);
}

Node* BST::remove(Node* node, int key) {
    if (node == nullptr)
        return nullptr;

    if (key < node->key) {
        node->left = remove(node->left, key);
    }
    else if (key > node->key) {
        node->right = remove(node->right, key);
    }
    else {
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;
        }
        else if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }
        else {
            Node* successor = minimum(node->right);

            node->key = successor->key;
            node->data = successor->data;

            node->right = remove(node->right, successor->key);
        }
    }

    return node;
}

Node* BST::minimum(Node* node) {
    while (node->left != nullptr)
        node = node->left;

    return node;
}

void BST::printTree() {
    printTree(root);
}

void BST::printTree(Node* node) {
    if(node == nullptr)
        return;

    printTree(node->left);

    cout << node->key << endl;

    printTree(node->right);
}

int main() {
    BST bst;

    bst.insert(3, 4);
    bst.insert(1, 10);
    bst.insert(5, 20);
    bst.insert(2, 30);

    bst.printTree();

    return 0;
}