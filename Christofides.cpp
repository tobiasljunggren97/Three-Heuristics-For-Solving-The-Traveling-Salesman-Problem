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

int setup_edges(Graph &g, vector<vector<int>> &edges) {
  cout << "OKAY SOMETHING FISHY IS GOING ON IN ADJACENCY LIST, LET'S FIND OUT WHAT >: (" << endl; 
  cout << "what is adjacency-list now?? " << endl; 
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
      cout << i << " -- " << adj_lst[i][j] << " has edge " << endl; 
    }
    
  }
  return edgesLeft;
}


vector<int> eularian_tour(Graph &g) {
  vector<vector<int>> edges; 
  int totalNrEdges = setup_edges(g, edges); 
  // cout << "what is size of edges after setup ?? "  << edges.size() << endl; 

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
    // cout << "EULARIAN TOUR: " << endl; 
    // for (int i = 0; i < eularian_tour.size(); i++) {
    //   cout << " -> " << eularian_tour[i]; 
    // }

  return eularian_tour; 
}




// vector<int> eularian_tour(Graph &g) {
//   vector<vector<int>> edges; 
//   setup_edges(g, edges); 

//   Graph gt = g; 
//   vector<vector<int>> adj_lst = gt.getAdjacencyList(); 
//   vector<vector<int>> edges_left = adj_lst; 

//   cout << "INSIDE CRISTOFIDES EULARIAN TOUR!! WHAT DOES GT.MATRIX LOOK LIKE? " << endl; 
//   gt.printWeightMatrix();
//   int totalNrEdges = 0; 
//   for (int i = 0; i < edges_left.size(); i++)
//   {
//     totalNrEdges = totalNrEdges + edges_left[i].size(); 
//   }

//   vector<int> eularian_tour; 
//   int notFinished = 1; 
//   int currentNode = 0; 
//   vector<int> neighbors; 
//   //eularian_tour.push_back(0); 
//   while(notFinished) 
//   {

// keep_going: 
//     neighbors = g.getNeighbors(currentNode); 
//     // cout << "what is size of neighbors ? " << neighbors.size() << endl;
//     // cout << "What is current node? " << currentNode << endl; 
//     // for (int i = 0; i < neighbors.size(); i++)
//     // {
//     //   cout << "neighbor nr " << i << ":  " << neighbors[i] << endl; 
//     // }
//     cout << "WHILE LOOP, WHAT DOES MATRIX LOOK LIKE?" << endl; 
//     gt.printWeightMatrix(); 
//     for (int i = 0; i < neighbors.size(); i++)
//     {  
//       // cout << "what is weight for gt.getWeight(currentNode, neighbors[i]) between " << currentNode << " and " << neighbors[i] << " ? " << gt.getWeight(currentNode, neighbors[i]) << endl; 
//       // cout << "VS" << endl; 
//       // cout << "what is weight for g.getWeight(currentNode, neighbors[i]) between " << currentNode << " and " << neighbors[i] << " ? " << g.getWeight(currentNode, neighbors[i]) << endl; 
//       if (gt.getWeight(currentNode, neighbors[i]) > 0) {
//           cout << "OMG WE FOUND AN EDGE: " << currentNode << "  --- " << neighbors[i] << endl; 
//           eularian_tour.push_back(currentNode); 
//           gt.setWeight(currentNode, neighbors[i], -1);
//           totalNrEdges--; 
//           currentNode = neighbors[i]; 
//           goto keep_going; 
//       }

//     }    
//     if (totalNrEdges > 0) {
//       cerr << "could not find path from node: " << currentNode << " to any of its neighbors, but there exist paths we haven't crossed yet." << endl; 
//       break; 
//     }
//     else if (totalNrEdges == 0) {
//       notFinished = 0; 
//     }
//   }
//     cout << "EULARIAN TOUR: " << endl; 
//     for (int i = 0; i < eularian_tour.size(); i++) {
//       cout << " -> " << eularian_tour[i]; 
//     }

//   return eularian_tour; 
// }




// vector<int> eularian_tour(Graph &g) {
//   vector<vector<int>> adj_lst = g.getAdjacencyList(); 
//   vector<vector<int>> edges_left = adj_lst; 
//   int totalNrEdges = 0; 
//   for (int i = 0; i < edges_left.size(); i++)
//   {
//     totalNrEdges = totalNrEdges + edges_left[i].size(); 
//   }

//   vector<int> eularian_tour; 
//   int notFinished = 1; 
//   int currentNode = 0; 
//   vector<int> neighbors; 
//   //eularian_tour.push_back(0); 
//   while(notFinished) 
//   {

// keep_going: 
//     neighbors = g.getNeighbors(currentNode); 
//     cout << "what is size of neighbors ? " << neighbors.size() << endl;
//     cout << "What is current node? " << currentNode << endl; 
//     for (int i = 0; i < neighbors.size(); i++)
//     {
//       cout << "neighbor nr " << i << ":  " << neighbors[i] << endl; 
//     }
     
//     for (int i = 0; i < neighbors.size(); i++)
//     {  

//       // cout << "what is currentnode? " << currentNode << endl; 
//       cout << "what is neighbor? " << neighbors[i] << endl; 
//       for (int j = 0; j < edges_left[currentNode].size(); j++)
//       {
//         cout << "what is edges_left[currentNode][" << j << "]" << edges_left[currentNode][j] << endl; 
//         if (edges_left[currentNode][j] == neighbors[i] || edges_left[j][currentNode] == neighbors[i]) { // there still exist an edge between current node and neighbors that we haven't crossed yet. 
//           cout << "OMG WE FOUND AN EDGE: " << currentNode << "  --- " << neighbors[i] << endl; 
//           eularian_tour.push_back(currentNode); 
//           edges_left[currentNode][j] = -1; // go through that edge. 
//           edges_left[neighbors[i]][j] = -1; 
//           totalNrEdges--; 
//           currentNode = neighbors[i]; 
//           goto keep_going; 
//         }
//       }
//     }    
//     if (totalNrEdges > 0) {
//       cerr << "could not find path from node: " << currentNode << " to any of its neighbors, but there exist paths we haven't crossed yet." << endl; 
//       break; 
//     }
//     else if (totalNrEdges == 0) {
//       notFinished = 0; 
//     }
//   }
//       cout << "EULARIAN TOUR: " << endl; 
//     for (int i = 0; i < eularian_tour.size(); i++) {
//       cout << " -> " << eularian_tour[i]; 
//     }

//   return eularian_tour; 
// }



// // // THIS IS THE LATEST ONE VENDELA 
// // /*Expected input: A graph object g whose adjacency list consists of an MST together with added edges from minweight perfect match. 
// // And thus, all nodes should have an even degree. */
// // vector<int> eulerian_tour(Graph g) {
// //     cout << "DO WE ENTER EULERIAN TOUR?!!" << endl; 
// //     cout << "omg perfect, then, what is our current graph? " << endl; 
// //     g.printWeightMatrix();
// //     vector<int> eularianTour; 
// //     int n = g.getN();
// //     vector<int> visited(n, 0);
// //     // visited[0] = 1; // Start by visiting first node. 
// //     int notFinished = 1; 
// //     int currentNode = 0; 
// //     int previousNode = -1; 
// //     int reverse = 0; 
// //     while(notFinished) {
// //       cout << "************************************************" << endl; 
// //       cout<< "current node: " << currentNode << endl; 
// //       eularianTour.push_back(currentNode);
// //       visited[currentNode] = 1;  
// //       vector<int> neighbors = g.getNeighbors(currentNode);
// //       notFinished = 0; 

// //       for (int i = 0; i < neighbors.size(); i++)
// //       {
// //         if (visited[neighbors[i]] == 0) { 
// //           cout << "What is current neighbor? " << neighbors[i] << endl; 
// //           cout << "visited[neighbors[i]]: " << visited[neighbors[i]] << endl; 
// //           cout << "previousNode: " << previousNode << endl; 
// //           previousNode = currentNode;
// //           notFinished = 1;
// //           currentNode = neighbors[i];
// //           reverse = 0; 
// //           break;
// //         }
// //       }
// //       for (int i = 0; i < neighbors.size(); i++)
// //       {
// //         if (neighbors[i] == previousNode && reverse == 0) { 
// //           cout << "AHA! we are going back once. " << endl; 
// //           // cout << "What is current neighbor? " << neighbors[i] << endl; 
// //           // cout << "visited[neighbors[i]]: " << visited[neighbors[i]] << endl; 
// //           // cout << "previousNode: " << previousNode << endl; 
// //           previousNode = currentNode;
// //           notFinished = 1;
// //           currentNode = neighbors[i];
// //           reverse = 1; 
// //           break;
// //         }
// //       }
      
      
// //     }
// //     cout << "EULARIAN TOUR: " << endl; 
// //     for (int i = 0; i < eularianTour.size(); i++) {
// //       cout << " -> " << eularianTour[i]; 
// //     }
    

// //     return eularianTour;
// // } 


// // // /*Expected input: A graph object g whose adjacency list consists of an MST together with added edges from minweight perfect match. 
// // // And thus, all nodes should have an even degree. */
// // // vector<int> eulerian_tour(Graph g) {

// // //     vector<int> eularianTour; 
// // //     int n = g.getN();
// // //     vector<int> visited(n, 0);
// // //     // visited[0] = 1; // Start by visiting first node. 
// // //     int notFinished = 1; 
// // //     int currentNode = 0; 
// // //     while(notFinished) {
// // //       cout << "what is current node? " << currentNode << endl; 
// // //       vector<int> neighbors = g.getNeighbors(currentNode);

// // //       if (visited[currentNode]) { // we have visited this node before. 
// // //         notFinished = 0; // Assume we are finished. 
// // //         for (int i = 0; i < neighbors.size(); i++) { // If we find node not visited, continue. 
// // //           if (visited[neighbors[i]] == 0) { 
// // //             cout << "what is neighbors[i] ?" << neighbors[i] << endl; 
// // //             notFinished = 1; 
// // //             currentNode = neighbors[i]; 
// // //             visited[currentNode] = 1; 
// // //             eularianTour.push_back(currentNode);
// // //             break;
// // //           }
// // //         }
// // //       } else {
// // //         visited[currentNode] = 1; // Visit current node. 
// // //         eularianTour.push_back(currentNode);
// // //       }
      
      
// // //     }
// // //     cout << "EULARIAN TOUR: " << endl; 
// // //     for (int i = 0; i < eularianTour.size(); i++) {
// // //       cout << " -> " << eularianTour[i]; 
// // //     }
    

// // //     return eularianTour;
// // // } 





// NOT THIS ONE!! 
// // // /*Expected input: A graph object g whose adjacency list consists of an MST together with added edges from minweight perfect match. 
// // // And thus, all nodes should have an even degree. */
// // // vector<int> eulerian_tour(Graph g) {

// // //     vector<int> eularianTour; 
// // //     int n = g.getN();
// // //     vector<int> visited(n, 0);
// // //     // visited[0] = 1; // Start by visiting first node. 
// // //     int notFinished = 1; 
// // //     int currentNode = 0; 
// // //     while(notFinished) {
// // //       cout << "what is current node? " << currentNode << endl; 
// // //       vector<int> neighbors = g.getNeighbors(currentNode);

// // //       if (visited[currentNode]) { // we have visited this node before. 
// // //         notFinished = 0; // Assume we are finished. 
// // //         for (int i = 0; i < neighbors.size(); i++) { // If we find node not visited, continue. 
// // //           cout << "what is neighbors[i] ?" << neighbors[i] << endl; 
// // //           vector<int> neighborsNeighbor = g.getNeighbors(neighbors[i]); 
// // //           for (int j = 0; j < neighborsNeighbor.size(); j++)
// // //           {
// // //             if (visited[neighborsNeighbor[j]] == 0) {  // does the neighbor have a neighbor we have not visited? 
// // //               notFinished = 1; 
// // //               currentNode = neighbors[i]; 
// // //               visited[currentNode] = 1; 
// // //               eularianTour.push_back(currentNode);
// // //               break;
// // //             }            
// // //           }
// // //         }
// // //       } else {
// // //         visited[currentNode] = 1; // Visit current node. 
// // //         eularianTour.push_back(currentNode);
// // //       }
      
      
// // //     }
// // //     cout << "EULARIAN TOUR: " << endl; 
// // //     for (int i = 0; i < eularianTour.size(); i++) {
// // //       cout << " -> " << eularianTour[i]; 
// // //     }
    

// // //     return eularianTour;
// // // } 












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
    cout << "what is last element in eulerian tour? " << eularianTour[n-1] << endl; 
    tsp.push_back(eularianTour[n-1]);

    cout << "GENERATED TSP: " << endl;

    for (int i = 0; i < tsp.size(); i++) {
      cout << " -> " << tsp[i]; 
    }
    
    return tsp;
}

int christofides(Graph &g) {

    // cout << "graph with in the beginning: "<< endl; 
    // g.printWeightMatrix();



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
