#include <iostream>
#include <vector>
#include <climits>

using namespace std;

/*
    L'algoritmo bellman serve per trovare il cammino con peso minimo (anche con pesi negativi).
    Inizializza per il nodo di partenza un costo 0 e per tutti gli altri un costo infinito.
    Per ogni arco (u, v) se la distanza da un nodo nodo u più il peso w è minore della distanza
    corrente al nodo v, aggiorna la distanza a v con il nuovo valore.
*/

// Struttura per rappresentare un arco con un'origine, una destinazione e un peso
struct Edge {
    int src, dest, weight;
};

// Funzione per stampare il percorso minimo da start a nodo corrente usando il vettore parent
void PrintPath(const vector<int>& parent, int j) {
    if (parent[j] == -1) {
        cout << j;
        return;
    }
    PrintPath(parent, parent[j]);
    cout << " -> " << j;
}

// Funzione per convertire una matrice di adiacenza in una lista di archi
vector<Edge> ConvertToEdges(const vector<vector<int>>& graphAdj) {
    vector<Edge> edges;
    int V = graphAdj.size();

    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (graphAdj[i][j] != 0 && graphAdj[i][j] != INT_MAX) { // Ignora peso zero o infinito (nessun arco)
                edges.push_back({i, j, graphAdj[i][j]});
            }
        }
    }

    return edges;
}

void BellmanFord(const vector<Edge>& edges, int V, int start, int target) {
    vector<int> dist(V, INT_MAX); // Inizializza le distanze a infinito
    vector<int> parent(V, -1);    // Vettore dei predecessori per tracciare i percorsi

    dist[start] = 0; // La distanza dal nodo di partenza è 0

    // Relaxa tutti gli archi V-1 volte (se pesoNodoCorrente + pesoArco < pesoNodoAdiacente allora
    // aggiorna il nuovo peso sul nodo adiacente e aggiorna il parent del nodo adiacente con nodoCorrente)
    for (int i = 0; i < V - 1; ++i) {
        for (const Edge& edge : edges) {
            int u = edge.src;
            int v = edge.dest;
            int weight = edge.weight;

            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;  // Aggiorna il predecessore di v
            }
        }
    }

    // Controllo dei cicli di peso negativo
    for (const Edge& edge : edges) {
        int u = edge.src;
        int v = edge.dest;
        int weight = edge.weight;

        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            cout << "Il grafo contiene un ciclo di peso negativo" << endl;
            return;
        }
    }

    // Stampa della distanza minima e del percorso minimo dal nodo start al nodo target
    if (dist[target] == INT_MAX) {
        cout << "Non esiste un percorso dal nodo " << start << " al nodo " << target << endl;
    } else {
        cout << "Distanza minima dal nodo " << start << " al nodo " << target << " : " << dist[target] << endl;
        cout << "Percorso minimo dal nodo " << start << " al nodo " << target << " : ";
        PrintPath(parent, target);
        cout << endl;
    }
}

int main() {
    // Matrice di adiacenza di esempio
    vector<vector<int>> graphAdj = {
        {0, -1, 4, INT_MAX, INT_MAX},
        {INT_MAX, 0, 3, 2, 2},
        {INT_MAX, INT_MAX, 0, INT_MAX, INT_MAX},
        {INT_MAX, 1, 5, 0, INT_MAX},
        {INT_MAX, INT_MAX, INT_MAX, -3, 0}
    };

    /*  Corrispettivi edges
    
    vector<Edge> edges = {
        {0, 1, -1},
        {0, 2, 4},
        {1, 2, 3},
        {1, 3, 2},
        {1, 4, 2},
        {3, 1, 1},
        {3, 2, 5},
        {4, 3, -3}
    };
    */

    int V = graphAdj.size(); // Numero di nodi nel grafo
    int start = 0; // Nodo di partenza
    int target = 3; // Nodo di destinazione

    // Converte la matrice di adiacenza in una lista di archi
    vector<Edge> edges = ConvertToEdges(graphAdj);

    // Esegue l'algoritmo di Bellman-Ford
    BellmanFord(edges, V, start, target);

    return 0;
}