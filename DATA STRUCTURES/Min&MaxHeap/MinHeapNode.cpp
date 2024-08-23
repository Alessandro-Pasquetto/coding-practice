#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct MinHeapComparator {
    bool operator()(int a, int b) const {
        return a > b; // Min-heap: il valore più piccolo ha la priorità più alta
    }
};

int main(int argc, char const *argv[])
{

    priority_queue<int, vector<int>, MinHeapComparator> minHeap;

    // Input
    minHeap.push(10);
    minHeap.push(5);
    minHeap.push(15);
    minHeap.push(2);

    // Output
    while (!minHeap.empty()) {
        cout << minHeap.top() << " ";
        minHeap.pop();
    }

    return 0;
}