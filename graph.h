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
    void receiveInput();
public:
    //Constructors
    Graph(){ receiveInput(); };

    //Getters
    int getWeight(int x, int y);
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