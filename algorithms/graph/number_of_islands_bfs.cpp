#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Coord{
    int r, c;
};

int main(){
    vector<vector<int> >matrix{
        {1, 0, 0, 1, 0, 1},
        {1, 1, 1, 1, 0, 1}
	};

    queue<Coord> queue;

    int R = matrix.size();
    int C = matrix[0].size();

    int islandCount = 0;

    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            if(!matrix[r][c])
                continue;

            islandCount++;

            // Set starting point
            queue.push(Coord{r, c});

            while (!queue.empty()) {
                Coord node = queue.front();
                queue.pop();

                // Check valid unvisited neighbors
                if (node.r > 0 && matrix[node.r - 1][node.c])      queue.push(Coord{node.r - 1, node.c});    // Top
                if (node.c < C - 1 && matrix[node.r][node.c + 1])  queue.push(Coord{node.r, node.c + 1});    // Right
                if (node.r < R - 1 && matrix[node.r + 1][node.c])  queue.push(Coord{node.r + 1, node.c});    // Bottom
                if (node.c > 0 && matrix[node.r][node.c - 1])      queue.push(Coord{node.r, node.c - 1});    // Left

                matrix[node.r][node.c] = 0; // Visited
            }
        }
    }

    cout << islandCount;

    return 0;
}