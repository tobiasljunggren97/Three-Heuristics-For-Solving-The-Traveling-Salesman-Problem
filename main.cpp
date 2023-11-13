#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <tuple>
#include "main.h"
#include <algorithm>
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
        while(std::find(randomVector.begin(), randomVector.end(), random) != randomVector.end())
        {
            random = rand() % max + min;
        }
        randomVector.push_back(random);
    }
}


TSPSolution tinyGraphEdgeCase(Graph &g){
    int n = g.getN();
    if(n == 2){
        TSPSolution solution;
        solution.tour = vector<int>(n);
        solution.cost = 0;
        solution.tour[0] = 0;
        solution.tour[1] = 1;
        solution.cost = g.getWeight(0, 1);
        return solution;
    } else {
        TSPSolution solution;
        solution.tour = vector<int>(n);
        solution.cost = 0;
        solution.tour[0] = 0;
        return solution;
    }
}

int main() {
    //Initializing Graph will read input and create weight matrix
    //Stopwatch stopwatch = Stopwatch();
    Graph g = Graph();

    //EDGE CASE, < 3 NODES
    if(g.getN() < 3){
        TSPSolution solution = tinyGraphEdgeCase(g);
        printSolution(solution, g);
        return 0;
    }
    TSPSolution solution;
    TSPSolution bestNNSolution;
    bestNNSolution.cost = numeric_limits<int>::max();

    int size = 25 > g.getN() ? g.getN() : 25;

    vector<int> randomVector;

    generateRandomVector(randomVector, size, 0, g.getN());
    for (int i = 0; i < size; i++) {
        solution = nearestNeighbor(g, randomVector[i]);
        if (solution.cost < bestNNSolution.cost) {
            bestNNSolution = solution;
        }
    }
    TSPSolution greedySolution;
    greedySolution = greedy(g);
    if (greedySolution.cost < bestNNSolution.cost) {
        printSolution(greedySolution, g);
    } else {
        printSolution(bestNNSolution, g);
    }

    return 0;
}

