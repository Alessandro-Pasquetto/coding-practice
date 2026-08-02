#include <iostream>
#include <vector>
#include <algorithm>

/*
    -Constraint satisfaction problem-
    Colora gli stati con i colori disponibili senza poter colorare due stati adiacenti con lo stesso colore
*/

using namespace std;

struct Node {
    int value;
    int color = -1;
    vector<Node*> adjacent;

    void addAdjacent(Node* node) {
        adjacent.push_back(node);
        node->adjacent.push_back(this);
    }
};

// Funzione ricorsiva per colorare i nodi
bool Fun(Node* node, vector<int>& availableColorsRef) {

    vector<int> availableColors = availableColorsRef;

    // Rimuovi i colori già utilizzati dai nodi adiacenti
    for (Node* n : node->adjacent) {
        availableColors.erase(remove(availableColors.begin(), availableColors.end(), n->color), availableColors.end());
    }

    // Prova a colorare il nodo con i colori disponibili
    while (!availableColors.empty()) {
        node->color = availableColors[0]; // Assegna il primo colore disponibile
        bool result = true;

        // Prova a colorare i nodi adiacenti
        for (Node* adj : node->adjacent) {
            if (adj->color == -1) { // Solo se non è ancora stato colorato
                if (!Fun(adj, availableColorsRef)) {
                    result = false;
                    break;
                }
            }
        }    

        if (result)
            return true; // Se tutti i nodi adiacenti sono stati colorati correttamente

        availableColors.erase(availableColors.begin()); // Prova il colore successivo
    }

    node->color = -1; // Resetta il colore se non ci sono colori disponibili
    return false; // Fallisce se non ci sono colori disponibili
}

int main() {
    // Esempio di creazione di nodi e adiacenze
    vector<Node*> nodes; // Vettore globale di nodi
    Node n1{1};
    Node n2{2};
    Node n3{3};
    Node n4{4};
    Node n5{5};
    Node n6{6};
    Node n7{7};

    n1.addAdjacent(&n2);
    n1.addAdjacent(&n4);
    n2.addAdjacent(&n3);
    n2.addAdjacent(&n4);
    n3.addAdjacent(&n4);
    n3.addAdjacent(&n5);
    n4.addAdjacent(&n5);
    n4.addAdjacent(&n6);

    vector<int> availableColors = {0, 1, 2};

    nodes.push_back(&n1);
    nodes.push_back(&n2);
    nodes.push_back(&n3);
    nodes.push_back(&n4);
    nodes.push_back(&n5);
    nodes.push_back(&n6);
    nodes.push_back(&n7);

    for (Node* node: nodes) {
        if(!Fun(node, availableColors)) {
            cout << "Colorazione fallita." << endl;
            return 0;
        }
    }
    
    cout << "Colorazione riuscita." << endl;
    for (Node* node : nodes)
        cout << "Nodo " << node->value << " colorato con " << node->color << endl;

    return 0;
}
