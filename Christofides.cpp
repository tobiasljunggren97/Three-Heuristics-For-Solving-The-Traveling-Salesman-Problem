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


using namespace std;

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
        cout << msg << endl;
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

	cout << "Optimal matching cost: " << obj << endl;
	cout << "Edges in the matching:" << endl;
	for(list<int>::iterator it = matching.begin(); it != matching.end(); it++)
	{
		pair<int, int> e = G.GetEdge( *it );

		cout << S[e.first] << " " << S[e.second] << endl;
    graph.addNeighbor(S[e.first], S[e.second]);
	}
    return 0;
}

vector<int> eulerian_tour(Graph g) {

    vector<int> eularianTour; 
    int n = g.getN();
    vector<int> visited(n, 0);
    // visited[0] = 1; // Start by visiting first node. 
    int notFinished = 1; 
    int currentNode = 0; 
    while(notFinished) {

      vector<int> neighbors = g.getNeighbors(currentNode);

      if (visited[currentNode]) { // we have visited this node before. 
        notFinished = 0; // Assume we are finished. 
        for (int i = 0; i < neighbors.size(); i++) { // If we find node not visited, continue. 
          if (visited[neighbors[i]] == 0) { notFinished = 1; currentNode = neighbors[i]; break;}
        }
      } else {
        visited[currentNode] = 1; // Visit current node. 
        eularianTour.push_back(currentNode);
      }
      
      
    }
    cout << "EULARIAN TOUR: " << endl; 
    for (int i = 0; i < eularianTour.size(); i++) {
      cout << " -> " << eularianTour[i]; 
    }
    

    return eularianTour;
}

vector<int> tsp_tour(vector<int> eularianTour) {
    int n = eularianTour.size(); 
    vector<int> tsp; 
    vector<int> visited(n, 0);
    for (int i = 0; i < n; i++) { // Iterate through eularian tour. 
      if (visited[eularianTour[i]] == 1) { 
        continue; 
      }
      tsp.push_back(eularianTour[i]);
      visited[eularianTour[i]] = 1;
    }

    cout << "GENERATED TSP: " << endl;

    for (int i = 0; i < eularianTour.size(); i++) {
      cout << " -> " << eularianTour[i]; 
    }
    cout << endl;
    

    
    return tsp;
}


//TEMPORARY HELPER
double calculateTourCost(vector<int> tsp_tour, Graph &g){
  int cost = 0;
  for(int i = 0; i < tsp_tour.size(); i++){
    cost += g.getWeight(tsp_tour[i], tsp_tour[(i+1) % tsp_tour.size()]);
  }
  return cost;
}

TSPSolution christofides(Graph &g) {
    cout << "graph with in the beginning: "<< endl; 
    g.printWeightMatrix();
    // Run prims algorithm to get neighbourlist
    prims(g);
    cout << "Adjacency list after prims: " << endl;
    g.printAdjacencyList();
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
    cout << "Adjacency list after matching: " << endl;
    g.printAdjacencyList();
    // Add new edges to neighbourlist (duplicates allowed) to get multigraph

    // Generate Eularian tour from multigraph with duplicate edges
    cout << "Graphs weights before eularian tour: " << endl; 
    g.printWeightMatrix(); 
    vector<int> eulerianTour = eulerian_tour(g);
    // Generate TSP tour from Eularian tour
    TSPSolution christofidesSolution(tsp_tour(eulerianTour));
    christofidesSolution.cost = calculateTourCost(christofidesSolution.tour, g);
    cout << "Cost of tour: " << christofidesSolution.cost << endl;
    
    return christofidesSolution;
}


