#include <iostream>
#include <vector>
#include <climits>

using namespace std;

/*
    The Bellman-Ford algorithm is used to find the shortest path (also with negative weights).
    It initializes the starting node with cost 0 and all the other nodes with infinity.
    For each edge (u, v), if the distance from node u plus the weight w is smaller than the
    current distance of node v, it updates the distance of v with the new value.
*/

// Structure to represent an edge with a source, destination, and weight
struct Edge {
    int source, destination, weight;
};

// Function to print the shortest path from the source to the current node using the predecessor vector
void printPath(const vector<int>& predecessor, int node) {
    if (predecessor[node] == -1) {
        cout << node;
        return;
    }

    printPath(predecessor, predecessor[node]);
    cout << " -> " << node;
}

// Function to convert an adjacency matrix into an edge list
vector<Edge> convertToEdgeList(const vector<vector<int>>& adjacencyMatrix) {
    vector<Edge> edgeList;
    int vertices = adjacencyMatrix.size();

    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            if (adjacencyMatrix[i][j] != 0 && adjacencyMatrix[i][j] != INT_MAX) { 
                // Ignore zero or infinite weights (no edge)
                edgeList.push_back({i, j, adjacencyMatrix[i][j]});
            }
        }
    }

    return edgeList;
}

void bellmanFord(const vector<Edge>& edgeList, int vertices, int source, int destination) {
    vector<int> distance(vertices, INT_MAX);   // Initialize distances to infinity
    vector<int> predecessor(vertices, -1);     // Vector of predecessors to reconstruct paths

    distance[source] = 0; // Distance from the starting node is 0

    // Relax all edges V-1 times (if the current node weight plus the edge weight is smaller
    // than the adjacent node weight, update the new distance of the adjacent node and
    // update its predecessor with the current node)
    for (int i = 0; i < vertices - 1; ++i) {
        for (const Edge& edge : edgeList) {
            int u = edge.source;
            int v = edge.destination;
            int weight = edge.weight;

            if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                predecessor[v] = u; // Update predecessor of v
            }
        }
    }

    // Check for negative weight cycles
    for (const Edge& edge : edgeList) {
        int u = edge.source;
        int v = edge.destination;
        int weight = edge.weight;

        if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
            cout << "The graph contains a negative weight cycle" << endl;
            return;
        }
    }

    // Print the shortest distance and the shortest path from source to destination
    if (distance[destination] == INT_MAX) {
        cout << "There is no path from node " << source 
             << " to node " << destination << endl;
    } 
    else {
        cout << "Shortest distance from node " << source 
             << " to node " << destination 
             << ": " << distance[destination] << endl;

        cout << "Shortest path from node " << source 
             << " to node " << destination << ": ";

        printPath(predecessor, destination);
        cout << endl;
    }
}

int main() {
    // Example adjacency matrix
    vector<vector<int>> adjacencyMatrix = {
        {0, -1, 4, INT_MAX, INT_MAX},
        {INT_MAX, 0, 3, 2, 2},
        {INT_MAX, INT_MAX, 0, INT_MAX, INT_MAX},
        {INT_MAX, 1, 5, 0, INT_MAX},
        {INT_MAX, INT_MAX, INT_MAX, -3, 0}
    };

    /*
        Corresponding edges:

        vector<Edge> edgeList = {
            {0, 1, -1},
            {0, 2, 4},
            {1, 2, 3},
            {1, 3, 2},
            {1, 4, 2},
            {3, 1, 1},
            {3, 2, 5},
            {4, 3, -3}
        };
    */

    int vertices = adjacencyMatrix.size(); // Number of nodes in the graph
    int source = 0;                        // Starting node
    int destination = 3;                   // Destination node

    // Convert adjacency matrix into an edge list
    vector<Edge> edgeList = convertToEdgeList(adjacencyMatrix);

    // Execute the Bellman-Ford algorithm
    bellmanFord(edgeList, vertices, source, destination);

    return 0;
}