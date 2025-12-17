#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n = 5;
    vector<int> valores = {1, 3, 4};

    // memo[i] -> todas las combinaciones que suman i
    vector<vector<vector<int>>> memo(n + 1);

    // Caso base: n = 0
    memo[0].push_back({});

    // Llenar memo
    for (int i = 1; i <= n; i++) {
        for (int v : valores) {
            if (i - v >= 0) {
                for (auto comb : memo[i - v]) {
                    comb.push_back(v);
                    memo[i].push_back(comb);
                }
            }
        }
    }

    // Imprimir todas las combinaciones
    cout << "Combinaciones válidas para " << n << ":\n";
    for (auto comb : memo[n]) {
        cout << "[ ";
        for (int x : comb) cout << x << " ";
        cout << "]\n";
    }

    cout << "\nTotal de combinaciones: " << memo[n].size() << endl;

    return 0;
}
