#include <gtest/gtest.h>
#include "../main.h"
#include "../Graph.h"
#include "../Christofides.h"
#include <fstream>
using namespace std;
#define TEST_INPUT_DIR "../../test/primsInputs/"

TEST(PrimsTest, TestSingleNodeGraph){
    Graph g(TEST_INPUT_DIR "SingleNodeGraph.txt");
    prims(g);
    EXPECT_EQ(g.getAdjacencyList().size(), 1);
    EXPECT_EQ(g.getNeighbors(0).size(), 0);
};

TEST(PrimsTest, TestFindOnePossibleMST){
    string filename = TEST_INPUT_DIR "mstGraph.txt";
    Graph g(7);
    //open file
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "ERROR: Filename not valid" << endl;
        exit(1);
    }
    int node1, node2, weight;
    vector<vector<int> > expected(7);
    while (file >> node1 >> node2 >> weight) {
        g.setWeight(node1, node2, weight);
        g.setWeight(node2, node1, weight);
        if (weight == 1) {
            expected[node1].push_back(node2);
            expected[node2].push_back(node1);
        }
    }
    file.close();
    prims(g);
    for(int i = 0; i < 6; i++){
        if(g.getNeighbors(i).size() != expected[i].size()){
            for (int i = 0; i < g.getNeighbors(i).size(); i++) {
                cout << g.getNeighbors(i)[i] << endl;
            }
            cout << "and" << endl;
            for (int i = 0; i < expected[i].size(); i++) {
                cout << expected[i][i] << endl;
            }
            FAIL();
        }
        //sort vectors
        vector<int> actual = g.getNeighbors(i);
        sort(actual.begin(), actual.end());
        sort(expected[i].begin(), expected[i].end());
        for(int j = 0; j < actual.size(); j++){
            if(actual[j] != expected[i][j]){
                FAIL();
            }
        }
    }
};

TEST(PrimsTest, TestGraphWithOneLoop){
    string filename = TEST_INPUT_DIR "graphOneLoop.txt";
    Graph g(7);
    //open file
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "ERROR: Filename not valid" << endl;
        exit(1);
    }
    int node1, node2, weight;
    vector<vector<int> > expected(7);
    while (file >> node1 >> node2 >> weight) {
        g.setWeight(node1, node2, weight);
        g.setWeight(node2, node1, weight);
    }
    file.close();
    prims(g);  
    vector<tuple<int, int>> edges;
    for(int i = 0; i < 6; i++){
        vector<int> neighbors = g.getNeighbors(i);
        for(int j = 0; j < neighbors.size(); j++){
            tuple<int, int> edge;
            if(i < neighbors[j]){
                edge = make_tuple(i, neighbors[j]);
            } else {
                edge = make_tuple(neighbors[j], i);
            }
            if(find(edges.begin(), edges.end(), edge) != edges.end()){
                //edge already exists
            } else {
                edges.push_back(edge);
            }
        }
    }
    //There should be one less edge than input, since one edge is a loop
    EXPECT_EQ(edges.size(), 6);

}
