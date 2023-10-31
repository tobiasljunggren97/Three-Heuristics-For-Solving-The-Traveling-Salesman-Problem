#include <gtest/gtest.h>
#include "../main.h"
#include "../Graph.h"
#include "../Christofides.h"
using namespace std;
#define TEST_INPUT_DIR "../../test/testInputs/"

TEST(PrimsTest, TestSingleNodeGraph){
    Graph g(TEST_INPUT_DIR "SingleNodeGraph.txt");
    prims(g);
    EXPECT_EQ(g.getNeighbors(0).size(), 0);
}
