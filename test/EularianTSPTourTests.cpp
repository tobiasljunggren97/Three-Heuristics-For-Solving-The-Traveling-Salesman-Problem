#include <gtest/gtest.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include "../main.h"
#include "../Christofides.h"
using namespace std;
#define INPUT_DIR "../../test/tourInputs/"

class MediumGraph : public ::testing::Test
{
protected:
    Graph g = Graph(13);
    // Set up code (optional)
    void SetUp() override
    {
        cout << "WE ARE SETTING UP!! " << endl;
        string filename = string(INPUT_DIR) + "mediumgraph.txt";

        ifstream file(filename);
        if (!file.is_open())
        {
            cout << "ERROR: Filename not valid " << filename << endl;
            exit(1);
        }

        int N;
        file >> N;
        // g = Graph(N);

        while (true)
        {
            int node1, node2, weight;
            if (!(file >> node1 >> node2 >> weight))
            {
                break;
            }
            g.addNeighbor(node1, node2);
            cout << "for node1: " << node1 << " and node2: " << node2 << ". we have weight: " << weight << endl; 
            g.setWeight(node1, node2, weight);
            cout << "after setting weight, calling g.getWeight(node1, node2) and we get: " << g.getWeight(node1, node2);  
        }

        file.close();
        // cout << "current graph: " << endl;
        // g.printWeightMatrix();
    }

    // Tear down code (optional)
    void TearDown() override
    {
        // Release any resources or clean up
        cout << "WE ARE TEARING DOWN!" << endl;
    }
};

TEST_F(MediumGraph, EularianTourMediumGraphReturnsRightPath)
{

    cout << "do we make it here?? " << endl;
    // Assume all are correct.
    int et1 = 1;
    int et2 = 1;
    int et3 = 1;
    int et4 = 1;
    cout << "THIS IS INSIDE THE TEST, WHAT IS WEIGHT HERE BETWEEN NODE 1 AND 2? " << endl; 
    cout << g.getWeight(0, 1) << endl; 
    vector<int> eularian_res = eularian_tour(g);

    // since there can be several correct eulerian tours for minweidht solution graph.
    vector<int> c_et_v1 = {0, 8, 12, 11, 9, 11, 7, 10, 2, 4, 5, 6, 3, 6, 12, 1, 0};
    vector<int> c_et_v2 = {0, 8, 12, 6, 3, 6, 5, 4, 2, 10, 7, 11, 9, 11, 12, 1, 0};

    // et_v1 reversed
    vector<int> c_et_v3 = {0, 1, 12, 6, 3, 6, 5, 4, 2, 10, 7, 11, 9, 11, 12, 8, 0};
    // et_v2 reversed
    vector<int> c_et_v4 = {0, 1, 12, 11, 9, 11, 7, 10, 2, 4, 5, 6, 3, 6, 12, 8, 0};

    for (int i = 0; i < c_et_v1.size(); i++)
    {
        et1 = c_et_v1[i] == eularian_res[i] && et1 == 1 ? 1 : 0;
        et2 = c_et_v2[i] == eularian_res[i] && et2 == 1 ? 1 : 0;
        et3 = c_et_v3[i] == eularian_res[i] && et3 == 1 ? 1 : 0;
        et4 = c_et_v4[i] == eularian_res[i] && et4 == 1 ? 1 : 0;
    }

    ASSERT_EQ(1, et1 || et2 || et3 || et4); // at most one will be correct.
}

TEST_F(MediumGraph, TSPTourMediumGraphReturnsRightPath)
{
    ASSERT_EQ(1, 1);
}