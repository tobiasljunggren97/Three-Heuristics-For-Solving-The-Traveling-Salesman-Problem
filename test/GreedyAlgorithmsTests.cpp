#include <gtest/gtest.h>
#include "../main.h"
#include "../Graph.h"
#include "../Christofides.h"
#include "../Greedy.h"
using namespace std;
#define TEST_INPUT_DIR "../../test/greedyTourInputs/"

TEST(GraphClassTests, TestingGreedy50Nodes){
    Stopwatch stopwatch = Stopwatch(false);
    string filename = TEST_INPUT_DIR "50nodes1.txt";
    stopwatch.start("Greedy 50 nodes 1");
    Graph g = Graph(filename);
    TSPSolution solution = greedy(g);
    double time = stopwatch.stop();
    EXPECT_LE(time, 1);
    EXPECT_TRUE(solution.tour.size() >= 50);

    stopwatch.start("Greedy 50 nodes 2");
    Graph h = Graph(TEST_INPUT_DIR "50nodes2.txt");
    TSPSolution solution2 = greedy(h);
    time = stopwatch.stop();
    EXPECT_LE(time, 1);
    EXPECT_TRUE(solution2.tour.size() >= 50);

    stopwatch.start("Greedy 50 nodes 3");
    Graph i = Graph(TEST_INPUT_DIR "50nodes3.txt");
    TSPSolution solution3 = greedy(i);
    time = stopwatch.stop();
    EXPECT_LE(time, 1);
    EXPECT_TRUE(solution3.tour.size() >= 50);
};

TEST(GraphClassTests, TestingNN50Nodes){
    Stopwatch stopwatch = Stopwatch(false);
    string filename = TEST_INPUT_DIR "50nodes1.txt";
    stopwatch.start("NN 50 nodes 1");
    Graph g = Graph(filename);
    TSPSolution solution = nearestNeighbor(g,0);
    double time = stopwatch.stop();
    EXPECT_LE(time, 1);
    EXPECT_TRUE(solution.tour.size() >= 50);

    stopwatch.start("NN 50 nodes 2");
    Graph h = Graph(TEST_INPUT_DIR "50nodes2.txt");
    TSPSolution solution2 = nearestNeighbor(h,0);
    time = stopwatch.stop();
    EXPECT_LE(time, 1);
    EXPECT_TRUE(solution2.tour.size() >= 50);

    stopwatch.start("NN 50 nodes 3");
    Graph i = Graph(TEST_INPUT_DIR "50nodes3.txt");
    TSPSolution solution3 = nearestNeighbor(i,0);
    time = stopwatch.stop();
    EXPECT_LE(time, 1);
    EXPECT_TRUE(solution3.tour.size() >= 50);
};

TEST(GraphClassTests, TestingGreedy1000Nodes){
    Stopwatch stopwatch = Stopwatch(false);
    string filename = TEST_INPUT_DIR "1000nodes1.txt";
    stopwatch.start("Greedy 1000 nodes 1");
    Graph g = Graph(filename);
    TSPSolution solution = greedy(g);
    double time = stopwatch.stop();
    EXPECT_LE(time, 3);
    EXPECT_TRUE(solution.tour.size() >= 1000);

    stopwatch.start("Greedy 1000 nodes 2");
    Graph h = Graph(TEST_INPUT_DIR "1000nodes2.txt");
    TSPSolution solution2 = greedy(h);
    time = stopwatch.stop();
    EXPECT_LE(time, 3);
    EXPECT_TRUE(solution2.tour.size() >= 1000);

    stopwatch.start("Greedy 1000 nodes 3");
    Graph i = Graph(TEST_INPUT_DIR "1000nodes3.txt");
    TSPSolution solution3 = greedy(i);
    time = stopwatch.stop();
    EXPECT_LE(time, 3);
    EXPECT_TRUE(solution3.tour.size() >= 1000);
};

TEST(GraphClassTests, TestingNN1000Nodes){
    Stopwatch stopwatch = Stopwatch(false);
    string filename = TEST_INPUT_DIR "1000nodes1.txt";
    stopwatch.start("NN 1000 nodes 1");
    Graph g = Graph(filename);
    TSPSolution solution = nearestNeighbor(g,0);
    double time = stopwatch.stop();
    EXPECT_LE(time, 3);
    EXPECT_TRUE(solution.tour.size() >= 1000);

    stopwatch.start("NN 1000 nodes 2");
    Graph h = Graph(TEST_INPUT_DIR "1000nodes2.txt");
    TSPSolution solution2 = nearestNeighbor(h,0);
    time = stopwatch.stop();
    EXPECT_LE(time, 3);
    EXPECT_TRUE(solution2.tour.size() >= 1000);

    stopwatch.start("NN 1000 nodes 3");
    Graph i = Graph(TEST_INPUT_DIR "1000nodes3.txt");
    TSPSolution solution3 = nearestNeighbor(i,0);
    time = stopwatch.stop();
    EXPECT_LE(time, 3);
    EXPECT_TRUE(solution3.tour.size() >= 1000);
};