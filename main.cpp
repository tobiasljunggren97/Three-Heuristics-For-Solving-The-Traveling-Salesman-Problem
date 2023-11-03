#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <tuple>
#include "main.h"
#include "TSPSolution.h"

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
    Graph g = Graph();
    TSPSolution christofidesSolution = christofides(g);  
    printSolution(christofidesSolution, g);
    return 0;
}


