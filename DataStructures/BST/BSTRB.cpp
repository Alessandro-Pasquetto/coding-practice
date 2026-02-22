#include <iostream>

using namespace std;

struct Node {
    int key;
    bool color; // true per rosso, false per nero
    Node *left, *right, *parent;

    Node(int key) : key(key), color(true), left(nullptr), right(nullptr), parent(nullptr) {}  // Costruttore
};

class RedBlackTree {
private:
    Node* root; // Radice dell'albero
    Node* NIL;  // Nodo foglia

    void LeftRotate(Node* x);
    void RightRotate(Node* y);
    void FixInsertViolation(Node* z);
    void FixDeleteViolation(Node* x);
    void Transplant(Node* u, Node* v);
    Node* MinimumByNode(Node* node);
    Node* MaximumByNode(Node* node);

public:
    RedBlackTree();
    Node* Minimum();
    Node* Maximum();
    Node* Predecessor(Node* x);
    Node* Successor(Node* x);
    void Insert(int key);
    void Delete(int key);
    Node* Search(int key);
    void PrintTreeHelper(Node* node, int indent);
    void PrintTree();
};

// Costruttore della classe RedBlackTree
RedBlackTree::RedBlackTree() {
    NIL = new Node(0);
    NIL->color = false;
    root = NIL;
}

// Funzione di rotazione a sinistra
void RedBlackTree::LeftRotate(Node* x) {

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

// Funzione di rotazione a destra
void RedBlackTree::RightRotate(Node* y) {

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

// Corregge le violazioni delle proprietà dell'albero rosso-nero dopo l'inserimento
void RedBlackTree::FixInsertViolation(Node* z) {
    while (z->parent->color) { // Se il genitore è rosso
        if (z->parent == z->parent->parent->left) {
            Node *y = z->parent->parent->right;
            if (y->color) { // Se lo zio è rosso
                z->parent->color = false; // Genitore diventa nero
                y->color = false; // Zio diventa nero
                z->parent->parent->color = true; // Nonno diventa rosso
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    LeftRotate(z);
                }
                z->parent->color = false;
                z->parent->parent->color = true;
                RightRotate(z->parent->parent);
            }
        } else {
            Node *y = z->parent->parent->left;
            if (y->color) {
                z->parent->color = false;
                y->color = false;
                z->parent->parent->color = true;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    RightRotate(z);
                }
                z->parent->color = false;
                z->parent->parent->color = true;
                LeftRotate(z->parent->parent);
            }
        }
    }
    root->color = false;
}

// Corregge le violazioni delle proprietà dell'albero rosso-nero dopo la cancellazione
void RedBlackTree::FixDeleteViolation(Node* x) {
    Node* w;
    while (x != root && x->color == false) {
        if (x == x->parent->left) {
            w = x->parent->right;
            if (w->color == true) { // Caso 1
                w->color = false;
                x->parent->color = true;
                LeftRotate(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == false && w->right->color == false) { // Caso 2
                w->color = true;
                x = x->parent;
            } else {
                if (w->right->color == false) { // Caso 3
                    w->left->color = false;
                    w->color = true;
                    RightRotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color; // Caso 4
                x->parent->color = false;
                w->right->color = false;
                LeftRotate(x->parent);
                x = root;
            }
        } else {
            w = x->parent->left;
            if (w->color == true) { // Caso 1
                w->color = false;
                x->parent->color = true;
                RightRotate(x->parent);
                w = x->parent->left;
            }
            if (w->right->color == false && w->right->color == false) { // Caso 2
                w->color = true;
                x = x->parent;
            } else {
                if (w->left->color == false) { // Caso 3
                    w->right->color = false;
                    w->color = true;
                    LeftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color; // Caso 4
                x->parent->color = false;
                w->left->color = false;
                RightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = false;
}

// Sostituisce il nodo u con il nodo v
void RedBlackTree::Transplant(Node* u, Node* v) {
    if (u->parent == NIL) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

// Trova il nodo minimo a partire dal nodo dato (serve nel delete)
Node* RedBlackTree::MinimumByNode(Node* node) {
    while (node->left != NIL) {
        node = node->left;
    }
    return node;
}

// Trova il nodo massimo a partire dal nodo dato
Node* RedBlackTree::MaximumByNode(Node* node) {
    while (node->right != NIL) {
        node = node->right;
    }
    return node;
}

// Restituisce il nodo minimo dell'albero
Node* RedBlackTree::Minimum() {
    return MinimumByNode(root);
}

// Restituisce il nodo massimo dell'albero
Node* RedBlackTree::Maximum() {
    return MaximumByNode(root);
}

// Trova il predecessore del nodo dato
Node* RedBlackTree::Predecessor(Node* x) {
    if (x->left != NIL) {
        return MaximumByNode(x->left);
    }
    Node* y = x->parent;
    while (y != NIL && x == y->left) {
        x = y;
        y = y->parent;
    }
    return y;
}

// Trova il successore del nodo dato
Node* RedBlackTree::Successor(Node* x) {
    if (x->right != NIL) {
        return MinimumByNode(x->right);
    }
    Node* y = x->parent;
    while (y != NIL && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}

// Inserisce un nuovo nodo nell'albero
void RedBlackTree::Insert(int key) {
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
    newNodo->color = true;

    FixInsertViolation(newNodo);
}

// Elimina un nodo con una chiave specifica
void RedBlackTree::Delete(int key) {
    Node* z = Search(key);

    Node* y = z;
    Node* x;
    bool yOriginalColor = y->color;

    if (z->left == NIL) {
        x = z->right;
        Transplant(z, z->right);
    } else if (z->right == NIL) {
        x = z->left;
        Transplant(z, z->left);
    } else {
        y = MinimumByNode(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            Transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        Transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (yOriginalColor == false) {
        FixDeleteViolation(x);
    }
    delete z;
}

// Cerca un nodo con una chiave specifica
Node* RedBlackTree::Search(int key) {
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
// Funzione per stampare l'albero rosso-nero con un'indentazione
void RedBlackTree::PrintTreeHelper(Node* node, int indent) {
    
    if (node == NIL) {
        return; // Non fare nulla se il nodo è NIL
    }

    // Stampa il sottoalbero destro
    if (node->right != NIL) {
        PrintTreeHelper(node->right, indent + 4);
    }

    // Stampa il nodo corrente
    if (indent > 0) {
        std::cout << std::setw(indent) << ' ';
    }
    std::cout << (node->color ? "R" : "B") << node->key << "\n";

    // Stampa il sottoalbero sinistro
    if (node->left != NIL) {
        PrintTreeHelper(node->left, indent + 4);
    }
}

// Stampa l'intero albero
void RedBlackTree::PrintTree() {
    cout<<endl<<endl;
    PrintTreeHelper(root, 0);
}

int main() {


    RedBlackTree tree;
    tree.Insert(10);
    tree.Insert(20);

    tree.PrintTree();

    tree.Insert(30);

    tree.PrintTree();

    tree.Insert(15);

    tree.PrintTree();

    tree.Delete(20);

    tree.PrintTree();

    return 0;
}