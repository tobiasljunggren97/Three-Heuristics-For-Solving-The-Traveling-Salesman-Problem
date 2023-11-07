#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include "GraphChristofides.h"
#include "MatchingChristofides.h"
#include "Graph.h"
#include "Christofides.h"
#include <tuple>
#include "TSPSolution.h"

#define DEBUG 0

using namespace std;

void prims2(Graph &g) {
  int numVertices = g.getN();
  int currentVertex = 0;
  vector<int> inMST(numVertices);
  inMST[currentVertex] = 1;
  vector<int> edgesToHandle = g.getNeighbors(currentVertex);
  int count = 0;

  while (count < numVertices) {
    int minWeightEdge = numeric_limits<int>::max();
    int minWeightNode = 0;
    int weight;
    for (int i = 0; i < edgesToHandle.size(); i++) {
      weight = g.getWeight(currentVertex, edgesToHandle[i]);
      if (weight < minWeightEdge) {
        minWeightNode = edgesToHandle[i];
        minWeightEdge = weight;
      }
    }
    inMST[minWeightNode] = 1;
    g.addNeighbor(currentVertex, minWeightNode);
    vector<int> minWeightNodeNeighbours = g.getNeighbors(minWeightNode);
    for (int node = 0; node < minWeightNodeNeighbours.size(); node ++) {
      if (!inMST[minWeightNodeNeighbours[node]]) {
        edgesToHandle.push_back(minWeightNodeNeighbours[node]);
      }
    }
    edgesToHandle.erase(edgesToHandle.begin()+minWeightNode);
  }

}

void prims(Graph &g){
  int numPoints = g.getN();
  int numEdges = 0;  
  vector<int> handled(numPoints);
  handled[0] = true;
  // vector<vector<int> > adjacencyList(numPoints);

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
    
    g.addNeighbor(node1, node2);
    handled[node2] = true;
    numEdges++;
  } 
}

pair<GraphC, vector<double> > ReadWeightedGraph(Graph &graph, vector<int> &S) {
    int numVertices = S.size();
    GraphC G(numVertices);

    vector<double> cost(numVertices * (numVertices-1)/2);
    try {
        for (int i = 0; i < numVertices; i++) {
            for (int j = i+1; j < numVertices; j++) {
                G.AddEdge(i, j); // Need to be 0-indexed, but if S = [1,4,5] then an edge in G is (0,1) = (S[0], S[1]) = (1,4) in graph
                cost[G.GetEdgeIndex(i, j)] = graph.getWeight(S[i], S[j]);
            }
        }
    } catch (const char* msg) {
        // cout << msg << endl;
    }

    return make_pair(G, cost);
}

int minimum_weight_matching(Graph &graph, vector<int> &S) {

  // OBS Example Min-Weight Matching from https://github.com/dilsonpereira/Minimum-Cost-Perfect-Matching/blob/master/Graph.h
  GraphC G;
	vector<double> cost;
	
	//Read the graph
	pair< GraphC, vector<double> > p = ReadWeightedGraph(graph, S);
    
	//pair< GraphC, vector<double> > p = CreateRandomGraph();
	G = p.first;
	cost = p.second;
  
  // for (int i = 0; i < G.GetNumEdges(); i++)
	// {
	// 	pair<int, int> e = G.GetEdge(i);
	// 	cout << e.first << " " << e.second << " " << cost[i] << endl;
	// }
	//Create a Matching instance passing the graph
	Matching M(G);

	//Pass the costs to solve the problem
	pair< list<int>, double > solution = M.SolveMinimumCostPerfectMatching(cost);

	list<int> matching = solution.first;
	double obj = solution.second;

	// cout << "Optimal matching cost: " << obj << endl;
	// cout << "Edges in the matching:" << endl;
	for(list<int>::iterator it = matching.begin(); it != matching.end(); it++)
	{
		pair<int, int> e = G.GetEdge( *it );

		// cout << S[e.first] << " " << S[e.second] << endl;
    graph.addNeighbor(S[e.first], S[e.second]);
	}
    return 0;
}

vector<int> eulerian_tour(Graph &g) {
    Graph gc = g;  // Copy graph object.
    vector<vector<int>> edges = g.getAdjacencyList();
    stack<int> currentPath;
    vector<int> finalPath;
    int currentNode = 0; 
    

    currentPath.push(currentNode);  // Push the starting node onto the stack.
    while (!currentPath.empty()) {
        vector<int> neighbors = gc.getNeighbors(currentNode);
        if (!neighbors.empty()) {
            int nextNode = neighbors[0];  // Choose an unvisited neighbor.
            currentPath.push(nextNode);  // Push the neighbor onto the stack.
            gc.removeNeighbor(currentNode, nextNode);  // Mark the edge as visited.
            currentNode = nextNode;  // Update the current node.
        } else {
            currentNode = currentPath.top();
            currentPath.pop();
            finalPath.push_back(currentNode);
        }
    }

    // If there are unvisited edges, no Eulerian tour exists.

    return finalPath;
}


TSPSolution tsp_tour(vector<int> &eularianTour, Graph &g) {

    int n = eularianTour.size(); 
    TSPSolution tspSolution = TSPSolution(n);
    vector<int> visited(n, 0);
    int count = 0;
    for (int i = 0; i < n; i++) { // Iterate through eularian tour. 
      if (visited[eularianTour[i]] == 1) { 
        continue; 
      }
      tspSolution.tour[count] = eularianTour[i];
      count++;
      tspSolution.cost += g.getWeight(eularianTour[i], eularianTour[(i+1) % n]);
      visited[eularianTour[i]] = 1;
    }
    tsp.push_back(eularianTour[n-1]);

    //Now printed in main
    // cout << "GENERATED TSP: " << endl;

    // for (int i = 0; i < eularianTour.size(); i++) {
    //   cout << " -> " << tspSolution.tour[i]; 
    // }
    // cout << endl;
    

    
    return tspSolution;
}

//TEMPORARY HELPER
// double calculateTourCost(vector<int> tsp_tour, Graph &g){
//   int cost = 0;
//   for(int i = 0; i < tsp_tour.size(); i++){
//     cost += g.getWeight(tsp_tour[i], tsp_tour[(i+1) % tsp_tour.size()]);
//   }
//   return cost;
// }

TSPSolution christofides(Graph &g) {
    // cout << "graph with in the beginning: "<< endl; 
    // g.printWeightMatrix();
    // Run prims algorithm to get neighbourlist
    prims(g);
    // cout << "Adjacency list after prims: " << endl;
    // g.printAdjacencyList();
    // Create S = { i : len(neightbours(i)) % 2 != 0 }
    vector<int> S;
    for(int i = 0; i < g.getN(); i++){
        if(g.getNeighbors(i).size() % 2 != 0){
            // cout << i << " has uneven number of neighbours" << endl;
            S.push_back(i);
        }
    }
    // Find minimum weight matching M in S
    minimum_weight_matching(g, S);
    // cout << "Adjacency list after matching: " << endl;
    // g.printAdjacencyList();
    // Add new edges to neighbourlist (duplicates allowed) to get multigraph

    // Generate Eularian tour from multigraph with duplicate edges
    // cout << "Graphs weights before eularian tour: " << endl; 
    // g.printWeightMatrix(); 
    vector<int> eulerianTour = eulerian_tour(g);
    // Generate TSP tour from Eularian tour
    TSPSolution christofidesSolution = tsp_tour(eulerianTour, g);
    // cout << "Cost of tour: " << christofidesSolution.cost << endl;
    
    return christofidesSolution;
}


