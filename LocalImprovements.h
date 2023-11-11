#ifndef LOCALIMPROVEMENTS_H
#define LOCALIMPROVEMENTS_H
#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <iomanip>

#include "TSPSolution.h"
#include "Graph.h"
#include <algorithm>
TSPSolution twoOpt (TSPSolution solution, Graph &graph);
TSPSolution simmulated_annealing_with_twoOpt(TSPSolution solution, Graph &g); 

#endif // LOCALIMPROVEMENTS_H