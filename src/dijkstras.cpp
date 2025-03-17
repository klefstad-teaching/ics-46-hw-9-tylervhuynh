#include "../src/dijkstras.h"


vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    vector<int> distances(n, INF);
    vector<bool> visited(n, false);
    previous.clear();
    previous.push_back(-1);
    for (int i = 1; i < n; ++i) {previous.push_back(-1);}
    distances[source] = 0;
    for (int i = 0; i < n; ++i) {
        int minVertex = -1;
        int minDistance = INF;
        for (int v = 0; v < n; ++v) {
            if (!visited[v] && distances[v] < minDistance) {
                minDistance = distances[v];
                minVertex = v;
            }
        }
        if (minVertex == -1) {break;}
        visited[minVertex] = true;
        for (const Edge& edge : G[minVertex]) {
            int newDist = distances[minVertex] + edge.weight;
            if (newDist < distances[edge.dst]) {
                distances[edge.dst] = newDist;
                previous[edge.dst] = minVertex;
            }
        }
    }

    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    if (distances[destination] == INF) {return path;}
    stack<int> temp_stack;
    for (int at = destination; at != -1; at = previous[at]) {temp_stack.push(at);}
    while (!temp_stack.empty()) {
        path.push_back(temp_stack.top());
        temp_stack.pop();
    }
    return path;
}

void print_path(const vector<int>& v, int total) {
    if (v.empty()) {
        cout << "No path found." << endl;
        return;
    }
    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i] << " ";
    }
    cout << "\nTotal cost is " << total << endl;
}