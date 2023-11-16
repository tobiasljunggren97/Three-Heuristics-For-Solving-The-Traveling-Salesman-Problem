#include <gtest/gtest.h>
#include "../main.h"
#include "../Graph.h"
#include "../Christofides.h"
#include "../Greedy.h"
#include "../Naive.h"
#include "../LocalImprovements.h"
using namespace std;
#define TEST_INPUT_DIR "../../test/greedyTourInputs/"


int calculateCost(vector<int> &solution, Graph &g) {
    int cost = 0;
    int N = g.getN();

    for (int i = 0; i < N-1; i++) {
        cost += g.getWeight(i, i+1);
    }
    cost += g.getWeight(0, solution[solution.size()-1]);
    return cost;
}


TEST(GraphClassTests, TestingTwoOpt50NodesImprovesNNSolution) {
    string filename = TEST_INPUT_DIR "50nodes1.txt";
    Graph g = Graph(filename);

    TSPSolution solSimple = greedy(g);

    TSPSolution solTwoOpt = twoOpt(solSimple, g);

    int solSimpleCost = calculateCost(solSimple.tour, g);
    // int solTwoOpt = calculateCost(solTwoOpt, )

    EXPECT_GE()







}
