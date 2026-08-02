#include <iostream>
#include <vector>

using namespace std;

void dfs(vector<vector<int>>& matrix, int r, int c) {
    int R = matrix.size();
    int C = matrix[0].size();

    matrix[r][c] = 0; // Visited

    // Check valid unvisited neighbors
    if(r > 0 && matrix[r - 1][c])       dfs(matrix, r - 1, c);   // Top
    if(c < C - 1 && matrix[r][c + 1])   dfs(matrix, r, c + 1);   // Right
    if(r < R - 1 && matrix[r + 1][c])   dfs(matrix, r + 1, c);   // Bottom
    if(c > 0 && matrix[r][c - 1])       dfs(matrix, r, c - 1);   // Left
}

int main() {
    vector<vector<int>> matrix{
        {1, 0, 0, 1, 0, 1},
        {1, 1, 1, 1, 0, 1}
	};

    int R = matrix.size();
    int C = matrix[0].size();

    int islandCount = 0;

    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            if (matrix[r][c] == 1) {
                dfs(matrix, r, c);
                islandCount++;
            }
        }
    }

    cout << islandCount;

    return 0;
}
