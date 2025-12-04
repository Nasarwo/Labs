#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> adj;
vector<int> tin, low;
vector<vector<int>> bridges;
vector<char> visited;
int timer;

void dfs(int v, int p = -1) {
    visited[v] = 1;
    tin[v] = low[v] = timer++;
    for (int to : adj[v]) {
        if (to == p) continue;
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] > tin[v]) {
                bridges.push_back({v, to});
            }
        }
    }
}

vector<vector<int>> criticalConnections(int n, const vector<vector<int>>& connections) {
    adj.assign(n, {});
    tin.assign(n, -1);
    low.assign(n, -1);
    visited.assign(n, 0);
    bridges.clear();
    timer = 0;

    for (const auto &e : connections) {
        int a = e[0], b = e[1];
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) dfs(i);
    }
    return bridges;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;

    cout << "Введите количество серверов n: ";
    if (!(cin >> n)) return 0;

    cout << "Введите количество соединений m: ";
    cin >> m;

    vector connections(m, vector<int>(2));

    cout << "Введите " << m << " соединений в формате: a b\n";
    cout << "(где 0 <= a, b < n)\n";

    for (int i = 0; i < m; ++i) {
        cout << "Соединение " << i + 1 << ": ";
        cin >> connections[i][0] >> connections[i][1];
    }

    vector<vector<int>> ans = criticalConnections(n, connections);

    cout << "\nКритические соединения:\n";
    if (ans.empty()) {
        cout << "Нет критических соединений.\n";
    } else {
        for (const auto &e : ans) {
            cout << e[0] << " " << e[1] << "\n";
        }
    }

    return 0;
}
