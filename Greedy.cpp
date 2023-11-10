#include "Greedy.h"
#include "LocalImprovements.h"

TSPSolution greedy(Graph &g) {
    int numVertices = g.getN();
    int currentVertex = 0;
    TSPSolution tspSolution = TSPSolution(numVertices);
    tspSolution.tour[0] = currentVertex;
    vector<int> visited(numVertices);
    visited[currentVertex] = 0;
    visited[0] = 1;
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
    tspSolution.cost += g.getWeight(currentVertex, 0);
    TSPSolution localImpr = twoOpt(tspSolution, g);
    return localImpr;
}



