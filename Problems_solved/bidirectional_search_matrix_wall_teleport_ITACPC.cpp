#include <iostream>
#include <vector>
#include <queue>

/*
    Bidirectional search
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
    vector<vector<char>> visited(R, vector<char>(C, '0'));

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

    int path_cost_start = 0;
    int path_cost_target = 0;
    int path_cost_tot = 0;

    int nearestS_toStart = -1;
    int nearestS_toTarget = -1;

    Coord start(rStart, cStart);
    Coord target(rTarget, cTarget);

    // Dichiaro coda
    queue<Coord> queueStart;
    queue<Coord> queueTarget;

    // Aggiungo punto di partenza e arrivo
    queueStart.push(start);
    visited[start.r][start.c] = 1;

    queueTarget.push(target);
    visited[target.r][target.c] = 1;

    // Bidirectional search while entrambe le queue non sono vuote
    while(!(queueStart.empty() && queueTarget.empty())){

        // From start
        if(int size = queueStart.size()){

            for (int i = 0; i < size; i++) {
                Coord nodo = queueStart.front();
                queueStart.pop();

                if(matrix[nodo.r][nodo.c] == 'S'){

                    if (nearestS_toStart == -1)
                        nearestS_toStart = path_cost_start;
                    else{
                        path_cost_start = nearestS_toStart + 1;
                    }
                }

                // Steps
                if(nodo.c < C - 1  && matrix[nodo.r][nodo.c + 1] != '#'){

                    if(visited[nodo.r][nodo.c + 1] == '0'){

                        queueStart.push(Coord(nodo.r, nodo.c + 1));
                        visited[nodo.r][nodo.c + 1] = 'P';
                    }else if(visited[nodo.r][nodo.c + 1] == 'B'){

                        path_cost_tot = path_cost_start + path_cost_target + 1;
                        if(nearestS_toStart != -1 && nearestS_toTarget != -1 && nearestS_toStart + nearestS_toTarget + 1 < path_cost_tot)
                            cout<<nearestS_toStart + nearestS_toTarget + 1;
                        else
                            cout<<path_cost_tot;

                        return 0;
                    }

                }
                if(nodo.r < R - 1  && matrix[nodo.r + 1][nodo.c] != '#'){
                    
                    if(visited[nodo.r + 1][nodo.c] == '0'){

                        queueStart.push(Coord(nodo.r + 1, nodo.c));
                        visited[nodo.r + 1][nodo.c] = 'P';
                    }else if(visited[nodo.r + 1][nodo.c] == 'B'){

                        path_cost_tot = path_cost_start + path_cost_target + 1;
                        if(nearestS_toStart != -1 && nearestS_toTarget != -1 && nearestS_toStart + nearestS_toTarget + 1 < path_cost_tot)
                            cout<<nearestS_toStart + nearestS_toTarget + 1;
                        else
                            cout<<path_cost_tot;

                        return 0;
                    }
                }
                if(nodo.c > 0 && matrix[nodo.r][nodo.c - 1] != '#'){
                    
                    if(visited[nodo.r][nodo.c - 1] == '0'){

                        queueStart.push(Coord(nodo.r, nodo.c - 1));
                        visited[nodo.r][nodo.c - 1] = 'P';
                    }else if(visited[nodo.r][nodo.c - 1] == 'B'){

                        path_cost_tot = path_cost_start + path_cost_target + 1;
                        if(nearestS_toStart != -1 && nearestS_toTarget != -1 && nearestS_toStart + nearestS_toTarget + 1 < path_cost_tot)
                            cout<<nearestS_toStart + nearestS_toTarget + 1;
                        else
                            cout<<path_cost_tot;

                        return 0;
                    }
                }
                if(nodo.r > 0 && matrix[nodo.r - 1][nodo.c] != '#'){
                    
                    if(visited[nodo.r - 1][nodo.c] == '0'){

                        queueStart.push(Coord(nodo.r - 1, nodo.c));
                        visited[nodo.r - 1][nodo.c] = 'P';
                    }else if(visited[nodo.r - 1][nodo.c] == 'B'){
                        path_cost_tot = path_cost_start + path_cost_target + 1;
                        if(nearestS_toStart != -1 && nearestS_toTarget != -1 && nearestS_toStart + nearestS_toTarget + 1 < path_cost_tot)
                            cout<<nearestS_toStart + nearestS_toTarget + 1;
                        else
                            cout<<path_cost_tot;


                        return 0;
                    }
                }
            }
            path_cost_start++;
        }

        // From target
        if(int size = queueTarget.size()){

            for (int i = 0; i < size; i++) {
                Coord nodo = queueTarget.front();
                queueTarget.pop();

                if(matrix[nodo.r][nodo.c] == 'S'){

                    if (nearestS_toTarget == -1)
                        nearestS_toTarget = path_cost_target;
                    else{
                        path_cost_target = nearestS_toTarget + 1;
                    }
                }

                // Steps
                if (nodo.c < C - 1 && matrix[nodo.r][nodo.c + 1] != '#'){

                    if(visited[nodo.r][nodo.c + 1] == '0'){

                        queueTarget.push(Coord(nodo.r, nodo.c + 1));
                        visited[nodo.r][nodo.c + 1] = 'B';
                    }else if(visited[nodo.r][nodo.c + 1] == 'P'){

                        path_cost_tot = path_cost_start + path_cost_target + 1;
                        if(nearestS_toStart != -1 && nearestS_toTarget != -1 && nearestS_toStart + nearestS_toTarget + 1 < path_cost_tot)
                            cout<<nearestS_toStart + nearestS_toTarget + 1;
                        else
                            cout<<path_cost_tot;

                        return 0;
                    }
                }
                if (nodo.r < R - 1 && matrix[nodo.r + 1][nodo.c] != '#'){

                    if(visited[nodo.r + 1][nodo.c] == '0'){

                        queueTarget.push(Coord(nodo.r + 1, nodo.c));
                        visited[nodo.r + 1][nodo.c] = 'B';
                    }else if(visited[nodo.r + 1][nodo.c] == 'P'){

                        path_cost_tot = path_cost_start + path_cost_target + 1;
                        if(nearestS_toStart != -1 && nearestS_toTarget != -1 && nearestS_toStart + nearestS_toTarget + 1 < path_cost_tot)
                            cout<<nearestS_toStart + nearestS_toTarget + 1;
                        else
                            cout<<path_cost_tot;

                        return 0;
                    }
                }
                if (nodo.c > 0 && matrix[nodo.r][nodo.c - 1] != '#'){

                    if(visited[nodo.r][nodo.c - 1] == '0'){

                        queueTarget.push(Coord(nodo.r, nodo.c - 1));
                        visited[nodo.r][nodo.c - 1] = 'B';
                    }else if(visited[nodo.r][nodo.c - 1] == 'P'){

                        path_cost_tot = path_cost_start + path_cost_target + 1;
                        if(nearestS_toStart != -1 && nearestS_toTarget != -1 && nearestS_toStart + nearestS_toTarget + 1 < path_cost_tot)
                            cout<<nearestS_toStart + nearestS_toTarget + 1;
                        else
                            cout<<path_cost_tot;

                        return 0;
                    }
                }
                if (nodo.r > 0 && matrix[nodo.r - 1][nodo.c] != '#'){

                    if(visited[nodo.r - 1][nodo.c] == '0'){

                        queueTarget.push(Coord(nodo.r - 1, nodo.c));
                        visited[nodo.r - 1][nodo.c] = 'B';
                    }else if(visited[nodo.r - 1][nodo.c] == 'P'){

                        path_cost_tot = path_cost_start + path_cost_target + 1;
                        if(nearestS_toStart != -1 && nearestS_toTarget != -1 && nearestS_toStart + nearestS_toTarget + 1 < path_cost_tot)
                            cout<<nearestS_toStart + nearestS_toTarget + 1;
                        else
                            cout<<path_cost_tot;

                        return 0;
                    }
                }
            }
            path_cost_target++;
        }
    }

    if(nearestS_toStart != -1 && nearestS_toTarget != -1)
        cout << nearestS_toStart + nearestS_toTarget + 1;
    else
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
..#..S
#.#..#
-1

3 6
P.#..B
.S#..S
#.#..#
4


3 15
P.........B..S.
.S#............
#.#..#.........
6

*/