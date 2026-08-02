#include <iostream>
#include <vector>
#include <set>

using namespace std;

class DSU {
public:
    vector<int> parent;
    vector<int> rank;

    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);

        // Initially, each element is its own parent
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x) {
        // Path compression: make every node point directly to the root
        if (parent[x] != x)
            parent[x] = find(parent[x]);

        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        // If are already in the same set
        if (rootX == rootY)
            return;

        // Union by rank: attach the smaller tree under the larger one
        if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        }
        else if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        }
        else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }

    int countGroups() {
        set<int> uniqueRoots;

        // Count distinct representatives of all sets
        for (size_t i = 0; i < parent.size(); i++)
            uniqueRoots.insert(find(i));

        return uniqueRoots.size();
    }
};

int main() {
    int n = 10; // Number of elements

    DSU dsu(n);

    dsu.unite(0, 1);
    dsu.unite(1, 2);
    dsu.unite(2, 3);

    dsu.unite(4, 5);
    dsu.unite(5, 6);

    cout << "Representative of 3: " << dsu.find(3) << endl;
    cout << "Representative of 6: " << dsu.find(6) << endl;

    cout << "Number of distinct groups: " << dsu.countGroups() << endl;

    return 0;
}