#ifndef CHRISTOFIDES_H
#define CHRISTOFIDES_H

#include "Graph.h"
// Only list signatures of the functions that main.cpp needs to call
int christofides(Graph &g);

int minimum_weight_matching(Graph &graph, vector<int> &S);

#endif