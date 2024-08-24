#include <iostream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

/*
    L'algoritmo dijikstra serve per trovare il cammino con peso minimo (pesi non negativi).
    Inizializza per il nodo di partenza un costo 0 e per tutti gli altri un costo infinito
    Estrae dal minHeap il nodo con costo minimo, aggiunge i nodi adiacenti non ancora visitati al minHeapPeso,
    se pesoNodoCorrente + pesoArco < pesoNodoAdiacente allora aggiorna il nuovo peso sul nodo adiacente e aggiorna
    il parent del nodo adiacente con nodoCorrente (Relax arco).
    Segna come visitato il nodoCorrente.
    Dato che visito prima i nodi a costo minimo quando visito un nodo sono certo che il peso che ha è il minimo per raggiungerlo
    Quindi se devo trovare il cammino minimo per arrivare al target appena l'algotimo visita il nodo target posso fermarmi.
*/

// Nodo per il minHeap
struct Node {
    int index;    // Indice del nodo
    int distance; // Distanza dal nodo di partenza
};

struct MinHeapComparator {
    bool operator()(const Node& node1, const Node& node2) const {
        return node1.distance > node2.distance;     // Maggiore per il minHeap
    }
};

// Funzione per stampare il percorso minimo
void PrintPath(const vector<int>& parent, int target) {
    if (parent[target] == -1) {
        cout << target;
        return;
    }

    PrintPath(parent, parent[target]);
    cout << " -> " << target;
}

void Dijkstra(const vector<vector<int>>& matrix, int start, int target) {

    // Inizializzo
    int R = matrix.size();
    int C = matrix[0].size();
    int V = R * C;   // Numero di nodi nel grafo
    vector<int> dist(V, INT_MAX);               // Distanze iniziali infinite per tutti i nodi
    vector<bool> visited(V, false);             // Set di nodi per cui è già stato trovato il percorso più breve
    vector<int> parent(V, -1);                  // Per tenere traccia del percorso

    
    priority_queue<Node, vector<Node>, MinHeapComparator> minHeap;  // MinHeap serve per estrarre i nodi da analizzare prima

    // Aggiungo il nodo di partenza alla coda
    dist[start] = 0;
    minHeap.push({start, 0});           // Inserisci l'indice del nodo e la distanza nel minHeap

    while (!minHeap.empty()) {

        int u = minHeap.top().index;    // Estrai il nodo con la distanza minima
        minHeap.pop();                  // Rimuovi il nodo dal minHeap

        visited[u] = true;              // Marca il nodo come visitato

        // Se raggiungiamo il nodo target, possiamo interrompere il ciclo
        if (u == target)
            break;

        // Aggiorna le distanze dei nodi adiacenti
        // Top
        int v = u - C;
        if(v >= R && !visited[v]){

            int newDist = dist[u] + matrix[v / C][v % C];

            if (newDist < dist[v]) {                // Se la nuova distanza è minore
                dist[v] = newDist;                  // Aggiorna la distanza
                parent[v] = u;                      // Aggiorna il parent
                minHeap.push({v, newDist});         // Inserisci la nuova distanza nel minHeap
            }
        }

        // Right
        v = u + 1;
        if(((v + 1) % C != 0) && !visited[v]){

            int newDist = dist[u] + matrix[v / C][v % C];

            if (newDist < dist[v]) {                // Se la nuova distanza è minore
                dist[v] = newDist;                  // Aggiorna la distanza
                parent[v] = u;                      // Aggiorna il parent
                minHeap.push({v, newDist});         // Inserisci la nuova distanza nel minHeap
            }
        }

        // Bot
        v = u + C;
        if(v < (V - C) && !visited[v]){

            int newDist = dist[u] + matrix[v / C][v % C];

            if (newDist < dist[v]) {                // Se la nuova distanza è minore
                dist[v] = newDist;                  // Aggiorna la distanza
                parent[v] = u;                      // Aggiorna il parent
                minHeap.push({v, newDist});         // Inserisci la nuova distanza nel minHeap
            }
        }

        // Left
        v = u - 1;
        if((v % C != 0) && !visited[v]){

            int newDist = dist[u] + matrix[v / C][v % C];

            if (newDist < dist[v]) {                // Se la nuova distanza è minore
                dist[v] = newDist;                  // Aggiorna la distanza
                parent[v] = u;                      // Aggiorna il parent
                minHeap.push({v, newDist});         // Inserisci la nuova distanza nel minHeap
            }
        }
    }

    // Stampa la distanza minima dal nodo start al nodo target
    cout << "Distanza minima dal nodo " << start << " al nodo " << target << " : " << dist[target] << endl;

    // Stampa il percorso minimo dal nodo start al nodo target
    cout << "Percorso minimo dal nodo " << start << " al nodo " << target << " : ";
    PrintPath(parent, target);
    cout << endl;
}

int main() {

    vector<vector<int>> matrix = {
        {1, 3, 1, 4, 5, 9},
        {6, 0, 9, 8, 1, 4},
        {5, 7, 2, 6, 3, 2},
        {4, 8, 1, 9, 7, 6},
        {2, 5, 3, 7, 4, 8},
        {9, 1, 6, 2, 5, 3}
    };

    int xStart = 1, yStart = 1;
    int xTarget = 4, yTarget = 4;

    int start = yStart * matrix[0].size() + xStart;     // Nodo di partenza
    int target = yTarget * matrix[0].size() + xTarget;  // Nodo di arrivo

    Dijkstra(matrix, start, target);

    return 0;
}
