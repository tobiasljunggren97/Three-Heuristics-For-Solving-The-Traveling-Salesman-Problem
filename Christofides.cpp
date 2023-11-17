#include "Christofides.h"
#include "hungarian.h"
#include "LocalImprovements.h"

#define DEBUG 0

using namespace std;

// Improved version which contains bugs, but is/should be faster. Keeping it for the interested
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
    if (count == 1)
    {
      stopwatch.stop();
    }
  }
}

// Actual prims used
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

  if (cost1 < cost2){
  for (int i = 0; i < hungarianMatch.size(); i++)
    {
      g.addNeighbor(left[i], right[hungarianMatch[i]]);
    }
  }
  else{
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
      if (count % 2 == 0)
      {
        right.push_back(i);
      }
      else
      {
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
  //1.  Run prims algorithm to get neighbourlist
  //2. Create S = { i : len(neightbours(i)) % 2 != 0 }
  //3. Add new edges to neighbourlist (duplicates allowed) to get multigraph
  //4. Generate Eularian tour from multigraph with duplicate edges
  //5. Generate TSP tour from Eularian tour
  
  prims(g);

  hungarian(g);

  vector<int> eulerianTour = eulerian_tour(g);
  
  TSPSolution christofidesSolution = tsp_tour(eulerianTour, g);
  

  
  TSPSolution twoOptSol = twoOpt(christofidesSolution, g);
  vector<int> path = twoOptSol.tour;
  cout << "Cost for two opt: " << twoOptSol.cost << endl;
  int thecost = 0;
  path = christofidesSolution.tour;
  cout << "Tour before three opt:" << endl; 
  for (int i = 0; i < path.size()-1; i++) {
    cout << path[i] << "->";
    thecost += g.getWeight(path[i], path[i+1]);
  }
  cout << path[path.size()-1] << ".\nCost: " << thecost << endl;
  thecost = 0; 

  threeOpt(christofidesSolution, g);
  cout << "Cost for three opt: " << christofidesSolution.cost << endl;
  path = christofidesSolution.tour;
  for (int i = 0; i < path.size()-1; i++) {
    cout << path[i] << "->";
    thecost += g.getWeight(path[i], path[i+1]);
  }
  cout << path[path.size()-1] << ".\nCost: " << thecost << endl;

  TSPSolution localImpr = twoOpt(christofidesSolution, g);
  // cout << "final cost: " << localImpr.cost << endl;
  return localImpr;
}


