#include "../src/dijkstras.h"


vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    
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
    if (v.empty()) {cout << "No path found." << endl; return;}
    cout << v.front() << endl;
    cout << "Total cost " << total << endl;
    for (int node : v) {
        cout << node << " ";
    }
    cout << endl;
    cout << "Total cost " << total << endl;
}