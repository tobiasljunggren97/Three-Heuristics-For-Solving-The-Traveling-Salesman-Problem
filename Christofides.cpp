#include "Christofides.h"


#define DEBUG 0

using namespace std;

void prims(Graph &g) {
  
  int numVertices = g.getN();
  int currentVertex = 0;
  vector<int> inMST(numVertices);
  inMST[currentVertex] = 1;
  vector<pair<int, int> > edgesToHandle;

  for (int i = 1; i < numVertices; i++) {
    edgesToHandle.push_back(make_pair(currentVertex, i));
  } 
  
  int count = 1;

  while (count < numVertices) {
    int minWeightEdge = numeric_limits<int>::max();
    int minWeightEdgeIndex = 0;
    int minWeightNode = 0;
    int weight = 0;
    for (int i = 0; i < edgesToHandle.size(); i++) {
      if (i != currentVertex) {
      weight = g.getWeight(edgesToHandle[i].first, edgesToHandle[i].second);
      if (weight < minWeightEdge && !(inMST[edgesToHandle[i].first] && inMST[edgesToHandle[i].second])) {
        currentVertex = edgesToHandle[i].first;
        minWeightNode = edgesToHandle[i].second;
        minWeightEdgeIndex = i;
        minWeightEdge = weight;
      }
      }
    }
    inMST[minWeightNode] = 1;
    count++;
    g.addNeighbor(currentVertex, minWeightNode);
    for (int node = 0; node < numVertices; node++) {
      if (!(inMST[node] && inMST[node]) && node != minWeightNode) {
        edgesToHandle.push_back(make_pair(minWeightNode, node));
      }
    }
    edgesToHandle.erase(edgesToHandle.begin()+minWeightEdgeIndex);
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
	// }
	//Create a Matching instance passing the graph
	Matching M(G);

	//Pass the costs to solve the problem
	pair< list<int>, double > solution = M.SolveMinimumCostPerfectMatching(cost);

	list<int> matching = solution.first;
	double obj = solution.second;

	for(list<int>::iterator it = matching.begin(); it != matching.end(); it++)
	{
		pair<int, int> e = G.GetEdge( *it );

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

    int eulerian_tour_size = eularianTour.size(); 
    int n = g.getN(); 
    TSPSolution tspSolution = TSPSolution(n);
    vector<int> visited(n, 0);
    int count = 0;
    for (int i = 0; i < eulerian_tour_size; i++) { // Iterate through eularian tour. 
      if (visited[eularianTour[i]] == 1) { 
        continue; 
      }
      tspSolution.tour[count] = eularianTour[i];
      count++;
      tspSolution.cost += g.getWeight(eularianTour[i], eularianTour[(i+1) % n]);
      visited[eularianTour[i]] = 1;
    }
  

    //Now printed in main
    cout << "TSP TOUR: " << endl;
    for (int i = 0; i < tspSolution.tour.size(); i++) {
      cout << tspSolution.tour[i] << " -> "; 
    }
    
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
    Stopwatch stopwatch = Stopwatch();
    stopwatch.start("Prims");
    // Run prims algorithm to get neighbourlist
    prims(g);
    stopwatch.stop();
    // Create S = { i : len(neightbours(i)) % 2 != 0 }
    stopwatch.start("Create S");
    vector<int> S;
    for(int i = 0; i < g.getN(); i++){
        if(g.getNeighbors(i).size() % 2 != 0){
            S.push_back(i);
        }
    }
    stopwatch.stop();
    // Find minimum weight matching M in S
    stopwatch.start("Minimum weight matching");
    minimum_weight_matching(g, S);
    stopwatch.stop();
    // Add new edges to neighbourlist (duplicates allowed) to get multigraph

    // Generate Eularian tour from multigraph with duplicate edges
    stopwatch.start("Eulerian tour");
    vector<int> eulerianTour = eulerian_tour(g);
    stopwatch.stop();
    // Generate TSP tour from Eularian tour
    stopwatch.start("TSP tour");
    TSPSolution christofidesSolution = tsp_tour(eulerianTour, g);
    stopwatch.stop();
    
    return christofidesSolution;
}


