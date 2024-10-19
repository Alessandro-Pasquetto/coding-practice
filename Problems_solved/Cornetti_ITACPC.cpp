#include <iostream>
#include <vector>
#include <queue>

/*

    Path cost from P to B avoid # and the cost path from S to S is 1

*/

using namespace std;

struct Coord{
    int r, c;
    Coord(int a, int b): r(a), c(b){}
};

int main()
{
    int R, C;
    cin>>R>>C;

    vector<vector<char>> matrix(R, vector<char>(C));
    vector<vector<int>> visited(R, vector<int>(C, 0));

    int rStart = 0, cStart = 0, rTarget = 0, cTarget = 0;

    // Input matrice
    for (int r = 0; r < R; r++)
    {
        for (int c = 0; c < C; c++)
        {
            cin>>matrix[r][c];

            if(matrix[r][c] == 'P'){
                rStart = r;
                cStart = c;
            }

            if(matrix[r][c] == 'B'){
                rTarget = r;
                cTarget = c;
            }
        }
    }

    int costo = 0;
    int firstS = -1;

    Coord start(rStart, cStart);
    Coord target(rTarget, cTarget);

    // Dichiaro coda
    queue<Coord> queue;

    // Setto punto di partenza
    queue.push(start);
    visited[start.r][start.c] = 1;

    // BFS from start
    while(!queue.empty()){

        int size = queue.size();

        for (int i = 0; i < size; i++) {
            Coord nodo = queue.front();
            queue.pop();

            if(matrix[nodo.r][nodo.c] == 'S'){

                if (firstS == -1)
                    firstS = costo;
                else{
                    costo = firstS + 1;
                }
            }

            if (matrix[nodo.r][nodo.c] == 'B') {
                cout << costo;
                return 0;
            }

            // Steps
            if (nodo.c < C - 1 && !visited[nodo.r][nodo.c + 1] && matrix[nodo.r][nodo.c + 1] != '#'){
                queue.push(Coord(nodo.r, nodo.c + 1));
                visited[nodo.r][nodo.c + 1] = 1;
            }
            if (nodo.r < R - 1 && !visited[nodo.r + 1][nodo.c] && matrix[nodo.r + 1][nodo.c] != '#'){
                queue.push(Coord(nodo.r + 1, nodo.c));
                visited[nodo.r + 1][nodo.c] = 1;
            }
            if (nodo.c > 0 && !visited[nodo.r][nodo.c - 1] && matrix[nodo.r][nodo.c - 1] != '#'){
                queue.push(Coord(nodo.r, nodo.c - 1));
                visited[nodo.r][nodo.c - 1] = 1;
            }
            if (nodo.r > 0 && !visited[nodo.r - 1][nodo.c] && matrix[nodo.r - 1][nodo.c] != '#'){
                queue.push(Coord(nodo.r - 1, nodo.c));
                visited[nodo.r - 1][nodo.c] = 1;
            }
        }

        costo++;
    }

    // Controllo se il bus deve passare attraverso il muro
    if(firstS != -1){
        // Setto punto di partenza
        costo = firstS + 1;

        queue.push(target);
        visited[target.r][target.c] = 1;

        // BFS from target
        while(!queue.empty()){

            int size = queue.size();

            for (int i = 0; i < size; i++) {
                
                Coord nodo = queue.front();
                queue.pop();
                

                if(matrix[nodo.r][nodo.c] == 'S'){
                    cout << costo;
                    return 0;
                }

                // Steps
                if (nodo.c < C - 1 && !visited[nodo.r][nodo.c + 1] && matrix[nodo.r][nodo.c + 1] != '#'){
                    queue.push(Coord(nodo.r, nodo.c + 1));
                    visited[nodo.r][nodo.c + 1] = 1;
                }
                if (nodo.r < R - 1 && !visited[nodo.r + 1][nodo.c] && matrix[nodo.r + 1][nodo.c] != '#'){
                    queue.push(Coord(nodo.r + 1, nodo.c));
                    visited[nodo.r + 1][nodo.c] = 1;
                }
                if (nodo.c > 0 && !visited[nodo.r][nodo.c - 1] && matrix[nodo.r][nodo.c - 1] != '#'){
                    queue.push(Coord(nodo.r, nodo.c - 1));
                    visited[nodo.r][nodo.c - 1] = 1;
                }
                if (nodo.r > 0 && !visited[nodo.r - 1][nodo.c] && matrix[nodo.r - 1][nodo.c] != '#'){
                    queue.push(Coord(nodo.r - 1, nodo.c));
                    visited[nodo.r - 1][nodo.c] = 1;
                }
            }
            
            costo++;
        }
    }else
        cout<<-1;

    return 0;
}


/*

3 6
P.#..B
..#..S
#....#
9

3 6
P.#..B
.S#..S
#.#..#
4

*/