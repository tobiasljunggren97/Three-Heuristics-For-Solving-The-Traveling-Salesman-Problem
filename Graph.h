#ifndef GRAPH_H
#define GRAPH_H 

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;
class Graph {
private: 
    int N;  
    vector<vector<double> > weight;
    vector<vector<int> > adjacencyList;
    void receiveInput(string filename = "");
public:
    //Constructors
    Graph(){ receiveInput(); };
    Graph(string filename){ receiveInput(filename); };

    //Getters
    int getWeight(int i, int j);
    int getN();
    vector<int> getNeighbors(int node);

    //Setters
    void setAdjancecyList(vector<vector<int> > adjList);
    void addNeighbor(int node, int neighbor);
    void removeNeighbor(int node, int neighbor); //ONLY REMOVES ONE NEIGHBOR NODE IF THERE ARE DUPLICATE EDGES

    //Helper functions
    void printAdjacencyList();
};


#endif
