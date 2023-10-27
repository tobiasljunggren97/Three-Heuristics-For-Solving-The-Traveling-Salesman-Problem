#include <gtest/gtest.h>
#include "../main.h"
using namespace std;
#define INPUT_DIR "../../test/testInputs/"

TEST(ExampleTests, DemonstrateGTestMacros)
{
    string filename = "../../test/testInputs/firsttest.txt";
    // string filename = INPUT_DIR + "firsttest.txt";
    Graph g = Graph(filename);
    for(int i = 0; i < g.getN(); i++)
    {
        for(int j = 0; j < g.getN(); j++)
        {
            ASSERT_EQ(g.getWeight(i,j), g.getWeight(j,i));
            ASSERT_EQ(g.getWeight(i,j), 1);
        }
    }
}
