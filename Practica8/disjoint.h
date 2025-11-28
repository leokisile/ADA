#include <vector>
using std::vector;

struct DisjointSet {
    int n;
    vector<int> parent;
    vector<int> rankv;

    //Constructor para nodos 0 hasta n-1
    DisjointSet(int n = 0) {
        init(n);
    }

    void init(int n_) {
        n = n_;
        parent.resize(n);
        rankv.assign(n, 0);   // todos los nodos inician con rank = 0

        for (int i = 0; i < n; ++i)
            parent[i] = i;     // cada nodo es su propia raíz
    }

    // FIND con path compression
    int find(int a) {
        if (parent[a] == a) return a;
        return parent[a] = find(parent[a]);
    }

    // UNITE por RANK usando claves arbitrarias
    bool unite(int A, int B) {
        int a = find(A);
        int b = find(B);

        a = find(a);
        b = find(b);

        if (a == b) return false;

        // unión por rank
        if (rankv[a] < rankv[b]) {
            parent[a] = b;
        } else if (rankv[b] < rankv[a]) {
            parent[b] = a;
        } else {
            parent[b] = a;
            rankv[a]++;
        }

        return true;
    }

    // COmprueba si es el mismo
    bool same(int A, int B) {
        return find(A) == find(B);
    }
};
