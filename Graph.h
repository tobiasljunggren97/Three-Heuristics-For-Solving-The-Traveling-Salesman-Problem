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
    Graph(int N) : N(N) { weight = vector<vector<double> >(N, vector<double>(N)); adjacencyList = vector<vector<int>>(N);}; // For testing
    Graph(string filename){ receiveInput(filename); };

    //Getters
    int getWeight(int i, int j);
    void setWeight(int i, int j, int w); // For testing
    int getN();
    vector<int> getNeighbors(int node);
    const vector<vector<int> >& getAdjacencyList(); // For testing
    const vector<vector<double> >& getWeights();
    void addNeighborOneWay(int node, int neighbor); // For testing 

    //Setters
    void setAdjancecyList(vector<vector<int> > adjList);
    void addNeighbor(int node, int neighbor);
    void removeNeighbor(int node, int neighbor); //ONLY REMOVES ONE NEIGHBOR NODE IF THERE ARE DUPLICATE EDGES

    //Helper functions
    void printAdjacencyList();

    void printWeightMatrix();
};


#endif
