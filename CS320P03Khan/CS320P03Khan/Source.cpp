#include <fstream>
#include <vector>
#include <climits>
#include <bitset>
#include <set>
#include <algorithm>
#include "graph.h"

using namespace std;

class TSPSolver {
public:
    static void travel(Graph& graph, vector<vector<int>>& distances, vector<vector<int>>& head, int& minlength) {
        int numVertices = graph.getNumVertices();
        distances.resize(numVertices, vector<int>(1 << numVertices, INT_MAX));
        head.resize(numVertices, vector<int>(1 << numVertices, -1));

        for (int i = 0; i < numVertices; ++i) {
            distances[i][1 << i] = graph.getEdgeCost(0, i);
        }

        for (int visitedSet = 1; visitedSet < (1 << numVertices); ++visitedSet) {
            for (int i = 0; i < numVertices; ++i) {
                if (visitedSet & (1 << i)) {
                    for (int j = 0; j < numVertices; ++j) {
                        if (j != i && (visitedSet & (1 << j))) {
                            int prevVisitedSet = visitedSet & ~(1 << i);
                            if (distances[j][prevVisitedSet] < INT_MAX && graph.getEdgeCost(j, i) < INT_MAX) {
                                int cost = distances[j][prevVisitedSet] + graph.getEdgeCost(j, i);
                                if (cost < distances[i][visitedSet]) {
                                    distances[i][visitedSet] = cost;
                                    head[i][visitedSet] = j;
                                }
                            }
                        }
                    }
                }
            }
        }

        minlength = distances[0][(1 << numVertices) - 1];
    }

    static vector<int> getOptimalPath(Graph& graph, const vector<vector<int>>& head) {
        int numVertices = graph.getNumVertices();
        vector<int> path;
        int endVertex = 0;
        int visitedSet = (1 << numVertices) - 1;
        while (head[endVertex][visitedSet] != -1) {
            int prevVertex = head[endVertex][visitedSet];
            path.push_back(prevVertex);
            visitedSet &= ~(1 << endVertex);
            endVertex = prevVertex;
        }
        path.push_back(0);
        reverse(path.begin(), path.end());
        return path;
    }
};

int main() {
    string filename;
    cout << "Enter the filename you want to open: ";
    cin >> filename;

    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return 1;
    }

    Graph graph;
    graph.read(infile);
    infile.close();

    vector<vector<int>> distances;
    vector<vector<int>> head;
    int minlength;

    TSPSolver::travel(graph, distances, head, minlength);

    cout << "----------------------------------------------------------" << endl;
    cout << filename << " Contents: " << endl;
    infile.open(filename);
    if (infile.is_open()) {
        string line;
        while (getline(infile, line)) {
            cout << line << endl;
        }
        infile.close();
    }
    else {
        cerr << "Error: Unable to reopen file " << filename << endl;
        return 1;
    }

    cout << "\n*********Output according to " << filename << " contents: " << endl;
    if (minlength == INT_MAX) {
        cout << "No Hamiltonian cycle" << endl;
    }
    else {
        cout << "Optimal Tour Cost = [" << minlength << ", ";
        vector<int> optimalPath = TSPSolver::getOptimalPath(graph, head);
        cout << "<";
        for (int vertex : optimalPath) {
            cout << graph.getVertexName(vertex) << ",";
        }
        cout << graph.getVertexName(0) << ">]" << endl;
    }
    cout << "----------------------------------------------------------" << endl;

    return 0;
}