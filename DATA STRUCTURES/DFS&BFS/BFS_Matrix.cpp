#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Coord{
    int r, c;
    Coord(int a, int b): r(a), c(b){}
};

int main(int argc, char const *argv[])
{
    // Inizializzo matrice
    vector<vector<int> >matrix{
        {1, 0, 0, 1, 0, 1},
        {1, 1, 1, 1, 0, 1}
	};

    // Dichiaro coda
    queue<Coord> queue;

    // Ricavo limiti matrice
    int R = matrix.size();
    int C = matrix[0].size();

    // Setto punto di partenza
    queue.push(Coord(0, 0));

    // Per ogni nodo a 1 nella lista controllo i nodi adiacenti
    while(!queue.empty()){

        Coord nodo = queue.front();
        queue.pop();

        if(matrix[nodo.r][nodo.c] == 1){    // Questo controllo lo posso fare prima di aggiungere un nodo alla queue (per ogni if)

            if(nodo.c < C - 1)  queue.push(Coord(nodo.r, nodo.c+1)); // Destra
            if(nodo.r < R - 1)  queue.push(Coord(nodo.r + 1, nodo.c)); // Sotto
            if(nodo.c > 0)      queue.push(Coord(nodo.r, nodo.c - 1)); // Sinistra
            if(nodo.r > 0)      queue.push(Coord(nodo.r - 1, nodo.c)); // Sopra

            matrix[nodo.r][nodo.c] = 0; // Visitato
        }
    }

    return 0;
}