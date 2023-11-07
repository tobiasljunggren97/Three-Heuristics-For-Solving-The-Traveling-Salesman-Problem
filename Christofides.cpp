#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include "GraphChristofides.h"
#include "MatchingChristofides.h"
#include "Graph.h"
#include "Christofides.h"
#include <tuple>

#define DEBUG 0

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

int setup_edges_old(Graph &g, vector<vector<int>> &edges) {

  g.printAdjacencyList(); 
  int edgesLeft = 0; 
  vector<vector<int>>  adj_lst = g.getAdjacencyList(); 
  edges = vector<vector<int>>(g.getN());
  for (int i = 0; i < adj_lst.size(); i++)
  {
    edges[i] = vector<int>(g.getN()); 
    for (int j = 0; j < adj_lst[i].size(); j++)
    {
      edges[i][adj_lst[i][j]] = 1; 
      edgesLeft = edgesLeft + 1; 
      // cout << i << " -- " << adj_lst[i][j] << " has edge " << endl; 
    }
    
  }
  return edgesLeft;
}

int setup_edges(Graph &g, vector<vector<int>> &edges) {

  g.printAdjacencyList(); 
  int edgesLeft = 0; 
  vector<vector<int>>  adj_lst = g.getAdjacencyList(); 
  edges = vector<vector<int>>(g.getN());
  for (int i = 0; i < adj_lst.size(); i++)
  {
    edges[i] = vector<int>(g.getN()); 
    for (int j = 0; j < adj_lst[i].size(); j++)
    {
      edges[i][adj_lst[i][j]] = 1; 
      edgesLeft = edgesLeft + 1; 
      // cout << i << " -- " << adj_lst[i][j] << " has edge " << endl; 
    }
    
  }
  return edgesLeft;
}


vector<int> eularian_tour(Graph &g) {
  vector<vector<int>> edges; 
  int totalNrEdges = setup_edges(g, edges); 

  vector<int> eularian_tour; 
  int notFinished = 1; 
  int currentNode = 0; 
  vector<int> neighbors; 
  eularian_tour.push_back(0); 
  while(notFinished) 
  {

keep_going: 
    for (int i = 0; i < g.getN(); i++)
    {  
      if (edges[currentNode][i] > 0) { // there is an unused edge between current node and the neighbor we are looking at. 
          eularian_tour.push_back(i); 
          edges[currentNode][i] = 0;
          totalNrEdges--; 
          currentNode = i; 
          goto keep_going; 
      }
      else if (edges[i][currentNode] > 0) { // there is an unused edge between current node and the neighbor we are looking at. 

          eularian_tour.push_back(i); 
          edges[i][currentNode] = 0;
          totalNrEdges--; 
          currentNode = i; 
          goto keep_going; 
      }

    }    
    if (totalNrEdges > 0) {
      cerr << "could not find path from node: " << currentNode << " to any of its neighbors, but there exist paths we haven't crossed yet." << endl; 
      break; 
    }
    else if (totalNrEdges == 0) {
      notFinished = 0; 
    }
  }

  if (DEBUG) {
    cout << "EULARIAN TOUR: " << endl; 
    for (int i = 0; i < eularian_tour.size(); i++) {
      cout << " -> " << eularian_tour[i]; 
    }
  }
   
  return eularian_tour; 
}



// vector<int> erlerian_tour(Graph &g) {
//   Graph gc = g; // copy graph object. 
//   vector<vector<int>> edges = g.getAdjacencyList(); 
//   stack<int> currentPath; 
//   vector<int> finalPath; 
//   int currentNode = 0; // starting node. 

//   currentPath.push(0); // push starting node onto stack. 
//   while(!currentPath.empty()) {
//     vector<int> neighbors = gc.getNeighbors(currentNode); 
//     if (neighbors.size() > 0 ) { // currentnode has unvisited edges. 
//       currentPath.push(neighbors[0]); // add first best neighbor 
//       gc.removeNeighbor(currentNode, neighbors[0]);
//       currentNode = neighbors[0];
//     }
//     else { // Current node has no free edges. 
//       currentNode = currentPath.top();
//       currentPath.pop();  
//       finalPath.push_back(currentNode); 
//     }
    
//   }

//   return finalPath; 
// }


vector<int> eulerian_tour_new(Graph &g) {
    Graph gc = g;  // Copy graph object.
    vector<vector<int>> edges = g.getAdjacencyList();
    stack<int> currentPath;
    vector<int> finalPath;
    int currentNode = 0;  // Initialize with a starting node (you should choose it properly).
    // Check for the number of odd-degree vertices and connectivity here.

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


vector<int> tsp_tour(vector<int> &eularianTour) {
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
    tsp.push_back(eularianTour[n-1]);

    if (DEBUG) {
      cout << "GENERATED TSP: " << endl;
      for (int i = 0; i < tsp.size(); i++) {
        cout << " -> " << tsp[i]; 
      }
    }
    
    return tsp;
}

int christofides(Graph &g) {



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
    vector<int> eulerianTour = eularian_tour(g);
    vector<int> tsp = tsp_tour(eulerianTour); 

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
