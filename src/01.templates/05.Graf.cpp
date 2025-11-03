#include <bits/stdc++.h>
using namespace std;

// ========== DFS (рекурсивный) ==========
void dfs_rec(const vector<vector<int>>& g, int u, vector<int>& visited, vector<int>& order) {
    visited[u] = 1;
    order.push_back(u);
    for (int v : g[u])
        if (!visited[v])
            dfs_rec(g, v, visited, order);
}

vector<int> dfs(const vector<vector<int>>& g, int start) {
    int n = g.size();
    vector<int> visited(n, 0), order;
    dfs_rec(g, start, visited, order);
    return order;
}

// ========== BFS ==========
vector<int> bfs(const vector<vector<int>>& g, int start) {
    int n = g.size();
    vector<int> dist(n, -1);
    queue<int> q;
    q.push(start);
    dist[start] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : g[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return dist;
}

// ========== Жадная раскраска графа ==========
vector<int> greedyColoring(const vector<vector<int>>& g) {
    int n = g.size();
    vector<int> color(n, -1);
    for (int u = 0; u < n; ++u) {
        vector<bool> used(n, false);
        for (int v : g[u])
            if (color[v] != -1) used[color[v]] = true;
        for (int c = 0; c < n; ++c)
            if (!used[c]) { color[u] = c; break; }
    }
    return color;
}

// ========== Проверка на двудольность ==========
bool isBipartite(const vector<vector<int>>& g, vector<int>& color) {
    int n = g.size();
    color.assign(n, -1);
    for (int start = 0; start < n; ++start) {
        if (color[start] != -1) continue;
        queue<int> q;
        q.push(start);
        color[start] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : g[u]) {
                if (color[v] == -1) {
                    color[v] = color[u] ^ 1;
                    q.push(v);
                }
                else if (color[v] == color[u])
                    return false;
            }
        }
    }
    return true;
}

// ==== Поиск цикла в неориентированном графе ====
vector<int> findCycle(const vector<vector<int>>& g) {
    int n = g.size();
    vector<int> parent(n, -1), color(n, 0);
    for (int i = 0; i < n; ++i) {
        if (color[i] != 0) continue;
        stack<int> st;
        st.push(i);
        color[i] = 1;
        while (!st.empty()) {
            int u = st.top();
            bool done = true;
            for (int v : g[u]) {
                if (v == parent[u]) continue;
                if (color[v] == 1) {
                    vector<int> cycle;
                    int cur = u;
                    while (cur != v) {
                        cycle.push_back(cur);
                        cur = parent[cur];
                    }
                    cycle.push_back(v);
                    cycle.push_back(u);
                    reverse(cycle.begin(), cycle.end());
                    return cycle;
                }
                if (color[v] == 0) {
                    parent[v] = u;
                    color[v] = 1;
                    st.push(v);
                    done = false;
                    break;
                }
            }
            if (done) {
                color[u] = 2;
                st.pop();
            }
        }
    }
    return {};
}

// ========== Дейкстра ==========
vector<long long> dijkstra(const vector<vector<pair<int, long long>>>& g, int s) {
    int n = g.size();
    const long long INF = (1LL << 60);
    vector<long long> dist(n, INF);
    dist[s] = 0;
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    pq.push({ 0, s });
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d != dist[u]) continue;
        for (auto [v, w] : g[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({ dist[v], v });
            }
        }
    }
    return dist;
}

// ========== Флойд–Уоршелл ==========
vector<vector<long long>> floydWarshall(const vector<vector<long long>>& adj) {
    int n = adj.size();
    const long long INF = (1LL << 60);
    vector<vector<long long>> dist = adj;
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (dist[i][k] < INF && dist[k][j] < INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    return dist;
}

// === Пример использования ===
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 5;
    vector<vector<int>> g(n);
    vector<pair<int, int>> edges = { {0,1},{1,2},{2,0},{2,3},{3,4} };
    for (auto [u, v] : edges) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    auto dfs_order = dfs(g, 0);
    auto bfs_dist = bfs(g, 0);

    cout << "DFS order (recursive): ";
    for (int v : dfs_order) cout << v << ' '; cout << "\n";

    cout << "BFS distances from 0: ";
    for (int d : bfs_dist) cout << d << ' '; cout << "\n";

    return 0;
}
