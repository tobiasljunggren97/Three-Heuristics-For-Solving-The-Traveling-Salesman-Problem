#include <gtest/gtest.h>
#include <gtest/gtest-param-test.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include "../main.h"
using namespace std;
#define INPUT_DIR "../../test/minWeightInputs/"

struct FilePair {
    string file_path;
    string solution_path;

    FilePair(string file_path, string solution_path) : file_path(file_path), solution_path(solution_path) {}
};

class MinWeightPerfectMatch : public ::testing::TestWithParam<FilePair> {
protected:
    string file_path;
    string solution_path;
    // Set up code (optional)
    void SetUp() override {
        FilePair filePair = GetParam();
        file_path = filePair.file_path;
        solution_path = filePair.solution_path;
        // Initialize common resources or state
    }

    // Tear down code (optional)
    // void TearDown() override {
    //     // Release any resources or clean up
    // }
};

INSTANTIATE_TEST_SUITE_P(MinWeightPerfectMatchTests, MinWeightPerfectMatch, ::testing::Values(
    FilePair(string(INPUT_DIR) + string("smallgraph.txt"), string(INPUT_DIR) + string("smallgraphSolution.txt")),
    FilePair(string(INPUT_DIR) + string("smallgraph.txt"), string(INPUT_DIR) + string("smallgraphIncorrect.txt"))
));

TEST_P(MinWeightPerfectMatch, minWeightPerfectMatchTest)
{
    string filename = file_path;

    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "ERROR: Filename not valid " << filename << endl;
        exit(1);
    }

    int N;
    file >> N;
    Graph g = Graph(N);

    while (true)
    {
        int node1, node2, weight;
        if (!(file >> node1 >> node2 >> weight)) {
            break;
        }
        g.addNeighbor(node1, node2);
        g.setWeight(node1, node2, weight);
    }

    file.close();

    string solution = solution_path;
    cout << "---------------------------------------------------------" << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "File: " << filename << endl;
    cout << "Solution: " << solution << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "---------------------------------------------------------" << endl;
    
    ifstream file2(solution);
    if (!file2.is_open())
    {
        cout << "ERROR: Filename not valid " << solution << endl;
        exit(1);
    }

    file2 >> N;
    Graph g2 = Graph(N);

    while (true)
    {
        int node1, node2, weight;
        if (!(file2 >> node1 >> node2 >> weight)) {
            break;
        }
        g2.addNeighbor(node1, node2);
        g2.setWeight(node1, node2, weight);
    }

    file2.close();
    vector<int> S;
    for (int i = 0; i < g.getN(); i++)
    {
        S.push_back(i);
    }

    const vector<vector<int>> adjacencyListBefore = g.getAdjacencyList();

    minimum_weight_matching(g, S);
    const vector<vector<int>> adjacencyListAfter = g.getAdjacencyList();

    vector<vector<int>> adjacencyListMinWeightPerfectMatch;
    const vector<vector<int>> solutionAdjacencyList = g2.getAdjacencyList();


    // Make adjacencyListMinWeightPerfectMatch be the list of edges that is in adjacencyListAfter but not in adjacencyListBefore
    for (int i = 0; i < adjacencyListAfter.size(); i++)
    {
        for (int j = adjacencyListBefore[i].size(); j < adjacencyListAfter[i].size(); j++)
        {
            adjacencyListMinWeightPerfectMatch.push_back({adjacencyListAfter[i][j]});
        }
    }

    ASSERT_EQ(adjacencyListMinWeightPerfectMatch, solutionAdjacencyList);

};
