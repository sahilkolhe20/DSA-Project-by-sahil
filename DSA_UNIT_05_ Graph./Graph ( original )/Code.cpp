Code--

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <climits>
#include <functional>
using namespace std;

int main() {
    int V, E;

    cout << "Enter number of service areas including hub: ";
    cin >> V;

    vector<string> name(V);

    cout << "\nEnter names of vertices:\n";
    for (int i = 0; i < V; i++) {
        cout << i << " - ";
        cin >> name[i];
    }

    vector<vector<pair<int, int>>> adj(V);

    cout << "\nEnter number of roads: ";
    cin >> E;

    cout << "Enter roads as: source destination distance\n";

    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    int hub;
    cout << "\nEnter hub vertex number: ";
    cin >> hub;

    const int INF = INT_MAX;
    vector<int> dist(V, INF);

    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > pq;

    dist[hub] = 0;
    pq.push({0, hub});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d != dist[u])
            continue;

        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i].first;
            int w = adj[u][i].second;

            if (dist[u] <= INF - w &&
                dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    cout << "\nShortest Delivery Distances:\n";

    for (int i = 0; i < V; i++) {
        if (dist[i] == INF) {
            cout << name[i]
                 << " : Unreachable\n";
        } else {
            cout << name[i]
                 << " : " << dist[i]
                 << " km\n";
        }
    }

    cout << "\nUnreachable Areas:\n";
    bool found = false;

    for (int i = 0; i < V; i++) {
        if (dist[i] == INF) {
            cout << name[i] << endl;
            found = true;
        }
    }

    if (!found)
        cout << "None\n";

    return 0;
}
