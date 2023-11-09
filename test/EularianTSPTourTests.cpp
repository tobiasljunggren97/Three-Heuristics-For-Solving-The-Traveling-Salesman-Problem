#include <gtest/gtest.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include "../main.h"
#include "../TSPSolution.h"
#include "../Christofides.h"
using namespace std;
#define INPUT_DIR "../../test/tourInputs/"

class MediumGraph : public ::testing::Test
{
protected:
    Graph *g;
    // Set up code (optional)
    void SetUp() override
    {
        cout << "Setup.." << endl;
        string filename = string(INPUT_DIR) + "mediumgraph.txt";

        ifstream file(filename);
        if (!file.is_open())
        {
            cout << "ERROR: Filename not valid " << filename << endl;
            exit(1);
        }

        int N;
        file >> N;
        g = new Graph(N);

        while (true)
        {
            int node1, node2, weight;
            if (!(file >> node1 >> node2 >> weight))
            {
                break;
            }
            // g->addNeighborOneWay(node1, node2);
            g->addNeighbor(node1, node2);
            g->setWeight(node1, node2, weight);
        }

        file.close();

    }

    // Tear down code (optional)
    void TearDown() override
    {
        // Release any resources or clean up
        cout << "Teardown..." << endl;
        delete g;
    }
};

TEST_F(MediumGraph, EularianTourMediumGraphReturnsRightPath)
{
    // Assume all are correct.
    int et1 = 1;
    int et2 = 1;
    int et3 = 1;
    int et4 = 1;

    vector<int> eularian_res = eulerian_tour(*g);

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

    EXPECT_EQ(1, et1 || et2 || et3 || et4); // at most one will be correct.
}

TEST_F(MediumGraph, TSPTourMediumGraphReturnsRightPath)
{
    // Assume all are correct.
    int et1 = 1;
    int et2 = 1;
    int et3 = 1;
    int et4 = 1;

    vector<int> eularian_res = eulerian_tour(*g);
    TSPSolution tspTour = tsp_tour(eularian_res, *g);

    vector<int> c_et_v1 = {0, 8, 12, 11, 9, 7, 10, 2, 4, 5, 6, 3, 1};
    vector<int> c_et_v2 = {0, 8, 12, 6, 3, 5, 4, 2, 10, 7, 11, 9, 1};

    // et_v1 reversed
    vector<int> c_et_v3 = {0, 1, 12, 6, 3, 5, 4, 2, 10, 7, 11, 9, 8};
    // et_v2 reversed
    vector<int> c_et_v4 = {0, 1, 12, 11, 9, 7, 10, 2, 4, 5, 6, 3, 8};

    for (int i = 0; i < c_et_v1.size(); i++)
    {
        et1 = c_et_v1[i] == tspTour.tour[i] && et1 == 1 ? 1 : 0;
        et2 = c_et_v2[i] == tspTour.tour[i] && et2 == 1 ? 1 : 0;
        et3 = c_et_v3[i] == tspTour.tour[i] && et3 == 1 ? 1 : 0;
        et4 = c_et_v4[i] == tspTour.tour[i] && et4 == 1 ? 1 : 0;
    }

    EXPECT_EQ(1, et1 || et2 || et3 || et4); // at most one will be correct.
}