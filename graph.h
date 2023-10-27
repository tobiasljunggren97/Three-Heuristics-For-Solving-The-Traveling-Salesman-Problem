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
    Graph(){
        receiveInput();
    };

    int getWeight(int x, int y) {
        return weight[x][y];
    }
    void setAdjancecyList(vector<vector<int> > adjList){
        adjacencyList = adjList;
    }
    int getN(){
        return N;
    }
    void printAdjacencyList();
    void addNeighbor(int node, int neighbor){
        adjacencyList[node].push_back(neighbor);
    }
    //ONLY REMOVES ONE NEIGHBOR IF THERE ARE DUPLICATES
    void removeNeighbor(int node, int neighbor){
        for(int i = 0; i < adjacencyList[node].size(); i++){
            if(adjacencyList[node][i] == neighbor){
                adjacencyList[node].erase(adjacencyList[node].begin() + i);
                return;
            }
        }
    }
    vector<int> getNeighbors(int node){
        return adjacencyList[node];
    }
    // int getNumEdges();
};


#endif