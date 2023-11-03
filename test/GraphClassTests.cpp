#include <gtest/gtest.h>
#include "../main.h"
#include "../Graph.h"
#include "../Christofides.h"
using namespace std;
#define TEST_INPUT_DIR "../../test/graphClassInputs/"


// ----------------------------- Graph.h / Graph.cpp TESTS ----------------------------- //
TEST(GraphClassTests, TestingGraphIsUndirected){
    string filename = TEST_INPUT_DIR "kattisSampleGraph.txt";
    Graph g = Graph(filename);
    for (int i = 0; i < g.getN(); i++) {
        for (int j = 0; j < g.getN(); j++) {
            ASSERT_EQ(g.getWeight(i, j), g.getWeight(j, i));
        }
    }
};

TEST(GraphClassTests, TestingRemovingNeighborInAdjList){
    string filename = TEST_INPUT_DIR "kattisSampleGraph.txt";
    Graph g = Graph(filename);
    g.addNeighbor(0 , 1);
    g.addNeighbor(0 , 2);
    g.removeNeighbor(0, 1);
    ASSERT_EQ(g.getNeighbors(0), vector<int>{2});
};

TEST(GraphClassTests, TestingRemovingNeighborWhenDuplicatesExistInAdjList){
    string filename = TEST_INPUT_DIR "kattisSampleGraph.txt";
    Graph g = Graph(filename);
    g.addNeighbor(0 , 1);
    g.addNeighbor(0 , 2);
    g.addNeighbor(0 , 2);
    g.addNeighbor(0 , 3);
    g.removeNeighbor(0, 2);
    //Should only remove one of the 2's
    vector<int> expected = vector<int>{1, 2, 3};
    ASSERT_EQ(g.getNeighbors(0), expected);
};

TEST(GraphClassTests, TestingAddingNeighbors){
    string filename = TEST_INPUT_DIR "kattisSampleGraph.txt";
    Graph g = Graph(filename);
    g.addNeighbor(0, 1);
    g.addNeighbor(0, 2);
    vector<int> expected = vector<int>{1, 2};
    ASSERT_EQ(g.getNeighbors(0), expected);
};
// ---------------------------------------------------------- //
