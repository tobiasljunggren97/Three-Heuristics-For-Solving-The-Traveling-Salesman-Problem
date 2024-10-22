#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <tuple>
#include "main.h"
#include <algorithm>
#include "TSPSolution.h"
#include "LocalImprovements.h"
#include "Stopwatch.h"

#include <fstream>

using namespace std;
#define NR_OF_RUNS 10

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


void benchmarking(ofstream &myfile, string filename){
    Graph g = Graph(filename);
    Stopwatch stopwatch = Stopwatch(false);
    //Benchmarking NN with random starting points
    
    {
        stopwatch.start("NN with max 25 random starting points");
        
        int runCount = 0;
        int NNcost = 0;
        TSPSolution solution;
        while (runCount < NR_OF_RUNS) {
            TSPSolution bestNNSolution;
            bestNNSolution.cost = numeric_limits<int>::max();

            int size = 25 > g.getN() ? g.getN() : 25;

            vector<int> randomVector;

            generateRandomVector(randomVector, size, 0, g.getN());
            for (int i = 0; i < size; i++) {
                solution = nearestNeighbor(g, randomVector[i]);
                solution = twoOpt(solution, g);
                if (solution.cost < bestNNSolution.cost) {
                    bestNNSolution = solution;
                }
            }
            runCount++;
            NNcost += bestNNSolution.cost;
        }
        double NNWithRandomTime = stopwatch.stop();
        NNWithRandomTime /= NR_OF_RUNS;
        NNcost /= NR_OF_RUNS;
        
        myfile << "NN with max 25 random starting points: " << endl;
        myfile << "Time: " << NNWithRandomTime << endl;
        myfile << "Cost: " << NNcost << endl;

    }

    {
        //Benchmarking NN with 0 as starting point
        TSPSolution solution;
        int runCount = 0;
        stopwatch.start("NN with 0 as starting point");
        while (runCount < NR_OF_RUNS) {
            solution = nearestNeighbor(g, 0);
            solution = twoOpt(solution, g);
            runCount++;
        }
        double NNWithZeroTime = stopwatch.stop();
        NNWithZeroTime /= NR_OF_RUNS;
        myfile << "NN with 0 as starting point: " << endl;
        myfile << "Time: " << NNWithZeroTime << endl;
        myfile << "Cost: " << solution.cost << endl;
    }
    {
        //Benchmarking greedy
        int runCount = 0;
        TSPSolution solution;
        stopwatch.start("Greedy");
        while (runCount < NR_OF_RUNS) {
            solution = greedy(g);
            solution = twoOpt(solution, g);
            runCount++;
        }
        double greedyTime = stopwatch.stop();
        greedyTime /= NR_OF_RUNS;
        myfile << "Greedy: " << endl;
        myfile << "Time: " << greedyTime << endl;
        myfile << "Cost: " << solution.cost << endl;
    }

    {
        //Benchmarking Christofides
        int runCount = 0;
        double totChristTime = 0;
        TSPSolution solution;
        while (runCount < NR_OF_RUNS) {
            Graph f  = Graph(filename);
            stopwatch.start("Christofides");
            solution = christofides(f);
            solution = twoOpt(solution, g);
            totChristTime += stopwatch.stop();
            runCount++;
        }
        totChristTime /= NR_OF_RUNS;
        myfile << "Christofides: " << endl;
        myfile << "Time: " << totChristTime << endl;
        myfile << "Cost: " << solution.cost << endl;
    }
}

// BENCHMARKING MAIN
// int main() {

//     ofstream myfile;
//     myfile.open("benchmarking.txt");
//     myfile << "Benchmarking results" << endl;
//     myfile << "---------------------" << endl;
//     myfile << endl;

//     string fileheader = "../benchmarkingtests/";
//     vector<string> fileendings = {"5nodes1.txt", "5nodes2.txt", "5nodes3.txt", "50nodes1.txt", "50nodes2.txt", "50nodes3.txt", "250nodes1.txt", "250nodes2.txt", "250nodes3.txt", "1000nodes1.txt", "1000nodes2.txt", "1000nodes3.txt"};
//     for(int i = 0; i < fileendings.size(); i++){
//         string filename = fileheader + fileendings[i];
//         cout << "Benchmarking with " << filename << endl;
//         myfile << "Benchmarking with " << filename << endl;
//         benchmarking(myfile, filename);
//         myfile << "---------------------" << endl;

//     }
//     myfile.close();


// }


// MAIN MAIN FUNCTION, FOR KATTIS
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
        solution = twoOpt(solution, g);
        if (solution.cost < bestNNSolution.cost) {
            bestNNSolution = solution;
        }
    }

    printSolution(bestNNSolution, g);
    // TSPSolution greedySolution;
    // greedySolution = greedy(g);
    // if (greedySolution.cost < bestNNSolution.cost) {
    //     printSolution(greedySolution, g);
    // } else {
        // printSolution(bestNNSolution, g);
    // }

    return 0;
}


