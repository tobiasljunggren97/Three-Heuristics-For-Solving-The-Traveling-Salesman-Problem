#ifndef LOCALIMPROVEMENTS_H
#define LOCALIMPROVEMENTS_H
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

#include "TSPSolution.h"
#include "Graph.h"
#include <algorithm>
TSPSolution twoOpt (TSPSolution solution, Graph &graph);

#endif // LOCALIMPROVEMENTS_H