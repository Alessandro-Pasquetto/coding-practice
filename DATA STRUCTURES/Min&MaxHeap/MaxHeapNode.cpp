#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Node {
    int data;
    int otherData;

    Node(int d, int o) : data(d), otherData(o) {}   // Solo per inizializzare in riga
};

// Comparatore per la max-heap
struct MaxHeapComparatorNode {
    bool operator()(Node& a, Node& b) const{
        return a.data < b.data; // Max-heap: il valore di data più piccolo ha la priorità più alta
    }
};


int main(int argc, char const *argv[])
{

    priority_queue<Node, vector<Node>, MaxHeapComparatorNode> maxHeapNode;

    // Input
    maxHeapNode.push(Node(10, 4));
    maxHeapNode.push(Node(5, 6));
    maxHeapNode.push(Node(15, 8));
    maxHeapNode.push(Node(2, 23));

    // Output
    while (!maxHeapNode.empty()) {
        cout << maxHeapNode.top().data << " ";
        maxHeapNode.pop();
    }

    return 0;
}