#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <tuple>
#include "graph.h"

using namespace std;

vector<vector<int> > prims(Graph g){
  int numPoints = g.getN();
  int numEdges = 0;  
  vector<int> handled(numPoints);
  handled[0] = true;
  vector<vector<int> > adjacencyList(numPoints);

  int node1;  
  int node2;  

  while (numEdges < numPoints - 1) {

    int min = numeric_limits<int>::max();
    node1 = 0;
    node2 = 0;

    for (int i = 0; i < numPoints; i++) {
      if (handled[i]) {
        for (int j = 0; j < numPoints; j++) {
          if (!handled[j] && g.getWeight(i,j)) {  // not in selected and there is an edge
            if (min > g.getWeight(i,j) && i != j) {
              min = g.getWeight(i,j);
              node1 = i;
              node2 = j;
            }
          }
        }
      }
    }
    
    adjacencyList[node1].push_back(node2);
    adjacencyList[node2].push_back(node1);
    handled[node2] = true;
    numEdges++;
  }

  return adjacencyList;    
}


int minimum_weight_matching() {
    return 0;
}

int eulerian_tour() {
    return 0;
}

int tsp_tour() {
    return 0;
}

int cristofides(Graph g) {
    // Run prims algorithm to get neighbourlist
    g.setAdjancecyList(prims(g));
    g.printAdjacencyList();
    // Create S = { i : len(neightbours(i)) % 2 != 0 }
    vector<int> S;
    for(int i = 0; i < g.getN(); i++){
        if(g.getNeighbors(i).size() % 2 != 0){
            cout << i << " has uneven number of neighbours" << endl;
            S.push_back(i);
        }
    }
    // Find minimum weight matching M in S

    // Add new edges to neighbourlist (duplicates allowed) to get multigraph

    // Generate Eularian tour from multigraph with duplicate edges

    // Generate TSP tour from Eularian tour
    return 0;
}


