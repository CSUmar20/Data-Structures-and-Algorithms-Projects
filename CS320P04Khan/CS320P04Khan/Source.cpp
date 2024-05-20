#include <iostream>
#include "graph.h" 

using namespace std;

int main() {
    int m, n;
    //cout << "Enter the number of colors: ";
    cin >> m;
    //cout << "Enter the number of vertices: ";
    cin >> n;
    Graph graph(n);
    //cout << "Enter the edges: ";

    char x, y;
    int u, v;
    while (true) {
        cin >> x >> u >> v >> y;
        if (u == -1 && v == -1) {
            break;
        }
        graph.addEdge(u, v);
    }

    graph.graphColoring(m);
    return 0;
}



