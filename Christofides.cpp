#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include "GraphChristofides.h"
#include "MatchingChristofides.h"


using namespace std;

int prims() {
    return 0;
}

pair<GraphC, vector<double> > ReadWeightedGraph(vector<vector<int> > adjacencyList, vector<vector<double> > weights, int numVertices, int numEdges) {
    GraphC G(numVertices);
    vector<double> cost(numEdges);
    cout << "HEJ"<< endl;
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < adjacencyList[i].size(); j++) { //ADJLIST MUST BE SORTED IN ASCENDING ORDER
            G.AddEdge(i, adjacencyList[i][j]);
            cost.push_back(weights[i][j]);
        }
    }
    return make_pair(G, cost);
}

int minimum_weight_matching(vector<vector<int> > adjacencyList, vector<vector<double> > weights, int numVertices, int numEdges) {
    // OBS Example Min-Weight Matching from https://github.com/dilsonpereira/Minimum-Cost-Perfect-Matching/blob/master/Graph.h
    GraphC G;
	vector<double> cost;
	
	//Read the graph
	pair< GraphC, vector<double> > p = ReadWeightedGraph(adjacencyList, weights, numVertices, numEdges);
    
	//pair< GraphC, vector<double> > p = CreateRandomGraph();
	G = p.first;
	cost = p.second;

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

int eularian_tour() {
    return 0;
}

int tsp_tour() {
    return 0;
}

int christofides() {
    // Run prims algorithm to get neighbourlist

    // Create S = { i : len(neightbours(i)) % 2 != 0 }

    // Find minimum weight matching M in S

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
