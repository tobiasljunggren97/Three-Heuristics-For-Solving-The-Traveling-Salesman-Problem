#include <gtest/gtest.h>
#include "../main.h"
#include "../Graph.h"
#include "../Christofides.h"
#include "../Greedy.h"
#include "../Naive.h"
using namespace std;
#define TEST_INPUT_DIR "../../test/greedyTourInputs/"

int validRoute(vector<int> &solution, Graph &g) {
    int N = g.getN();
    if (solution.size() != N) {
        return 0;
    }
    vector<int> visited(N);
    for (int i = 0; i < N; i++) {
        if (visited[solution[i]]) {
            return 0;
        }
        visited[solution[i]] = 1;
    }
    return 1;
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

TSPSolution nearestRandom(Graph &g) {
    int size = 25 > g.getN() ? g.getN() : 25;
    TSPSolution solution;
    TSPSolution bestNNSolution;
    bestNNSolution.cost = numeric_limits<int>::max(); // obs obs vendela la till.  
    vector<int> randomVector;

    generateRandomVector(randomVector, size, 0, g.getN());
    for (int i = 0; i < size; i++) {
        solution = nearestNeighbor(g, randomVector[i]);
        if (solution.cost < bestNNSolution.cost) {
            bestNNSolution = solution;
        }
    }
    return bestNNSolution;
}

int calculateCost(vector<int> &solution, Graph &g) {
    int cost = 0;
    int N = g.getN();

    for (int i = 0; i < N-1; i++) {
        cost += g.getWeight(i, i+1);
    }
    cost += g.getWeight(0, solution[solution.size()-1]);
    return cost;
}

TEST(GraphClassTests, TestingGreedy50Nodes){

    // g
    Stopwatch stopwatch = Stopwatch(false);
    string filename = TEST_INPUT_DIR "50nodes1.txt";
    stopwatch.start("Greedy 50 nodes 1");
    Graph g = Graph(filename);
    TSPSolution solution = greedy(g);
    double time = stopwatch.stop();
    EXPECT_LE(time, 1);
    EXPECT_TRUE(solution.tour.size() >= 50);
    EXPECT_TRUE(validRoute(solution.tour, g));
    TSPSolution naiveSol = naive(g);
    int solutionCost = calculateCost(solution.tour, g);
    int naiveSolCost = calculateCost(naiveSol.tour, g);
    EXPECT_LE(solutionCost, naiveSolCost);
    
    // h
    stopwatch.start("Greedy 50 nodes 2");
    Graph h = Graph(TEST_INPUT_DIR "50nodes2.txt");
    TSPSolution solution2 = greedy(h);
    time = stopwatch.stop();
    EXPECT_LE(time, 1);
    EXPECT_TRUE(solution2.tour.size() >= 50);
    EXPECT_TRUE(validRoute(solution2.tour, h));
    TSPSolution naiveSol2 = naive(h);
    solutionCost = calculateCost(solution2.tour, h);
    naiveSolCost = calculateCost(naiveSol2.tour, h);
    EXPECT_LE(solutionCost, naiveSolCost);


    // i
    stopwatch.start("Greedy 50 nodes 3");
    Graph i = Graph(TEST_INPUT_DIR "50nodes3.txt");
    TSPSolution solution3 = greedy(i);
    time = stopwatch.stop();
    EXPECT_LE(time, 1);
    EXPECT_TRUE(solution3.tour.size() >= 50);
    EXPECT_TRUE(validRoute(solution3.tour, i));
    TSPSolution naiveSol3 = naive(i);
    solutionCost = calculateCost(solution3.tour, i);
    naiveSolCost = calculateCost(naiveSol3.tour, i);
    EXPECT_LE(solutionCost, naiveSolCost);
};

TEST(GraphClassTests, TestingNN50Nodes){
    Stopwatch stopwatch = Stopwatch(false);
    string filename = TEST_INPUT_DIR "50nodes1.txt";
    stopwatch.start("NN 50 nodes 1");
    Graph g = Graph(filename);
    TSPSolution solution = nearestRandom(g);
    double time = stopwatch.stop();
    EXPECT_LE(time, 1);
    EXPECT_TRUE(g.getN() == 50);
    cout << "WHAT IS SIZE OF SOLUTION? " << solution.tour.size() << endl;
    EXPECT_TRUE(solution.tour.size() >= 50);
    EXPECT_TRUE(validRoute(solution.tour, g));
    TSPSolution naiveSol = naive(g);
    int solutionCost = calculateCost(solution.tour, g);
    int naiveSolCost = calculateCost(naiveSol.tour, g);
    EXPECT_LE(solutionCost, naiveSolCost);

    stopwatch.start("NN 50 nodes 2");
    Graph h = Graph(TEST_INPUT_DIR "50nodes2.txt");
    TSPSolution solution2 = nearestRandom(h);
    time = stopwatch.stop();
    EXPECT_LE(time, 1);
    EXPECT_TRUE(solution2.tour.size() >= 50);
    EXPECT_TRUE(validRoute(solution2.tour, h));
    TSPSolution naiveSol2 = naive(h);
    solutionCost = calculateCost(solution2.tour, h);
    naiveSolCost = calculateCost(naiveSol2.tour, h);
    EXPECT_LE(solutionCost, naiveSolCost);

    stopwatch.start("NN 50 nodes 3");
    Graph i = Graph(TEST_INPUT_DIR "50nodes3.txt");
    TSPSolution solution3 = nearestRandom(i);
    time = stopwatch.stop();
    EXPECT_LE(time, 1);
    EXPECT_TRUE(solution3.tour.size() >= 50);
    EXPECT_TRUE(validRoute(solution3.tour, i));
    TSPSolution naiveSol3 = naive(i);
    solutionCost = calculateCost(solution3.tour, i);
    naiveSolCost = calculateCost(naiveSol3.tour, i);
    EXPECT_LE(solutionCost, naiveSolCost);
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
    EXPECT_TRUE(validRoute(solution.tour, g));
    TSPSolution naiveSol = naive(g);
    int solutionCost = calculateCost(solution.tour, g);
    int naiveSolCost = calculateCost(naiveSol.tour, g);
    EXPECT_LE(solutionCost, naiveSolCost);

    stopwatch.start("Greedy 1000 nodes 2");
    Graph h = Graph(TEST_INPUT_DIR "1000nodes2.txt");
    TSPSolution solution2 = greedy(h);
    time = stopwatch.stop();
    EXPECT_LE(time, 3);
    EXPECT_TRUE(solution2.tour.size() >= 1000);
    EXPECT_TRUE(validRoute(solution2.tour, h));
    TSPSolution naiveSol2 = naive(h);
    solutionCost = calculateCost(solution2.tour, h);
    naiveSolCost = calculateCost(naiveSol2.tour, h);
    EXPECT_LE(solutionCost, naiveSolCost);

    stopwatch.start("Greedy 1000 nodes 3");
    Graph i = Graph(TEST_INPUT_DIR "1000nodes3.txt");
    TSPSolution solution3 = greedy(i);
    time = stopwatch.stop();
    EXPECT_LE(time, 3);
    EXPECT_TRUE(solution3.tour.size() >= 1000);
    EXPECT_TRUE(validRoute(solution3.tour, i));
    TSPSolution naiveSol3 = naive(i);
    solutionCost = calculateCost(solution3.tour, i);
    naiveSolCost = calculateCost(naiveSol3.tour, i);
    EXPECT_LE(solutionCost, naiveSolCost);
};

TEST(GraphClassTests, TestingNN1000Nodes){
    Stopwatch stopwatch = Stopwatch(false);
    string filename = TEST_INPUT_DIR "1000nodes1.txt";
    stopwatch.start("NN 1000 nodes 1");
    Graph g = Graph(filename);
    TSPSolution solution = nearestRandom(g);
    double time = stopwatch.stop();
    EXPECT_LE(time, 3);
    EXPECT_TRUE(solution.tour.size() >= 1000);
    EXPECT_TRUE(validRoute(solution.tour, g));
    TSPSolution naiveSol = naive(g);
    int solutionCost = calculateCost(solution.tour, g);
    int naiveSolCost = calculateCost(naiveSol.tour, g);
    EXPECT_LE(solutionCost, naiveSolCost);

    stopwatch.start("NN 1000 nodes 2");
    Graph h = Graph(TEST_INPUT_DIR "1000nodes2.txt");
    TSPSolution solution2 = nearestRandom(h);
    time = stopwatch.stop();
    EXPECT_LE(time, 3);
    EXPECT_TRUE(solution2.tour.size() >= 1000);
    EXPECT_TRUE(validRoute(solution2.tour, h));
    TSPSolution naiveSol2 = naive(h);
    solutionCost = calculateCost(solution2.tour, h);
    naiveSolCost = calculateCost(naiveSol2.tour, h);
    EXPECT_LE(solutionCost, naiveSolCost);

    stopwatch.start("NN 1000 nodes 3");
    Graph i = Graph(TEST_INPUT_DIR "1000nodes3.txt");
    TSPSolution solution3 = nearestRandom(i);
    time = stopwatch.stop();
    EXPECT_LE(time, 3);
    EXPECT_TRUE(solution3.tour.size() >= 1000);
    EXPECT_TRUE(validRoute(solution3.tour, i));
    TSPSolution naiveSol3 = naive(i);
    solutionCost = calculateCost(solution3.tour, i);
    naiveSolCost = calculateCost(naiveSol3.tour, i);
    EXPECT_LE(solutionCost, naiveSolCost); // DETTA TEST FAILAR! 
};

