#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include "GraphChristofides.h"
#include "MatchingChristofides.h"
#include "Graph.h"
#include "Christofides.h"
#include <tuple>


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
    for (int a = 0; a < numVertices; a++) {
      cout << S[a] << endl;
      cout << graph.getNeighbors(S[a])[0] << endl;
    }
    cout << "HEJ" << endl;
    vector<double> cost(numVertices * (numVertices-1)/2);
    try {
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < graph.getNeighbors(S[i]).size(); j++) { //ADJLIST MUST BE SORTED IN ASCENDING ORDER
                G.AddEdge(i, graph.getNeighbors(S[i])[j]);
                cost.push_back(graph.getWeight(S[i], j));
            }
        }
    } catch (const char* msg) {
        cout << msg << endl;
    }
    // for (int i = 0; i < numVertices; i++) {
    //     for (int j = 0; j < graph.getNeighbors(S[i]).size(); j++) { //ADJLIST MUST BE SORTED IN ASCENDING ORDER
    //         G.AddEdge(i, graph.getNeighbors(S[i])[j]);
    //         cost.push_back(graph.getWeight(S[i], j));
    //     }
    // }
    return make_pair(G, cost);
}

int minimum_weight_matching(Graph &graph, vector<int> &S) {
    // OBS Example Min-Weight Matching from
    
  // OBS Example Min-Weight Matching from https://github.com/dilsonpereira/Minimum-Cost-Perfect-Matching/blob/master/Graph.h
  GraphC G;
	vector<double> cost;
	
	//Read the graph
	pair< GraphC, vector<double> > p = ReadWeightedGraph(graph, S);
    
	//pair< GraphC, vector<double> > p = CreateRandomGraph();
	G = p.first;
	cost = p.second;
  
  for (int i = 0; i < G.GetNumEdges(); i++)
	{
		pair<int, int> e = G.GetEdge(i);
		cout << e.first << " " << e.second << " " << cost[i] << endl;
	}
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

		cout << e.first << " " << e.second << endl;
	}
    return 0;
}

int eulerian_tour() {
    return 0;
}

int tsp_tour() {
    return 0;
}

int christofides(Graph &g) {
    // Run prims algorithm to get neighbourlist
    prims(g);

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
    minimum_weight_matching(g, S);
    // Add new edges to neighbourlist (duplicates allowed) to get multigraph

    // Generate Eularian tour from multigraph with duplicate edges

    // Generate TSP tour from Eularian tour
    return 0;
}


// JUST A TEST
// int main() {
//     int N = 10;
//     vector<double> inner_vector(N);
//     vector<vector<double> > weight(N,inner_vector);
//     cout << "HEJ"<< endl;
//     weight[0][1] = 10;
//     weight[0][2] = 4;
//     weight[1][2] = 3;
//     weight[1][5] = 2;
//     weight[1][6] = 2;
//     weight[2][3] = 1;
//     weight[2][4] = 2;
//     weight[3][4] = 5;
//     weight[4][6] = 4;
//     weight[4][7] = 1;
//     weight[4][8] = 3;
//     weight[5][6] = 1;
//     weight[6][7] = 2;
//     weight[7][8] = 3;
//     weight[7][9] = 2;
//     weight[8][9] = 1;
//     cout << "HEJ"<< endl;
//     vector<vector<int> > adjacencyList(N);
//     adjacencyList[0].push_back(1);
//     adjacencyList[0].push_back(2);
//     adjacencyList[1].push_back(0);
//     adjacencyList[1].push_back(2);
//     adjacencyList[1].push_back(5);
//     adjacencyList[1].push_back(6);
//     adjacencyList[2].push_back(0);
//     adjacencyList[2].push_back(1);
//     adjacencyList[2].push_back(3);
//     adjacencyList[2].push_back(4);
//     adjacencyList[3].push_back(2);
//     adjacencyList[3].push_back(4);
//     adjacencyList[4].push_back(2);
//     adjacencyList[4].push_back(3);
//     adjacencyList[4].push_back(6);
//     adjacencyList[4].push_back(7);
//     adjacencyList[4].push_back(8);
//     adjacencyList[5].push_back(1);
//     adjacencyList[5].push_back(6);
//     adjacencyList[6].push_back(1);
//     adjacencyList[6].push_back(4);
//     adjacencyList[6].push_back(5);
//     adjacencyList[6].push_back(7);
//     adjacencyList[7].push_back(4);
//     adjacencyList[7].push_back(6);
//     adjacencyList[7].push_back(8);
//     adjacencyList[7].push_back(9);
//     adjacencyList[8].push_back(4);
//     adjacencyList[8].push_back(7);
//     adjacencyList[8].push_back(9);
//     adjacencyList[9].push_back(7);
//     adjacencyList[9].push_back(8);
//     cout << "HEJ"<< endl;
//     minimum_weight_matching(adjacencyList, weight, N, 16);

//     return 0;
// }
