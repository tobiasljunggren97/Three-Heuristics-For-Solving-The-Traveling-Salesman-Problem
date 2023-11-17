#include <gtest/gtest.h>
#include "../main.h"
#include "../Graph.h"
#include "../Christofides.h"
#include "../Greedy.h"
#include "../Naive.h"
#include "../LocalImprovements.h"
using namespace std;
#define TEST_INPUT_DIR "../../test/greedyTourInputs/"

int calcCost(vector<int> &solution, Graph &g)
{
    int cost = 0;
    int N = g.getN();

    for (int i = 0; i < N - 1; i++)
    {
        cost += g.getWeight(i, i + 1);
    }
    cost += g.getWeight(0, solution[solution.size() - 1]);
    return cost;
}

// 5

TEST(GraphClassTests, TestingTwoOpt5NodesImprovesNNSolution1)
{
    string filename = TEST_INPUT_DIR "5nodes1.txt";
    Graph g = Graph(filename);

    TSPSolution solSimple = nearestNeighbor(g, 0);

    TSPSolution solTwoOpt = twoOpt(solSimple, g);

    int solSimpleCost = calcCost(solSimple.tour, g);
    int solTwoOptCost = calcCost(solTwoOpt.tour, g);
    EXPECT_LE(solTwoOptCost, solSimpleCost);
}

TEST(GraphClassTests, TestingTwoOpt5NodesImprovesNNSolution2)
{
    string filename = TEST_INPUT_DIR "5nodes2.txt";
    Graph g = Graph(filename);

    TSPSolution solSimple = nearestNeighbor(g, 0);

    TSPSolution solTwoOpt = twoOpt(solSimple, g);

    int solSimpleCost = calcCost(solSimple.tour, g);
    int solTwoOptCost = calcCost(solTwoOpt.tour, g);
    EXPECT_LE(solTwoOptCost, solSimpleCost); 
}

TEST(GraphClassTests, TestingTwoOpt5NodesImprovesNNSolution3)
{
    string filename = TEST_INPUT_DIR "5nodes3.txt";
    Graph g = Graph(filename);

    TSPSolution solSimple = nearestNeighbor(g, 0);

    TSPSolution solTwoOpt = twoOpt(solSimple, g);

    int solSimpleCost = calcCost(solSimple.tour, g);
    int solTwoOptCost = calcCost(solTwoOpt.tour, g);
    EXPECT_LE(solTwoOptCost, solSimpleCost);
}

// 50 NODES:

TEST(GraphClassTests, TestingTwoOpt50NodesImprovesNNSolution1)
{
    string filename = TEST_INPUT_DIR "50nodes1.txt";
    Graph g = Graph(filename);

    TSPSolution solSimple = nearestNeighbor(g, 0);

    TSPSolution solTwoOpt = twoOpt(solSimple, g);

    int solSimpleCost = calcCost(solSimple.tour, g);
    int solTwoOptCost = calcCost(solTwoOpt.tour, g);
    EXPECT_LE(solTwoOptCost, solSimpleCost);
}

TEST(GraphClassTests, TestingTwoOpt50NodesImprovesNNSolution2)
{
    string filename = TEST_INPUT_DIR "50nodes2.txt";
    Graph g = Graph(filename);

    TSPSolution solSimple = nearestNeighbor(g, 0);

    TSPSolution solTwoOpt = twoOpt(solSimple, g);

    int solSimpleCost = calcCost(solSimple.tour, g);
    int solTwoOptCost = calcCost(solTwoOpt.tour, g);
    EXPECT_LE(solTwoOptCost, solSimpleCost);
}

TEST(GraphClassTests, TestingTwoOpt50NodesImprovesNNSolution3)
{
    string filename = TEST_INPUT_DIR "50nodes3.txt";
    Graph g = Graph(filename);

    TSPSolution solSimple = nearestNeighbor(g, 0);

    TSPSolution solTwoOpt = twoOpt(solSimple, g);

    int solSimpleCost = calcCost(solSimple.tour, g);
    int solTwoOptCost = calcCost(solTwoOpt.tour, g);
    EXPECT_LE(solTwoOptCost, solSimpleCost);
}

// 250 NODES:

TEST(GraphClassTests, TestingTwoOpt250NodesImprovesNNSolution1)
{
    string filename = TEST_INPUT_DIR "250nodes1.txt";
    Graph g = Graph(filename);

    TSPSolution solSimple = nearestNeighbor(g, 0);

    TSPSolution solTwoOpt = twoOpt(solSimple, g);

    int solSimpleCost = calcCost(solSimple.tour, g);
    int solTwoOptCost = calcCost(solTwoOpt.tour, g);
    EXPECT_LE(solTwoOptCost, solSimpleCost);
}

TEST(GraphClassTests, TestingTwoOpt250NodesImprovesNNSolution2)
{
    string filename = TEST_INPUT_DIR "250nodes2.txt";
    Graph g = Graph(filename);

    TSPSolution solSimple = nearestNeighbor(g, 0);

    TSPSolution solTwoOpt = twoOpt(solSimple, g);

    int solSimpleCost = calcCost(solSimple.tour, g);
    int solTwoOptCost = calcCost(solTwoOpt.tour, g);
    EXPECT_LE(solTwoOptCost, solSimpleCost);
}

TEST(GraphClassTests, TestingTwoOpt250NodesImprovesNNSolution3)
{
    string filename = TEST_INPUT_DIR "250nodes3.txt";
    Graph g = Graph(filename);

    TSPSolution solSimple = nearestNeighbor(g, 0);

    TSPSolution solTwoOpt = twoOpt(solSimple, g);

    int solSimpleCost = calcCost(solSimple.tour, g);
    int solTwoOptCost = calcCost(solTwoOpt.tour, g);
    EXPECT_LE(solTwoOptCost, solSimpleCost);
}

// 1000 NODES:

TEST(GraphClassTests, TestingTwoOpt1000NodesImprovesNNSolution1)
{
    string filename = TEST_INPUT_DIR "1000nodes1.txt";
    Graph g = Graph(filename);

    TSPSolution solSimple = nearestNeighbor(g, 0);

    TSPSolution solTwoOpt = twoOpt(solSimple, g);

    int solSimpleCost = calcCost(solSimple.tour, g);
    int solTwoOptCost = calcCost(solTwoOpt.tour, g);
    EXPECT_LE(solTwoOptCost, solSimpleCost);
}

TEST(GraphClassTests, TestingTwoOpt1000NodesImprovesNNSolution2)
{
    string filename = TEST_INPUT_DIR "1000nodes2.txt";
    Graph g = Graph(filename);

    TSPSolution solSimple = nearestNeighbor(g, 0);

    TSPSolution solTwoOpt = twoOpt(solSimple, g);

    int solSimpleCost = calcCost(solSimple.tour, g);
    int solTwoOptCost = calcCost(solTwoOpt.tour, g);
    EXPECT_LE(solTwoOptCost, solSimpleCost);
}

TEST(GraphClassTests, TestingTwoOpt1000NodesImprovesNNSolution3)
{
    string filename = TEST_INPUT_DIR "1000nodes3.txt";
    Graph g = Graph(filename);

    TSPSolution solSimple = nearestNeighbor(g, 0);

    TSPSolution solTwoOpt = twoOpt(solSimple, g);

    int solSimpleCost = calcCost(solSimple.tour, g);
    int solTwoOptCost = calcCost(solTwoOpt.tour, g);
    EXPECT_LE(solTwoOptCost, solSimpleCost);
}
