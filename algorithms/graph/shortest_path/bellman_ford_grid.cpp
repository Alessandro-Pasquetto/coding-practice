#include <iostream>
#include <vector>
#include <climits>
#include <tuple>

using namespace std;

// Function to print the shortest path
void printPath(const vector<int>& predecessor, int target) {
    if (predecessor[target] == -1) {
        cout << target;
        return;
    }

    printPath(predecessor, predecessor[target]);
    cout << " -> " << target;
}

void bellmanFord(const vector<vector<int>>& grid, int source, int destination) {
    int rows = grid.size();
    int cols = grid[0].size();
    int nodes = rows * cols; // Number of nodes in the graph

    vector<int> distance(nodes, INT_MAX); // Initial distances
    vector<int> predecessor(nodes, -1);   // Store previous nodes to reconstruct the path

    distance[source] = 0;

    // Edge list
    vector<tuple<int, int, int>> edgeList;

    // Build the edge list
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            int currentNode = row * cols + col;

            if (row > 0)
                edgeList.emplace_back(currentNode, (row - 1) * cols + col, grid[row][col]); // Edge to the top

            if (row < rows - 1)
                edgeList.emplace_back(currentNode, (row + 1) * cols + col, grid[row][col]); // Edge to the bottom

            if (col > 0)
                edgeList.emplace_back(currentNode, row * cols + (col - 1), grid[row][col]); // Edge to the left

            if (col < cols - 1)
                edgeList.emplace_back(currentNode, row * cols + (col + 1), grid[row][col]); // Edge to the right
        }
    }

    // Relaxation phase
    for (int i = 0; i < nodes - 1; i++) {
        for (const auto& [u, v, weight] : edgeList) {
            if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                predecessor[v] = u;
            }
        }
    }

    // Check for negative weight cycles
    for (const auto& [u, v, weight] : edgeList) {
        if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
            cout << "Graph contains negative weight cycles!" << endl;
            return;
        }
    }

    // Print shortest distance
    cout << "Shortest distance from node " << source
         << " to node " << destination
         << ": " << distance[destination] << endl;

    // Print shortest path
    cout << "Shortest path from node " << source
         << " to node " << destination << ": ";

    printPath(predecessor, destination);
    cout << endl;
}

int main() {
    vector<vector<int>> grid = {
        {1, 3, 1, 4, -1, 9},
        {6, 0, 9, 8, 1, 4},
        {5, 7, 2, 6, 3, 2},
        {4, 8, 1, 9, 7, 6},
        {2, -2, 3, 7, 4, 8},
        {9, 2, 6, -2, 5, 3}
    };

    int startX = 1;
    int startY = 1;

    int targetX = 4;
    int targetY = 4;

    int source = startY * grid[0].size() + startX;          // Starting node
    int destination = targetY * grid[0].size() + targetX;   // Destination node

    bellmanFord(grid, source, destination);

    return 0;
}