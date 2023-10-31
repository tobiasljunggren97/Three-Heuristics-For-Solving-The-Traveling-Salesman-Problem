#ifndef CHRISTOFIDES_H
#define CHRISTOFIDES_H

#include "Graph.h"
#include "TSPSolution.h"
// Only list signatures of the functions that main.cpp needs to call
TSPSolution christofides(Graph &g);
void prims(Graph &g);

int minimum_weight_matching(Graph &graph, vector<int> &S);

#endif