#include "../src/dijkstras.h"


vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {

}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination) {

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