#include <iostream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

/*
    The Dijkstra algorithm is used to find the shortest path (with non-negative weights).
    It initializes the starting node with cost 0 and all the other nodes with infinite cost.
    It extracts from the minHeap the node with the minimum cost, adds the adjacent nodes not yet visited
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
        return node1.distance > node2.distance; // Greater value for minHeap
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

void dijkstra(const vector<vector<int>>& adjacencyMatrix, int source, int destination) {
    // Initialize
    int vertices = adjacencyMatrix.size();              // Number of nodes in the graph
    vector<int> distance(vertices, INT_MAX);            // Initial distances set to infinity
    vector<bool> visited(vertices, false);               // Set of nodes whose shortest path has already been found
    vector<int> predecessor(vertices, -1);              // To keep track of the path

    priority_queue<Node, vector<Node>, MinHeapComparator> minHeap; 
    // MinHeap is used to extract the nodes to analyze first

    // Add the starting node to the queue
    distance[source] = 0;
    minHeap.push({source, 0}); // Insert the node index and distance into the minHeap

    while (!minHeap.empty()) {
        int current = minHeap.top().id; // Extract the node with the minimum distance
        minHeap.pop();                  // Remove the node from the minHeap

        visited[current] = true;        // Mark the node as visited

        // If we reach the destination node, we can stop the loop
        if (current == destination)
            break;

        // Update the distances of adjacent nodes
        for (int neighbor = 0; neighbor < vertices; neighbor++) {

            // Check if an edge exists and if the node has not been visited
            if (adjacencyMatrix[current][neighbor] && !visited[neighbor]) {

                int newDistance = distance[current] + adjacencyMatrix[current][neighbor];

                if (newDistance < distance[neighbor]) {
                    distance[neighbor] = newDistance;     // Update the distance
                    predecessor[neighbor] = current;      // Update the predecessor
                    minHeap.push({neighbor, newDistance}); // Insert the new distance into the minHeap
                }
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
    // Example adjacency matrix
    vector<vector<int>> adjacencyMatrix = {
        {0, 10, 0, 0, 5},
        {0, 0, 1, 0, 2},
        {0, 0, 0, 4, 0},
        {7, 0, 6, 0, 0},
        {0, 3, 9, 2, 0}
    };

    int source = 0;       // Starting node
    int destination = 3;  // Destination node

    dijkstra(adjacencyMatrix, source, destination);

    return 0;
}