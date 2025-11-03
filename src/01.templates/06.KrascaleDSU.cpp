#include <bits/stdc++.h>
using namespace std;

// ========== СНМ (DSU) с ранговой эвристикой и сжатием путей ==========
struct DSU {
    vector<int> parent, rank;
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        return (x == parent[x]) ? x : parent[x] = find(parent[x]);
    }
    bool unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        if (rank[x] < rank[y]) swap(x, y);
        parent[y] = x;
        if (rank[x] == rank[y]) rank[x]++;
        return true;
    }
};

// ========== Алгоритм Краскала (MST) ==========
// Рёбра: {вес, вершина u, вершина v}
vector<tuple<long long, int, int>> kruskal(int n, vector<tuple<long long, int, int>>& edges) {
    sort(edges.begin(), edges.end());
    DSU dsu(n);
    vector<tuple<long long, int, int>> mst;
    for (auto [w, u, v] : edges) {
        if (dsu.unite(u, v)) {
            mst.push_back({ w, u, v });
            if ((int)mst.size() == n - 1) break;
        }
    }
    return mst; // если размер < n-1 → граф несвязный
}

// == Пример использования ==
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 4, m = 5;
    // Рёбра: вес, u, v (все вершины 0-индексированы)
    vector<tuple<long long, int, int>> edges = {
        {1, 0, 1},
        {3, 1, 2},
        {2, 0, 2},
        {4, 2, 3},
        {5, 1, 3}
    };

    auto mst = kruskal(n, edges);
    long long total_weight = 0;
    cout << "MST edges:\n";
    for (auto [w, u, v] : mst) {
        cout << u << " -- " << v << " (weight " << w << ")\n";
        total_weight += w;
    }
    cout << "Total weight: " << total_weight << "\n";

    // Проверка связности
    if ((int)mst.size() != n - 1) {
        cout << "Graph is not connected!\n";
    }

    return 0;
}
