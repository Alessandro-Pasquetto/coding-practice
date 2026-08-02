#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Node {
    int data1;
    int data2;

    Node(int d1, int d2) : data1(d1), data2(d2) {}
};

// Returns true if 'a' has lower priority than 'b'
struct MinHeapComparatorNode {
    bool operator()(Node& a, Node& b) const{
        return a.data1 > b.data1;
    }
};

int main() {
    priority_queue<Node, vector<Node>, MinHeapComparatorNode> minHeapNode;

    minHeapNode.push(Node(10, 4));
    minHeapNode.push(Node(5, 6));
    minHeapNode.push(Node(15, 8));
    minHeapNode.push(Node(2, 23));

    while (!minHeapNode.empty()) {
        cout << minHeapNode.top().data1 << " ";
        minHeapNode.pop();
    }

    return 0;
}