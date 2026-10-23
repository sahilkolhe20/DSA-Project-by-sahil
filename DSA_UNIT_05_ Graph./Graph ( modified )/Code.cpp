Code.cpp

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <functional>
#include <algorithm>
#include <string>
using namespace std;

const int V = 6;
const int INF = INT_MAX;

string area[V] = {
    "Courier Hub", "Area A", "Area B",
    "Area C", "Area D", "Area E"
};

using Edge = pair<int, int>;
using Graph = vector<vector<Edge>>;

// Add a bidirectional road
void addRoad(Graph &adj, int u, int v, int w) {
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
}

// Find an existing road and update its weight
bool updateDirection(Graph &adj, int u, int v, int w) {
    for (auto &edge : adj[u]) {
        if (edge.first == v) {
            edge.second = w;
            return true;
        }
    }
    return false;
}

bool updateRoad(Graph &adj, int u, int v, int w) {
    bool first = updateDirection(adj, u, v, w);
    bool second = updateDirection(adj, v, u, w);
    return first && second;
}

// Dijkstra: calculates distances and parent vertices
void dijkstra(const Graph &adj, int source,
              vector<int> &dist, vector<int> &parent) {
    dist.assign(V, INF);
    parent.assign(V, -1);

    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > pq;

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d != dist[u])
            continue;

        for (const auto &edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;

            if (dist[u] != INF &&
                dist[u] <= INF - w &&
                dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
}

// Display shortest distances from any source
void displayDistances(const Graph &adj, int source) {
    vector<int> dist, parent;
    dijkstra(adj, source, dist, parent);

    cout << "\nShortest distances from "
         << area[source] << ":\n";

    for (int i = 0; i < V; i++) {
        cout << area[i] << ": ";

        if (dist[i] == INF)
            cout << "Unreachable\n";
        else
            cout << dist[i] << " km\n";
    }
}

// Display complete shortest path to a destination
void displayPath(const Graph &adj, int source, int dest) {
    vector<int> dist, parent;
    dijkstra(adj, source, dist, parent);

    if (dist[dest] == INF) {
        cout << "\nDestination is unreachable.\n";
        return;
    }

    vector<int> path;

    for (int v = dest; v != -1; v = parent[v])
        path.push_back(v);

    reverse(path.begin(), path.end());

    cout << "\nShortest path: ";
    for (int i = 0; i < (int)path.size(); i++) {
        cout << area[path[i]];
        if (i + 1 < (int)path.size())
            cout << " -> ";
    }

    cout << "\nTotal distance: " << dist[dest] << " km\n";
}

void showAreas() {
    cout << "\nAvailable locations:\n";
    for (int i = 0; i < V; i++)
        cout << i << " - " << area[i] << '\n';
}

int main() {
    Graph adj(V);

    // Initial roads and distances in kilometers
    addRoad(adj, 0, 1, 4);
    addRoad(adj, 0, 2, 2);
    addRoad(adj, 2, 1, 1);
    addRoad(adj, 1, 3, 5);
    addRoad(adj, 2, 3, 8);
    addRoad(adj, 3, 4, 2);

    // Area E (vertex 5) is initially disconnected

    int choice;

    do {
        cout << "\n=== Courier Delivery System ===\n";
        cout << "1. Calculate shortest distances\n";
        cout << "2. Display complete shortest path\n";
        cout << "3. Update road weight and recalculate\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            showAreas();

            int source;
            cout << "Enter source vertex (0-5): ";
            cin >> source;

            if (source < 0 || source >= V) {
                cout << "Invalid source vertex.\n";
                continue;
            }

            displayDistances(adj, source);
        }
        else if (choice == 2) {
            showAreas();

            int source, dest;
            cout << "Enter source vertex (0-5): ";
            cin >> source;
            cout << "Enter destination vertex (0-5): ";
            cin >> dest;

            if (source < 0 || source >= V ||
                dest < 0 || dest >= V) {
                cout << "Invalid vertex.\n";
                continue;
            }

            displayPath(adj, source, dest);
        }
        else if (choice == 3) {
            showAreas();

            int u, v, newWeight;
            cout << "Enter road endpoint 1 (0-5): ";
            cin >> u;
            cout << "Enter road endpoint 2 (0-5): ";
            cin >> v;
            cout << "Enter new distance in km: ";
            cin >> newWeight;

            if (u < 0 || u >= V || v < 0 || v >= V ||
                u == v || newWeight < 0) {
                cout << "Invalid endpoints or distance.\n";
                continue;
            }

            if (updateRoad(adj, u, v, newWeight)) {
                cout << "Road distance updated successfully.\n";

                int source;
                cout << "Enter source for recalculation (0-5): ";
                cin >> source;

                if (source < 0 || source >= V) {
                    cout << "Invalid source vertex.\n";
                    continue;
                }

                displayDistances(adj, source);
            } else {
                cout << "Road does not exist. No changes made.\n";
            }
        }
        else if (choice == 4) {
            cout << "Program ended.\n";
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 4);

    return 0;
}
