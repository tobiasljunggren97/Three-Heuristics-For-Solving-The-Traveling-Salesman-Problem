#ifndef CHRISTOFIDES_H
#define CHRISTOFIDES_H
#include <stack>
#include "Graph.h"
#include "TSPSolution.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include "GraphChristofides.h"
#include "MatchingChristofides.h"
#include <tuple>
#include "Stopwatch.h"
// Only list signatures of the functions that main.cpp needs to call
TSPSolution christofides(Graph &g);
void prims(Graph &g);

int minimum_weight_matching(Graph &graph, vector<int> &S);

vector<int> eulerian_tour(Graph &g); 

TSPSolution tsp_tour(vector<int> &eulerian_tour, Graph &g);



#endif