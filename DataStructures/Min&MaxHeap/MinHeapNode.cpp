#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Node {
    int data;
    int otherData;

    Node(int d, int o) : data(d), otherData(o) {}   // Solo per inizializzare in riga
};

// Comparatore per la min-heap
struct MinHeapComparatorNode {
    bool operator()(Node& a, Node& b) const{
        return a.data > b.data; // Min-heap: il valore più piccolo ha la priorità più alta
    }
};

int main(){

    priority_queue<Node, vector<Node>, MinHeapComparatorNode> minHeapNode;

    // Input
    minHeapNode.push(Node(10, 4));
    minHeapNode.push(Node(5, 6));
    minHeapNode.push(Node(15, 8));
    minHeapNode.push(Node(2, 23));

    // Output
    while (!minHeapNode.empty()) {
        cout << minHeapNode.top().data << " ";
        minHeapNode.pop();
    }

    return 0;
}