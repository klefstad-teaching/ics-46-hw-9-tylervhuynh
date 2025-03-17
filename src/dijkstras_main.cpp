#include "../src/dijkstras.h"


int main(int argc, char *argv[]) {
    string filename = "../src/small.txt";
    Graph G;
    file_to_graph(filename, G);
    vector<int> previous(G.numVertices, -1);
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);
    for (int destination = 0; destination < G.numVertices; destination++) {
        vector<int> path = extract_shortest_path(distances, previous, destination);
        print_path(path, distances[destination]);
    }
    return 0;
}