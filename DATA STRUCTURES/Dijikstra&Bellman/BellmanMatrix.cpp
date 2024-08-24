#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Funzione per stampare il percorso minimo
void PrintPath(const vector<int>& parent, int target) {
    if (parent[target] == -1) {
        cout << target;
        return;
    }

    PrintPath(parent, parent[target]);
    cout << " -> " << target;
}

void BellmanFord(const vector<vector<int>>& matrix, int start, int target) {
    int R = matrix.size();
    int C = matrix[0].size();
    int V = R * C; // Numero di nodi nel grafo

    vector<int> dist(V, INT_MAX);   // Distanze iniziali
    vector<int> parent(V, -1);      // Per tenere traccia del percorso

    dist[start] = 0;

    // Lista degli archi
    vector<tuple<int, int, int>> edges;

    // Costruisci la lista degli archi
    for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
            int u = r * C + c;
            if (r > 0) edges.emplace_back(u, (r - 1) * C + c, matrix[r][c]); // Arco verso sopra
            if (r < R - 1) edges.emplace_back(u, (r + 1) * C + c, matrix[r][c]); // Arco verso sotto
            if (c > 0) edges.emplace_back(u, r * C + (c - 1), matrix[r][c]); // Arco verso sinistra
            if (c < C - 1) edges.emplace_back(u, r * C + (c + 1), matrix[r][c]); // Arco verso destra
        }
    }

    // Fase di rilassamento
    for (int i = 0; i < V - 1; ++i) {
        for (const auto& [u, v, weight] : edges) {
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
            }
        }
    }

    // Controlla cicli negativi
    for (const auto& [u, v, weight] : edges) {
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            cout << "Il grafo contiene cicli negativi!" << endl;
            return;
        }
    }

    // Stampa la distanza minima
    cout << "Distanza minima dal nodo " << start << " al nodo " << target << " : " << dist[target] << endl;

    // Stampa il percorso minimo
    cout << "Percorso minimo dal nodo " << start << " al nodo " << target << " : ";
    PrintPath(parent, target);
    cout << endl;
}

int main() {
    vector<vector<int>> matrix = {
        {1, 3, 1, 4, -2, 9},
        {6, 0, 9, 8, 1, 4},
        {5, 7, 2, 6, 3, 2},
        {4, 8, 1, 9, 7, 6},
        {2, -3, 3, 7, 4, 8},
        {9, 1, 6, -2, 5, 3}
    };

    int xStart = 1, yStart = 1;
    int xTarget = 4, yTarget = 4;

    int start = yStart * matrix[0].size() + xStart; // Nodo di partenza
    int target = yTarget * matrix[0].size() + xTarget; // Nodo di arrivo

    BellmanFord(matrix, start, target);

    return 0;
}
