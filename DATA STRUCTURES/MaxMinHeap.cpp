#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/* INT */

struct MinHeapComparator {
    bool operator()(int a, int b) const {
        return a > b; // Min-heap: il valore più piccolo ha la priorità più alta
    }
};

/* NODI */

// Definizione della struttura Node
struct Node {
    int data;
    int otherData;

    Node(int d, int o) : data(d), otherData(o) {}   // Solo per inizializzare in riga
};

// Comparatore per la min-heap
struct MinHeapComparatorNode {
    bool operator()(Node& a, Node& b) const{
        return a.data > b.data; // Min-heap: il valore di data più piccolo ha la priorità più alta
    }
};

// Comparatore per la max-heap
struct MaxHeapComparatorNode {
    bool operator()(Node& a, Node& b) const{
        return a.data < b.data; // Max-heap: il valore di data più piccolo ha la priorità più alta
    }
};

/* MAIN*/

int main() {

    /* Dichiarazioni */

    priority_queue<int, vector<int>, MinHeapComparator> minHeap;
    priority_queue<int, vector<int>> maxHeap;

    // Creazione della min&max-heap utilizzando priority_queue e Min&MaxHeapComparatorNode
    priority_queue<Node, vector<Node>, MinHeapComparatorNode> minHeapNode;
    priority_queue<Node, vector<Node>, MaxHeapComparatorNode> maxHeapNode;


    /* Input */

    // Aggiungi alcuni nodi alla min-heap
    minHeap.push(10);
    minHeap.push(5);
    minHeap.push(15);
    minHeap.push(2);
    // Aggiungi alcuni nodi alla max-heap
    maxHeap.push(10);
    maxHeap.push(5);
    maxHeap.push(15);
    maxHeap.push(2);

    // Aggiungi alcuni nodi alla min-heapNode
    minHeapNode.push(Node(10, 4));
    minHeapNode.push(Node(5, 6));
    minHeapNode.push(Node(15, 8));
    minHeapNode.push(Node(2, 23));
    // Aggiungi alcuni nodi alla max-heapNode
    maxHeapNode.push(Node(10, 4));
    maxHeapNode.push(Node(5, 6));
    maxHeapNode.push(Node(15, 8));
    maxHeapNode.push(Node(2, 23));


    /* Output */

    // Stampa i dati dei nodi in ordine crescente (dal più piccolo al più grande)
    while (!minHeap.empty()) {
        cout << minHeap.top() << " ";
        minHeap.pop();
    }

    cout<<endl;
    
    // Stampa i dati dei nodi in ordine crescente (dal più piccolo al più grande)
    while (!maxHeap.empty()) {
        cout << maxHeap.top() << " ";
        maxHeap.pop();
    }

    cout<<endl;

    // Stampa i dati dei nodi in ordine crescente (dal più piccolo al più grande)
    while (!minHeapNode.empty()) {
        cout << minHeapNode.top().data << " ";
        minHeapNode.pop();
    }

    cout<<endl;

    // Stampa i dati dei nodi in ordine crescente (dal più grande al più piccolo)
    while (!maxHeapNode.empty()) {
        cout << maxHeapNode.top().data << " ";
        maxHeapNode.pop();
    }

    return 0;
}
