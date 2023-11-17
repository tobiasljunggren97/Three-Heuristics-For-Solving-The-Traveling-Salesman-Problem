#include "Christofides.h"
#include "hungarian.h"
#include "LocalImprovements.h"

#define DEBUG 0

using namespace std;

void primss(Graph &g)
{
  Stopwatch stopwatch = Stopwatch();
  int numVertices = g.getN();
  vector<int> inMST(numVertices);
  vector<int> toCheck = {0};
  inMST[0] = 1;
  stopwatch.start("First edgesToHandle");

  stopwatch.stop();
  int count = 1;

  while (count < numVertices)
  {
    int minWeightEdge = numeric_limits<int>::max();
    int minWeightNode = 0;
    int weight = 0;
    int neighbour = 0;
    if (count == 1)
    {
      stopwatch.start("First iteration");
    }
    for (int i = 0; i < toCheck.size(); i++)
    {
      for (int j = toCheck[i] + 1; j < numVertices; j++)
      {
        weight = g.getWeight(toCheck[i], j);
        if (weight < minWeightEdge && !inMST[j])
        {
          minWeightNode = j;
          minWeightEdge = weight;
          neighbour = toCheck[i];
        }
      }
    }
    inMST[minWeightNode] = 1;
    toCheck.push_back(minWeightNode);
    g.addNeighbor(neighbour, minWeightNode);
    count++;
    // cout << "Min edge " << neighbour << ", " << minWeightNode << " at weight " << weight << endl;
    if (count == 1)
    {
      stopwatch.stop();
    }
  }
}

void prims(Graph &g)
{
  Stopwatch stopwatch = Stopwatch();
  int numVertices = g.getN();
  int currentVertex = 0;
  vector<int> inMST(numVertices);
  inMST[currentVertex] = 1;

  vector<pair<int, int>> edgesToHandle;
  stopwatch.start("First edgesToHandle");
  for (int i = 1; i < numVertices; i++)
  {
    edgesToHandle.push_back(make_pair(currentVertex, i));
  }
  stopwatch.stop();
  int count = 1;

  while (count < numVertices)
  {
    int minWeightEdge = numeric_limits<int>::max();
    int minWeightEdgeIndex = 0;
    int minWeightNode = 0;
    int weight = 0;

    if (count == 1)
    {
      stopwatch.start("First iteration");
    }
    for (int i = 0; i < edgesToHandle.size(); i++)
    {
      if (i != currentVertex)
      {
        weight = g.getWeight(edgesToHandle[i].first, edgesToHandle[i].second);
        if (weight < minWeightEdge && !(inMST[edgesToHandle[i].first] && inMST[edgesToHandle[i].second]))
        {
          currentVertex = edgesToHandle[i].first;
          minWeightNode = edgesToHandle[i].second;
          minWeightEdgeIndex = i;
          minWeightEdge = weight;
        }
      }
    }
    if (count == 1)
    {
      stopwatch.stop();
    }
    inMST[minWeightNode] = 1;
    count++;
    g.addNeighbor(currentVertex, minWeightNode);
    for (int node = 0; node < numVertices; node++)
    {
      if (!(inMST[node] && inMST[node]) && node != minWeightNode)
      {
        edgesToHandle.push_back(make_pair(minWeightNode, node));
      }
    }
    edgesToHandle.erase(edgesToHandle.begin() + minWeightEdgeIndex);
  }
}

// // pair<GraphC, vector<double>> ReadWeightedGraph(Graph &graph, vector<int> &S)
// // {
// //   int numVertices = S.size();
// //   GraphC G(numVertices);

// //   vector<double> cost(numVertices * (numVertices - 1) / 2);
// //   try
// //   {
// //     for (int i = 0; i < numVertices; i++)
// //     {
// //       for (int j = i + 1; j < numVertices; j++)
// //       {
// //         G.AddEdge(i, j); // Need to be 0-indexed, but if S = [1,4,5] then an edge in G is (0,1) = (S[0], S[1]) = (1,4) in graph
// //         cost[G.GetEdgeIndex(i, j)] = graph.getWeight(S[i], S[j]);
// //       }
// //     }
// //   }
// //   catch (const char *msg)
// //   {
// //   }

// //   return make_pair(G, cost);
// // }

// // int minimum_weight_matching(Graph &graph, vector<int> &S)
// // {
// //   Stopwatch stopwatch = Stopwatch();

// //   // OBS Example Min-Weight Matching from https://github.com/dilsonpereira/Minimum-Cost-Perfect-Matching/blob/master/Graph.h
// //   GraphC G;
// //   vector<double> cost;

// //   // Read the graph
// //   stopwatch.start("ReadWeightedGraph");
// //   pair<GraphC, vector<double>> p = ReadWeightedGraph(graph, S);
// //   stopwatch.stop();
// //   // pair< GraphC, vector<double> > p = CreateRandomGraph();
// //   G = p.first;
// //   cost = p.second;

// //   // for (int i = 0; i < G.GetNumEdges(); i++)
// //   // {
// //   // 	pair<int, int> e = G.GetEdge(i);
// //   // }
// //   // Create a Matching instance passing the graph
// //   stopwatch.start("Matching M(G)");
// //   Matching M(G);
// //   stopwatch.stop();

// //   // Pass the costs to solve the problem
// //   stopwatch.start("SolveMinimumCostPerfectMatching");
// //   pair<list<int>, double> solution = M.SolveMinimumCostPerfectMatching(cost);
// //   stopwatch.stop();

// //   stopwatch.start("line 100");
// //   list<int> matching = solution.first;
// //   double obj = solution.second;
// //   stopwatch.stop();

// //   stopwatch.start("Copying result to our graph");
// //   for (list<int>::iterator it = matching.begin(); it != matching.end(); it++)
// //   {
// //     pair<int, int> e = G.GetEdge(*it);

// //     graph.addNeighbor(S[e.first], S[e.second]);
// //   }
// //   stopwatch.stop();
// //   return 0;
// // }

vector<int> eulerian_tour(Graph &g)
{
  vector<vector<int>> edges = g.getAdjacencyList();
  stack<int> currentPath;
  vector<int> eulerianTour;
  int currentNode = 0;

  currentPath.push(currentNode);
  while (!currentPath.empty())
  {
    vector<int> neighbors = g.getNeighbors(currentNode);
    if (!neighbors.empty())
    {
      int nextNode = neighbors[0];
      currentPath.push(nextNode);
      g.removeNeighbor(currentNode, nextNode); // mark as visited!
      currentNode = nextNode;
    }
    else
    { // neighbors were empty, do backtracking!
      currentNode = currentPath.top();
      currentPath.pop();
      eulerianTour.push_back(currentNode);
    }
  }

  if (DEBUG)
  {
    // Now printed in main
    cout << "EULERIAN TOUR: " << endl;
    for (int i = 0; i < eulerianTour.size(); i++)
    {
      cout << eulerianTour[i] << " -> ";
    }
  }

  return eulerianTour;
}

// int minimum_weight_matching(Graph &graph, vector<int> &S) {

//   // OBS Example Min-Weight Matching from https://github.com/dilsonpereira/Minimum-Cost-Perfect-Matching/blob/master/Graph.h
//   GraphC G;
// 	vector<double> cost;
// 	Stopwatch stopwatch = Stopwatch();
//   stopwatch.start("ReadWeightedGraph");
// 	//Read the graph
// 	pair< GraphC, vector<double> > p = ReadWeightedGraph(graph, S);
//   stopwatch.stop();

// 	//pair< GraphC, vector<double> > p = CreateRandomGraph();
// 	G = p.first;
// 	cost = p.second;

//   // for (int i = 0; i < G.GetNumEdges(); i++)
// 	// {
// 	// 	pair<int, int> e = G.GetEdge(i);
// 	// }
// 	//Create a Matching instance passing the graph
//   stopwatch.start("Matching(G)");
// 	Matching M(G);
//   stopwatch.stop();

// 	//Pass the costs to solve the problem
//   stopwatch.start("SolveMinimumCostPerfectMatching");
// 	pair< list<int>, double > solution = M.SolveMinimumCostPerfectMatching(cost);
//   stopwatch.stop();

// 	list<int> matching = solution.first;
// 	double obj = solution.second;
//   stopwatch.start("Add edges to graph");
// 	for(list<int>::iterator it = matching.begin(); it != matching.end(); it++)
// 	{
// 		pair<int, int> e = G.GetEdge( *it );

//     graph.addNeighbor(S[e.first], S[e.second]);
// 	}
//   stopwatch.stop();
//     return 0;
// }

TSPSolution tsp_tour(vector<int> &eularianTour, Graph &g)
{

  int eulerian_tour_size = eularianTour.size();
  int n = g.getN();
  TSPSolution tspSolution = TSPSolution(n);
  vector<int> visited(n, 0);
  int count = 0;
  for (int i = 0; i < eulerian_tour_size; i++)
  { // Iterate through eularian tour.
    if (visited[eularianTour[i]] == 1)
    {
      continue;
    }
    tspSolution.tour[count] = eularianTour[i];
    count++;
    tspSolution.cost += g.getWeight(eularianTour[i], eularianTour[(i + 1) % n]);
    visited[eularianTour[i]] = 1;
  }

  if (DEBUG)
  {
    // Now printed in main
    cout << "TSP TOUR: " << endl;
    for (int i = 0; i < tspSolution.tour.size(); i++)
    {
      cout << tspSolution.tour[i] << " -> ";
    }
  }

  return tspSolution;
}

// TEMPORARY HELPER
//  double calculateTourCost(vector<int> tsp_tour, Graph &g){
//    int cost = 0;
//    for(int i = 0; i < tsp_tour.size(); i++){
//      cost += g.getWeight(tsp_tour[i], tsp_tour[(i+1) % tsp_tour.size()]);
//    }
//    return cost;
//  }



vector<int> hungarianMatching(Graph &g, vector<int> &right, vector<int> &left){
  vector<WeightedBipartiteEdge> allEdges;
  for (int i = 0; i < left.size(); i++)
  {
    for (int j = 0; j < right.size(); j++)
    {
      allEdges.push_back(WeightedBipartiteEdge(i, j, g.getWeight(left[i], right[j])));
    }
  }
  return hungarianMinimumWeightPerfectMatching(right.size(), allEdges);
}



void hungarian(Graph &g){
  vector<int> S;
  vector<int> right;
  vector<int> left;
  vector<int> right2;
  vector<int> left2;
  for (int i = 0; i < g.getN(); i++)
  {
    if (g.getNeighbors(i).size() % 2 != 0)
    {
      S.push_back(i);
    }
  }

  //Partition every other node into left and right
  for (int i = 0; i < S.size(); i++)
  {
    if (i % 2 == 0)
    {
      right.push_back(S[i]);
    }
    else
    {
      left.push_back(S[i]);
    }
  }
  //Partition the first half of S into left and the second half into right
  for (int i = 0; i < S.size(); i++){
    if (i < S.size()/2){
      left2.push_back(S[i]);
    }
    else{
      right2.push_back(S[i]);
    }
  }
  vector<int> hungarianMatch = hungarianMatching(g, right, left);
  vector<int> hungarianMatch2 = hungarianMatching(g, right2, left2);
  int cost1 = 0;
  int cost2 = 0;
  for (int i = 0; i < hungarianMatch.size(); i++){
    cost1 += g.getWeight(left[i], right[hungarianMatch[i]]);
  }
  for (int i = 0; i < hungarianMatch2.size(); i++){
    cost2 += g.getWeight(left2[i], right2[hungarianMatch2[i]]);
  }
  // cout << "cost1: " << cost1 << endl;
  // cout << "cost2: " << cost2 << endl;

  if (cost1 < cost2){
    // cout << "using cost1" << endl;
  for (int i = 0; i < hungarianMatch.size(); i++)
    {
      g.addNeighbor(left[i], right[hungarianMatch[i]]);
    }
  }
  else{
    // cout << "using cost2" << endl;
    for (int i = 0; i < hungarianMatch2.size(); i++)
    {
      g.addNeighbor(left2[i], right2[hungarianMatch2[i]]);
    }
  }

}

void oldhungarian(Graph &g){
  vector<WeightedBipartiteEdge> allEdges;
  vector<int> right;
  vector<int> left;
  int count = 0;
  for (int i = 0; i < g.getN(); i++)
  {
    if (g.getNeighbors(i).size() % 2 != 0)
    {
      // Varannan vänster, höger
      if (count % 2 == 0)
      {
        // Jämn => Höger
        right.push_back(i);
      }
      else
      {
        // Udda => Vänster
        left.push_back(i);
      }
      count++;
    }
  }

  for (int i = 0; i < left.size(); i++)
  {
    for (int j = 0; j < right.size(); j++)
    {
      allEdges.push_back(WeightedBipartiteEdge(i, j, g.getWeight(left[i], right[j])));
    }
  }

  vector<int> hungarianMatch = hungarianMinimumWeightPerfectMatching(right.size(), allEdges);
  for (int i = 0; i < hungarianMatch.size(); i++)
  {
    g.addNeighbor(left[i], right[hungarianMatch[i]]);
  }

}

TSPSolution christofides(Graph &g)
{

  // Run prims algorithm to get neighbourlist
  prims(g);
  // Create S = { i : len(neightbours(i)) % 2 != 0 }
  hungarian(g);
  // Add new edges to neighbourlist (duplicates allowed) to get multigraph

  // Generate Eularian tour from multigraph with duplicate edges
  vector<int> eulerianTour = eulerian_tour(g);
  // Generate TSP tour from Eularian tour
  TSPSolution christofidesSolution = tsp_tour(eulerianTour, g);
  

  
  // TSPSolution twoOptSol = twoOpt(christofidesSolution, g);
  // vector<int> path = twoOptSol.tour;
  // cout << "Cost for two opt: " << twoOptSol.cost << endl;
  // int thecost = 0;
  // path = christofidesSolution.tour;
  // cout << "Tour before three opt:" << endl; 
  // for (int i = 0; i < path.size()-1; i++) {
    
  //   cout << path[i] << "->";
  //   thecost += g.getWeight(path[i], path[i+1]);
  // }
  // cout << path[path.size()-1] << ".\nCost: " << thecost << endl;
  // thecost = 0; 

  // threeOpt(christofidesSolution, g);
  // cout << "Cost for three opt: " << christofidesSolution.cost << endl;
  // path = christofidesSolution.tour;
  // for (int i = 0; i < path.size()-1; i++) {
  //   cout << path[i] << "->";
  //   thecost += g.getWeight(path[i], path[i+1]);
  // }
  // cout << path[path.size()-1] << ".\nCost: " << thecost << endl;



  // cout << "MATRIX: " << endl; 
  // g.printWeightMatrix();
  // stopwatch.start("Simmulated Annealing with Two opt");
  // TSPSolution localImpr = simmulated_annealing_with_twoOpt(christofidesSolution, g);
  // stopwatch.stop();

  // cout << "cost with simmulated annealing: " << localImpr.cost << endl;
  // cout << "cost before regular two opt: " << christofidesSolution.cost << endl;
  // TSPSolution twoOptSol = twoOpt(christofidesSolution, g);

  // cout << "cost with two opt only: " << twoOptSol.cost << endl;
  // TSPSolution localImpr = twoOpt(christofidesSolution, g);
  // cout << "final cost: " << localImpr.cost << endl;
  return christofidesSolution;
}

// // // SAVING OLD CHRISTOFIDES HERE JUST IN CASE.
// // TSPSolution christofides(Graph &g) {
// //     Stopwatch stopwatch = Stopwatch();
// //     stopwatch.start("Prims");
// //     // Run prims algorithm to get neighbourlist
// //     prims(g);
// //     stopwatch.stop();
// //     // Create S = { i : len(neightbours(i)) % 2 != 0 }
// //     stopwatch.start("Create S");
// //     vector<int> S;
// //     for(int i = 0; i < g.getN(); i++){
// //         if(g.getNeighbors(i).size() % 2 != 0){
// //             S.push_back(i);
// //         }
// //     }
// //     stopwatch.stop();
// //     // Find minimum weight matching M in S
// //     stopwatch.start("Minimum weight matching");
// //     minimum_weight_matching(g, S);
// //     stopwatch.stop();
// //     // Add new edges to neighbourlist (duplicates allowed) to get multigraph

// //     // Generate Eularian tour from multigraph with duplicate edges
// //     stopwatch.start("Eulerian tour");
// //     vector<int> eulerianTour = eulerian_tour(g);
// //     stopwatch.stop();
// //     // Generate TSP tour from Eularian tour
// //     stopwatch.start("TSP tour");
// //     TSPSolution christofidesSolution = tsp_tour(eulerianTour, g);
// //     stopwatch.stop();

// //     return christofidesSolution;
// // }