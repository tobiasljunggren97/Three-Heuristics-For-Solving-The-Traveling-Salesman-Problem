#include "Greedy.h"
#include "LocalImprovements.h"

TSPSolution nearestNeighbor(Graph &g, int startNode) {
    int numVertices = g.getN();
    if(startNode < 0 || startNode >= numVertices) {
        throw "Invalid start node";
    }
    int currentVertex = startNode;
    TSPSolution tspSolution = TSPSolution(numVertices);
    tspSolution.tour[0] = currentVertex;
    vector<int> visited(numVertices);
    visited[currentVertex] = 1;
    int counter = 1;
    const vector<int> weights;


    int minWeight = numeric_limits<int>::max();
    int currentWeight;
    int minWeightNode;
    while (counter < numVertices) {

        for (int i = 0; i < numVertices; i++) {
            if (i != currentVertex && !visited[i]) {
                currentWeight = g.getWeight(currentVertex, i);
                if (currentWeight < minWeight) {
                    minWeight = currentWeight;
                    minWeightNode = i;
                }
            }
        }

        tspSolution.tour[counter] = minWeightNode;
        visited[minWeightNode] = 1;
        tspSolution.cost += minWeight;
        minWeight = numeric_limits<int>::max();
        currentVertex = minWeightNode;
        counter++;
    }
    tspSolution.cost += g.getWeight(currentVertex, startNode);
    TSPSolution localImpr = twoOpt(tspSolution, g);
    return localImpr;
}

