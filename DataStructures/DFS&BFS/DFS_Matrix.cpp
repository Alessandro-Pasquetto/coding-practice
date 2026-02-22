#include <stdio.h>
#include <vector>

using namespace std;

void DFS_Matrix(vector<vector<int>>&matrix, int r, int c)
{
    // Limiti della matrice
    int R = matrix.size();
    int C = matrix[0].size();



    matrix[r][c] = 0; // Visited
    printf("\nR: %d\tC:%d", r, c);

    // Controllo se esiste il nodo in quella direzione e se non è già stato visitato (1)
    if(r > 0 && matrix[r - 1][c])       DFS_Matrix(matrix, r - 1, c);   // Top
    if(c < C - 1 && matrix[r][c + 1])   DFS_Matrix(matrix, r, c + 1);   // Right
    if(r < R - 1 && matrix[r + 1][c])   DFS_Matrix(matrix, r + 1, c);   // Bottom
    if(c > 0 && matrix[r][c - 1])       DFS_Matrix(matrix, r, c - 1);   // Left

}

int main(int argc, char const *argv[])
{
    // Inizializzo matrice
    vector<vector<int> >matrix{
        {1, 0, 0, 1, 0, 1},
        {1, 1, 1, 1, 0, 1}
	};

    // Ricavo limiti matrice
    int R = matrix.size();
    int C = matrix[0].size();

    // Print delle coordinate dei blocchi delle isole di 1 nella matrice binaria
    for (int r = 0; r < R; r++)
    {
        for (int c = 0; c < C; c++)
        {
            if (matrix[r][c] == 1)
                DFS_Matrix(matrix, r, c);
        }
    }

    return 0;
}
