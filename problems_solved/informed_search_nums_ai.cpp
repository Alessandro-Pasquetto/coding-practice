#include <iostream>
#include <queue>

using namespace std;

struct Node{
    int num, steps, h, k;
    bool a = 0, b = 0, c = 0;

    Node(int num, int steps, int h, bool a, bool b, bool c) {
        this->num = num;                    // Num
        this->steps = steps;                // #Steps
        this->h = h;                        // Heuristic
        this->k = h + steps;                // h + steps

        this->a = a;
        this->b = b;
        this->c = c;
    };
};

// Comparatore per la min-heap
struct MinHeapComparatorNode {
    bool operator()(Node& a, Node& b) const{
        return a.k > b.k; // Min-heap: il valore più piccolo ha la priorità più alta
    }
};

// Calcola distanza cifre tra target e num, se il numero fa parte dei babNumbers {667, 668} o se al numero ci si arriva per mezzo di una doppia mossa uguale fissa il costo a 30
int HeuristicFunction(int num, int target_int, bool mossaRipetuta) {
    if(num == 667 || num == 668)
        return 30;

    string n1_string = to_string(num);
    string n2_string = to_string(target_int);

    int h = 0;

    for (int i = 0; i< 3; i++)
        h += abs(n1_string[i] - n2_string[i]); 

    h += 30 * mossaRipetuta;

    return h;
}

int main() {
    int target_int = 777;
    int start_int = 567;

    Node startNode(start_int, 0, HeuristicFunction(start_int, target_int, 0), 0, 0, 0);

    priority_queue<Node, vector<Node>, MinHeapComparatorNode> minHeapNode;

    minHeapNode.push(startNode);

    while(!minHeapNode.empty()) {

        Node nodo = minHeapNode.top();
        minHeapNode.pop();

        cout<<"Step: "<<nodo.steps<<", Num: "<<nodo.num<<endl;

        if(nodo.num == target_int)
            break;

        int next_int = 0;
        int heuristic_int = 0;

        int decinaN = nodo.num - 100 * (nodo.num / 100);
        int unitaN = nodo.num - 110 * (nodo.num / 110);
        
        // -a
        if(nodo.num > 200) {
            next_int = nodo.num - 100;
            heuristic_int = HeuristicFunction(next_int, target_int, nodo.a);
            minHeapNode.push(Node(next_int, nodo.steps + 1, heuristic_int, 1, 0 ,0));
        }
        // +a
        if(nodo.num < 900) {
            next_int = nodo.num + 100;
            heuristic_int = HeuristicFunction(next_int, target_int, nodo.a);
            minHeapNode.push(Node(next_int, nodo.steps + 1, heuristic_int, 1, 0, 0));
        }
        // -b
        if(decinaN > 10) {
            next_int = nodo.num - 10;
            heuristic_int = HeuristicFunction(next_int, target_int, nodo.b);
            minHeapNode.push(Node(next_int, nodo.steps + 1, heuristic_int, 0, 1, 0));
        }
        // +b
        if(decinaN < 90) {
            next_int = nodo.num + 10;
            heuristic_int = HeuristicFunction(next_int, target_int, nodo.b);
            minHeapNode.push(Node(next_int, nodo.steps + 1, heuristic_int, 0, 1, 0));
        }
        // -c
        if(unitaN > 0) {
            next_int = nodo.num - 1;
            heuristic_int = HeuristicFunction(next_int, target_int, nodo.c);
            minHeapNode.push(Node(next_int, nodo.steps + 1, heuristic_int, 0, 0, 1));
        }
        // +c
        if(unitaN < 9) {
            next_int = nodo.num + 1;
            heuristic_int = HeuristicFunction(next_int, target_int, nodo.c);
            minHeapNode.push(Node(next_int, nodo.steps + 1, heuristic_int, 0, 0, 1));
        }
    }

    return 0;
}