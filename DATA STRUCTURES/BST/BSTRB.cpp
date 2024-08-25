#include <iostream>
#include <iomanip>

using namespace std;

// Struttura per rappresentare un nodo nell'albero rosso-nero
struct Node {
    int key;
    bool color;
    Node *left, *right, *parent;

    Node(int key) : key(key), color(1), left(nullptr), right(nullptr), parent(nullptr) {}  // Costruttore
};

// Classe per rappresentare l'albero rosso-nero
class RedBlackTree {
    private:
        Node* root;  // Radice dell'albero

        void LeftRotate(Node*&);
        void RightRotate(Node*&);
        void FixInsertViolation(Node*&);
        void FixDeleteViolation(Node*&);
        void Transplant(Node*, Node*);
        Node* MinimumByNode(Node*);
        Node* MaximumByNode(Node*);

    public:
        RedBlackTree();
        Node* Minimum();
        Node* Maximum();
        Node* Predecessor(Node*);
        Node* Successor(Node*);
        void Insert(int);
        void DeleteNode(int);
        Node* Search(int);
        void PrintTreeHelper(Node*, int);
        void PrintTree();
};

// Costruttore
RedBlackTree::RedBlackTree(){
    root = nullptr;
}

// Rotazione a sinistra
void RedBlackTree::LeftRotate(Node*& pt) {
    Node* pt_right = pt->right;

    pt->right = pt_right->left;
    if (pt->right != nullptr)
        pt->right->parent = pt;

    pt_right->parent = pt->parent;

    if (pt->parent == nullptr)
        root = pt_right;
    else if (pt == pt->parent->left)
        pt->parent->left = pt_right;
    else
        pt->parent->right = pt_right;

    pt_right->left = pt;
    pt->parent = pt_right;
}

// Rotazione a destra
void RedBlackTree::RightRotate(Node*& pt) {
    Node* pt_left = pt->left;

    pt->left = pt_left->right;
    if (pt->left != nullptr)
        pt->left->parent = pt;

    pt_left->parent = pt->parent;

    if (pt->parent == nullptr)
        root = pt_left;
    else if (pt == pt->parent->left)
        pt->parent->left = pt_left;
    else
        pt->parent->right = pt_left;

    pt_left->right = pt;
    pt->parent = pt_left;
}

// Corregge le violazioni delle proprietà dell'albero rosso-nero dopo l'inserimento
void RedBlackTree::FixInsertViolation(Node*& pt) {
    while (pt->parent->color) { // Se il genitore è rosso
        if (pt->parent == pt->parent->parent->left) {
            Node *y = pt->parent->parent->right;
            if (y->color) { // Se lo zio è rosso
                pt->parent->color = false; // Genitore diventa nero
                y->color = false; // Zio diventa nero
                pt->parent->parent->color = true; // Nonno diventa rosso
                pt = pt->parent->parent;
            } else {
                if (pt == pt->parent->right) {
                    pt = pt->parent;
                    LeftRotate(pt);
                }
                pt->parent->color = false;
                pt->parent->parent->color = true;
                RightRotate(pt->parent->parent);
            }
        } else {
            Node *y = pt->parent->parent->left;
            if (y->color) {
                pt->parent->color = false;
                y->color = false;
                pt->parent->parent->color = true;
                pt = pt->parent->parent;
            } else {
                if (pt == pt->parent->left) {
                    pt = pt->parent;
                    RightRotate(pt);
                }
                pt->parent->color = false;
                pt->parent->parent->color = true;
                LeftRotate(pt->parent->parent);
            }
        }
    }
    root->color = false;
}

// Corregge le violazioni delle proprietà dell'albero rosso-nero dopo la cancellazione
void RedBlackTree::FixDeleteViolation(Node*& x) {
    while (x != root && !x->color) {
        if (x == x->parent->left) {
            Node *w = x->parent->right;
            if (w->color) {
                w->color = false;
                x->parent->color = true;
                LeftRotate(x->parent);
                w = x->parent->right;
            }
            if (!w->left->color && !w->right->color) {
                w->color = true;
                x = x->parent;
            } else {
                if (!w->right->color) {
                    w->left->color = false;
                    w->color = true;
                    RightRotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = false;
                w->right->color = false;
                LeftRotate(x->parent);
                x = root;
            }
        } else {
            Node *w = x->parent->left;
            if (w->color) {
                w->color = false;
                x->parent->color = true;
                RightRotate(x->parent);
                w = x->parent->left;
            }
            if (!w->right->color && !w->left->color) {
                w->color = true;
                x = x->parent;
            } else {
                if (!w->left->color) {
                    w->right->color = false;
                    w->color = true;
                    LeftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = false;
                w->left->color = false;
                RightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = false;
}

// Sostituisce un sottoalbero con un altro
void RedBlackTree::Transplant(Node* u, Node* v) {
    if (u->parent == nullptr)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    if (v != nullptr)
        v->parent = u->parent;
}

// Nodo minimo a partire da un nodo
Node* RedBlackTree::MinimumByNode(Node* node){

    while(node->left != nullptr)
        node = node->left;

    return node;
}

// Nodo massimo a partire da un nodo
Node* RedBlackTree::MaximumByNode(Node* node){

    while(node->right != nullptr)
        node = node->right;

    return node;
}

// Nodo minimo
Node* RedBlackTree::Minimum(){
    Node* node = root;

    while(node->left != nullptr)
        node = node->left;

    return node;
}

// Nodo massimo
Node* RedBlackTree::Maximum(){
    Node* node = root;

    while(node->right != nullptr)
        node = node->right;

    return node;
}

Node* RedBlackTree::Predecessor(Node* x){
    if (x == nullptr) {
        return nullptr; // Se il nodo è la sentinella, restituisci la sentinella stessa
    }

    // Se il nodo ha un sottoalbero sinistro, il predecessore è il massimo di quel sottoalbero
    if (x->left != nullptr) {
        return MaximumByNode(x->left);
    }

    // Se non ha sottoalbero sinistro, bisogna risalire l'albero per trovare il predecessore
    Node *y = x->parent;
    while (y != nullptr && x == y->left) {
        x = y;
        y = y->parent;
    }
    return y;
}

Node* RedBlackTree::Successor(Node* x) {
    if (x == nullptr) {
        return nullptr; // Se il nodo è null, restituisci null
    }

    // Caso 1: Se il nodo ha un sottoalbero destro, il successore è il minimo di quel sottoalbero
    if (x->right != nullptr) {
        return MinimumByNode(x->right);
    }

    // Caso 2: Se non ha sottoalbero destro, risalire l'albero per trovare il successore
    Node* y = x->parent;
    while (y != nullptr && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}

// Inserisce un nuovo nodo nell'albero
void RedBlackTree::Insert(int key) {
    Node* pt = new Node(key);

    // Inserimento del nodo utilizzando il classico inserimento di un BST
    if (root == nullptr) {
        root = pt;
        pt->color = 0;
        return;
    }

    Node* parent = nullptr;
    Node* current = root;

    while (current != nullptr) {
        parent = current;
        if (pt->key < current->key)
            current = current->left;
        else
            current = current->right;
    }

    pt->parent = parent;

    if (pt->key < parent->key)
        parent->left = pt;
    else
        parent->right = pt;

    FixInsertViolation(pt);
}

// Rimuove un nodo dall'albero
void RedBlackTree::DeleteNode(int key) {

    Node* z = Search(key);
    if (z == nullptr) return;

    Node* y = z;
    Node* x;
    bool y_original_color = y->color;

    if (z->left == nullptr) {
        x = z->right;
        Transplant(z, z->right);
    } else if (z->right == nullptr) {
        x = z->left;
        Transplant(z, z->left);
    } else {
        y = MinimumByNode(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z)
            x->parent = y;
        else {
            Transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        Transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (y_original_color == 0)
        FixDeleteViolation(x);

    delete z;
}

Node* RedBlackTree::Search(int key) {
    Node* current = root;  // Inizia dalla radice

    while (current != nullptr) {
        if (key == current->key) {
            return current;  // La chiave è stata trovata
        } else if (key < current->key) {
            current = current->left;  // Vai al sottoalbero sinistro
        } else {
            current = current->right;  // Vai al sottoalbero destro
        }
    }

    return nullptr;  // La chiave non è stata trovata
}

// Mostra la struttura dell'albero
void RedBlackTree::PrintTreeHelper(Node* node, int indent){
    if (node != nullptr) {
        // Stampa il sottoalbero destro con indentazione
        if (node->right != nullptr) {
            PrintTreeHelper(node->right, indent + 4);
        }
        
        // Stampa il nodo corrente
        cout << setw(indent) << ' ' << node->key << (node->color == 1 ? " (R)" : " (B)") << endl;

        // Stampa il sottoalbero sinistro con indentazione
        if (node->left != nullptr) {
            PrintTreeHelper(node->left, indent + 4);
        }
    }
}

void RedBlackTree::PrintTree(){
    PrintTreeHelper(root, 0);
}


int main() {
    RedBlackTree tree;

    tree.Insert(10);
    tree.Insert(20);
    tree.Insert(30);
    cout<<"p";
    tree.Insert(15);
    tree.Insert(25);
    tree.Insert(5);

    tree.PrintTree();

    tree.DeleteNode(10);

    tree.PrintTree();


    return 0;
}
