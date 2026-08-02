#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Returns true if 'a' has lower priority than 'b'
struct MinHeapComparator {
    bool operator()(int a, int b) const {
        return a > b;
    }
};

int main() {
    priority_queue<int, vector<int>, MinHeapComparator> minHeap;

    minHeap.push(10);
    minHeap.push(5);
    minHeap.push(15);
    minHeap.push(2);

    while (!minHeap.empty()) {
        cout << minHeap.top() << " ";
        minHeap.pop();
    }

    return 0;
}