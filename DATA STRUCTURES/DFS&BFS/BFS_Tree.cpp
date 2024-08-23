#include <iostream>
#include <queue>

using namespace std;

struct Node {
    int data;
    Node *left, *right;

    // Costruttore
    Node(int data, Node* left = nullptr, Node* right = nullptr):
        data(data), left(left), right(right) {}   
};

int main(int argc, char const *argv[])
{

    // Creazione di nodi
    Node* leaf1 = new Node(4);              // Nodo foglia con valore 4
    Node* leaf2 = new Node(5);              // Nodo foglia con valore 5
    Node* leaf3 = new Node(6);              // Nodo foglia con valore 6
    Node* leaf4 = new Node(7);              // Nodo foglia con valore 7

    Node* node1 = new Node(2, leaf1, leaf2);    // Nodo con valore 2, figli 4 e 5
    Node* node2 = new Node(3, leaf3, leaf4);    // Nodo con valore 3, figli 6 e 7

    Node* root = new Node(1, node1, node2); // Radice con valore 1, figli 2 e 3

    // Dichiaro coda
    queue<Node*> queue;

    // Setto punto di partenza
    queue.push(root);

    // Stampo nodi percorrendo l'albero per livelli
    while(!queue.empty()){

        Node *node = queue.front();
        queue.pop();

        if(node != nullptr){    // Questo controllo lo posso fare prima di aggiungere un nodo alla queue (per ogni if)
            cout<<node->data;
            
            queue.push(node->left);     // Left
            queue.push(node->right);    // Right
        }
    }

    return 0;
}