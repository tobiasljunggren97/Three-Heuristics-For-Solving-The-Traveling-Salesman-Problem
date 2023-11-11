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

void generateRandomVector(vector<int> &randomVector, int size, int min, int max)
{
    for(int i = 0; i < size; i++)
    {
        int random = rand() % max + min;
        while(find(randomVector.begin(), randomVector.end(), random) != randomVector.end())
        {
            random = rand() % max + min;
        }
        randomVector.push_back(random);
    }
}

int main() {
    //Initializing Graph will read input and create weight matrix
    Stopwatch stopwatch = Stopwatch();
    Graph g = Graph();
    // TSPSolution solution1 = nearestNeighbor(g, 0);
    // TSPSolution solution2 = nearestNeighbor(g, g.getN() / 2);
    // TSPSolution solution3 = nearestNeighbor(g, g.getN() - 1);
    
    TSPSolution solution;
    TSPSolution bestSolution;
    bestSolution.cost = numeric_limits<int>::max();

    // New vector a of size 10

    vector<int> randomVector;
    generateRandomVector(randomVector, g.getN(), 0, g.getN());
    for (int i = 0; i < g.getN(); i++) {
        solution = nearestNeighbor(g, randomVector[i]);
        if (solution.cost < bestSolution.cost) {
            bestSolution = solution;
        }
    }
    printSolution(bestSolution, g);
    // if(solution1.cost < solution2.cost && solution1.cost < solution3.cost) {
    //     printSolution(solution1, g);
    // } else if(solution2.cost < solution1.cost && solution2.cost < solution3.cost) {
    //     printSolution(solution2, g);
    // } else {
    //     printSolution(solution3, g);
    // }

    

    return 0;
}


