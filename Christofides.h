#ifndef CHRISTOFIDES_H
#define CHRISTOFIDES_H
#include <stack>
#include "Graph.h"
// Only list signatures of the functions that main.cpp needs to call
int christofides(Graph &g);

int minimum_weight_matching(Graph &graph, vector<int> &S);

vector<int> eulerian_tour(Graph &g); 

vector<int> tsp_tour(vector<int> &eulerian_tour);

#endif