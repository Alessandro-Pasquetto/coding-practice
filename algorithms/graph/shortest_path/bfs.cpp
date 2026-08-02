#include <iostream>
#include <vector>
#include <queue>

/*
    Path cost from S to T avoid #
*/

using namespace std;

struct Coord{
    int r, c;
};

int main() {
    int R, C;
    cin >> R >> C;

    vector<vector<char>> matrix(R, vector<char>(C));
    vector<vector<int>> visited(R, vector<int>(C, 0));

    int rStart = 0, cStart = 0;

    // Matrix input
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            cin>>matrix[r][c];

            if(matrix[r][c] == 'S') {
                rStart = r;
                cStart = c;
            }
        }
    }

    int cost = 0;

    Coord start{rStart, cStart};

    queue<Coord> queue;

    queue.push(start);
    visited[start.r][start.c] = 1;

    // BFS from start
    while(!queue.empty()) {
        int levelSize = queue.size();

        for (int i = 0; i < levelSize; i++) {
            Coord nodo = queue.front();
            queue.pop();

            if (matrix[nodo.r][nodo.c] == 'T') {
                cout << cost;
                return 0;
            }

            // Steps
            if (nodo.c < C - 1 && !visited[nodo.r][nodo.c + 1] && matrix[nodo.r][nodo.c + 1] != '#') {
                queue.push(Coord{nodo.r, nodo.c + 1});
                visited[nodo.r][nodo.c + 1] = 1;
            }
            if (nodo.r < R - 1 && !visited[nodo.r + 1][nodo.c] && matrix[nodo.r + 1][nodo.c] != '#') {
                queue.push(Coord{nodo.r + 1, nodo.c});
                visited[nodo.r + 1][nodo.c] = 1;
            }
            if (nodo.c > 0 && !visited[nodo.r][nodo.c - 1] && matrix[nodo.r][nodo.c - 1] != '#') {
                queue.push(Coord{nodo.r, nodo.c - 1});
                visited[nodo.r][nodo.c - 1] = 1;
            }
            if (nodo.r > 0 && !visited[nodo.r - 1][nodo.c] && matrix[nodo.r - 1][nodo.c] != '#') {
                queue.push(Coord{nodo.r - 1, nodo.c});
                visited[nodo.r - 1][nodo.c] = 1;
            }
        }

        cost++;
    }

    cout << -1;

    return 0;
}

/*
3 6
S.#..T
..#...
#....#
9
*/