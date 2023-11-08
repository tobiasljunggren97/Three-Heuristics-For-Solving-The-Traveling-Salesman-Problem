#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <tuple>
#include "main.h"
#include "TSPSolution.h"
#include "Stopwatch.h"

#include <fstream>

using namespace std;

void printSolution(TSPSolution &solution, Graph &g)
{
    int n = solution.tour.size();
    for(int i = 0; i < n; i++)
    {
        cout << solution.tour[i] << endl;
    }
}

int main() {
    //Initializing Graph will read input and create weight matrix
    Stopwatch stopwatch = Stopwatch();
    stopwatch.start("Graph initialization");
    Graph g = Graph();
    stopwatch.stop();
    stopwatch.start("Christofides in total");
    TSPSolution christofidesSolution = christofides(g);  
    stopwatch.stop();
    printSolution(christofidesSolution, g);
    return 0;
}


