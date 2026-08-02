#include <iostream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

/*
    The Dijkstra algorithm is used to find the shortest path (with non-negative weights).
    It initializes the starting node with cost 0 and all the other nodes with infinite cost.
    It extracts from the minHeap the node with the minimum cost, adds the not yet visited adjacent nodes
    to the minHeap, if currentNodeWeight + edgeWeight < adjacentNodeWeight then it updates
    the new weight of the adjacent node and updates the parent of the adjacent node with the current node
    (edge relaxation).
    It marks the current node as visited.
    Since it visits the nodes with the lowest cost first, when a node is visited we are sure that
    its weight is the minimum possible cost to reach it.
    Therefore, if we need to find the shortest path to the target, as soon as the algorithm visits
    the target node we can stop.
*/

// Node for the minHeap
struct Node {
    int id;        // Node index
    int distance;  // Distance from the starting node
};

struct MinHeapComparator {
    bool operator()(const Node& node1, const Node& node2) const {
        return node1.distance > node2.distance; // Greater value for the minHeap
    }
};

// Function to print the shortest path
void printPath(const vector<int>& predecessor, int destination) {
    if (predecessor[destination] == -1) {
        cout << destination;
        return;
    }

    printPath(predecessor, predecessor[destination]);
    cout << " -> " << destination;
}

void dijkstra(const vector<vector<int>>& grid, int source, int destination) {

    // Initialize
    int rows = grid.size();
    int cols = grid[0].size();
    int nodes = rows * cols; // Number of nodes in the graph

    vector<int> distance(nodes, INT_MAX); // Initial distances set to infinity for all nodes
    vector<bool> visited(nodes, false);   // Set of nodes whose shortest path has already been found
    vector<int> predecessor(nodes, -1);   // To keep track of the path

    priority_queue<Node, vector<Node>, MinHeapComparator> minHeap;
    // MinHeap is used to extract the nodes to analyze first

    // Add the starting node to the queue
    distance[source] = 0;
    minHeap.push({source, 0}); // Insert the node index and distance into the minHeap

    while (!minHeap.empty()) {

        int current = minHeap.top().id; // Extract the node with minimum distance
        minHeap.pop();                  // Remove the node from the minHeap

        visited[current] = true;        // Mark the node as visited

        // If we reach the destination node, we can stop the loop
        if (current == destination)
            break;


        // Update distances of adjacent nodes

        // Top
        int neighbor = current - cols;
        if (neighbor >= 0 && !visited[neighbor]) {

            int newDistance = distance[current] + grid[neighbor / cols][neighbor % cols];

            if (newDistance < distance[neighbor]) { // If the new distance is smaller
                distance[neighbor] = newDistance;   // Update the distance
                predecessor[neighbor] = current;    // Update the predecessor
                minHeap.push({neighbor, newDistance}); // Insert the new distance into the minHeap
            }
        }


        // Right
        neighbor = current + 1;
        if ((neighbor % cols != 0) && !visited[neighbor]) {

            int newDistance = distance[current] + grid[neighbor / cols][neighbor % cols];

            if (newDistance < distance[neighbor]) { // If the new distance is smaller
                distance[neighbor] = newDistance;   // Update the distance
                predecessor[neighbor] = current;    // Update the predecessor
                minHeap.push({neighbor, newDistance}); // Insert the new distance into the minHeap
            }
        }


        // Bottom
        neighbor = current + cols;
        if (neighbor < nodes && !visited[neighbor]) {

            int newDistance = distance[current] + grid[neighbor / cols][neighbor % cols];

            if (newDistance < distance[neighbor]) { // If the new distance is smaller
                distance[neighbor] = newDistance;   // Update the distance
                predecessor[neighbor] = current;    // Update the predecessor
                minHeap.push({neighbor, newDistance}); // Insert the new distance into the minHeap
            }
        }


        // Left
        neighbor = current - 1;
        if ((neighbor >= 0) && (neighbor % cols != cols - 1) && !visited[neighbor]) {

            int newDistance = distance[current] + grid[neighbor / cols][neighbor % cols];

            if (newDistance < distance[neighbor]) { // If the new distance is smaller
                distance[neighbor] = newDistance;   // Update the distance
                predecessor[neighbor] = current;    // Update the predecessor
                minHeap.push({neighbor, newDistance}); // Insert the new distance into the minHeap
            }
        }
    }

    // Print the shortest distance from source to destination
    cout << "Shortest distance from node " << source
         << " to node " << destination
         << ": " << distance[destination] << endl;

    // Print the shortest path from source to destination
    cout << "Shortest path from node " << source
         << " to node " << destination << ": ";

    printPath(predecessor, destination);
    cout << endl;
}

int main() {
    // Example grid
    vector<vector<int>> grid = {
        {1, 3, 1, 4, 5, 9},
        {6, 0, 9, 8, 1, 4},
        {5, 7, 2, 6, 3, 2},
        {4, 8, 1, 9, 7, 6},
        {2, 5, 3, 7, 4, 8},
        {9, 1, 6, 2, 5, 3}
    };

    int startX = 1;
    int startY = 1;

    int targetX = 4;
    int targetY = 4;

    int source = startY * grid[0].size() + startX;          // Starting node
    int destination = targetY * grid[0].size() + targetX;   // Destination node

    dijkstra(grid, source, destination);

    return 0;
}