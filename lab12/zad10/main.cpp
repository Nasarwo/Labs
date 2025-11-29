#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

int networkDelayTime(vector<vector<int>>& times, int n, int k) {
    vector<vector<pair<int, int>>> graph(n + 1);
    
    for (const auto& edge : times) {
        int u = edge[0];
        int v = edge[1];
        int w = edge[2];
        graph[u].push_back({v, w});
    }
    
    vector<int> dist(n + 1, INT_MAX);
    dist[k] = 0;
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, k});
    
    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();
        
        if (d > dist[u]) {
            continue;
        }
        
        for (const auto& neighbor : graph[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;
            
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    
    int maxTime = 0;
    for (int i = 1; i <= n; i++) {
        if (dist[i] == INT_MAX) {
            return -1;
        }
        maxTime = max(maxTime, dist[i]);
    }
    
    return maxTime;
}

int main() {
    int n, k, m;
    
    cout << "Введите количество узлов (n): ";
    cin >> n;
    
    cout << "Введите начальный узел (k): ";
    cin >> k;
    
    cout << "Введите количество рёбер: ";
    cin >> m;
    
    vector<vector<int>> times(m);
    cout << "Введите рёбра в формате: начальный_узел конечный_узел вес" << endl;
    for (int i = 0; i < m; i++) {
        cout << "Ребро " << (i + 1) << ": ";
        int u, v, w;
        cin >> u >> v >> w;
        times[i] = {u, v, w};
    }
    
    int result = networkDelayTime(times, n, k);
    
    if (result == -1) {
        cout << "Результат: -1 (невозможно достичь все узлы)" << endl;
    } else {
        cout << "Результат: " << result << endl;
    }
    
    return 0;
}

