#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>

using namespace std;

class Graph {
private:
    int numberOfVertices;
    vector<vector<int>> adjacencyMatrix;

    bool backtrackColor(int currentVertex, int maxColors, vector<int>& vertexColors, int& maxUsedColor) {
        if (currentVertex == numberOfVertices) {
            return true;
        }

        for (int color = 1; color <= maxColors; color++) {
            vertexColors[currentVertex] = color;
            if (isPromising(currentVertex, vertexColors)) {
                if (color > maxUsedColor) {
                    maxUsedColor = color; 
                }
                if (backtrackColor(currentVertex + 1, maxColors, vertexColors, maxUsedColor)) {
                    return true;
                }
            }
        }
        vertexColors[currentVertex] = 0;
        return false;
    }

    bool isPromising(int currentVertex, const vector<int>& vertexColors) {
        for (int nextVertex = 0; nextVertex < numberOfVertices; nextVertex++) {
            if (adjacencyMatrix[currentVertex][nextVertex] != 0 && vertexColors[nextVertex] == vertexColors[currentVertex]) {
                return false;
            }
        }
        return true;
    }

public:
    Graph(int numVertices) : numberOfVertices(numVertices) {
        adjacencyMatrix.resize(numVertices, vector<int>(numVertices, 0));
    }

    void addEdge(int vertex1, int vertex2) {
        if (vertex1 >= 0 && vertex1 < numberOfVertices && vertex2 >= 0 && vertex2 < numberOfVertices) {
            this->adjacencyMatrix[vertex1][vertex2] = 1;
            this->adjacencyMatrix[vertex2][vertex1] = 1;
        }
    }

    void graphColoring(int maxColors) {
        vector<int> vertexColors(numberOfVertices, 0);
        int maxUsedColor = 0; 

        if (!backtrackColor(0, maxColors, vertexColors, maxUsedColor)) {
            cout << endl;
            cout << "No color assignment exists" << endl;
        }
        else {
            cout << endl;
            cout << "Color assignment:" << endl;
            for (int i = 0; i < numberOfVertices; i++) {
                cout << i << " : " << vertexColors[i] << endl;
            }
        }
    }

};

#endif
