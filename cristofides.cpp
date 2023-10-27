#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <tuple>

using namespace std;

vector<vector<int> > prims(vector<vector<double> > weight, int numPoints){
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
          if (!handled[j] && weight[i][j]) {  // not in selected and there is an edge
            if (min > weight[i][j] && i != j) {
              min = weight[i][j];
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

int cristofides(vector<vector<double> > weight, int N) {
    // Run prims algorithm to get neighbourlist

    vector<vector<int> > adjacencyList(N);
    adjacencyList = prims(weight, N);

    // Print adjacency list
    for (int i = 0; i < N; ++i) {
        cout << i << ": ";
        for (int j = 0; j < adjacencyList[i].size(); ++j) {
            cout << adjacencyList[i][j] << " ";
        }
        cout << endl;
    }

    // Create S = { i : len(neightbours(i)) % 2 != 0 }

    // Find minimum weight matching M in S

    // Add new edges to neighbourlist (duplicates allowed) to get multigraph

    // Generate Eularian tour from multigraph with duplicate edges

    // Generate TSP tour from Eularian tour
    return 0;
}
