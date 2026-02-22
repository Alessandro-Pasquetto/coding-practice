#include <iostream>
#include <vector>
#include <set>

using namespace std;

class DSU {
    public:
    vector<int> parent, rank;

    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        
        // Ogni elemento è inizialmente il proprio genitore
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int Find(int x) {
        if (parent[x] != x)
            parent[x] = Find(parent[x]);
        return parent[x];
    }

    void Union_Sets(int x, int y) {
        int rootX = Find(x);
        int rootY = Find(y);

        // Se non appartengono allo stesso set
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }

    // Funzione per contare i gruppi distinti
    int CountGroups() {
        set<int> uniqueRoots;

        // Inserisce il rappresentante del set
        for (int i = 0; i < parent.size(); ++i)
            uniqueRoots.insert(Find(i));

        return uniqueRoots.size();
    }
};

int main() {
    int n = 10;  // Numero di elementi
    DSU dsu(n);

    dsu.Union_Sets(0, 1);
    dsu.Union_Sets(1, 2);
    dsu.Union_Sets(2, 3);
    dsu.Union_Sets(4, 5);
    dsu.Union_Sets(5, 6);

    cout << "Rappresentante di 3: " << dsu.Find(3) << endl;
    cout << "Rappresentante di 6: " << dsu.Find(6) << endl;

    cout << "Numero di gruppi distinti: " << dsu.CountGroups() << endl;

    return 0;
}
