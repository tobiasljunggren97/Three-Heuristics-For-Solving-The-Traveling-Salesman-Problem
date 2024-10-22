#include "Graph.h"
#include <algorithm>

using namespace std;

//----------------------- GETTERS AND SETTERS --------------------//
int Graph::getWeight(int i, int j) { 
    return weight[i][j]; 
    
    }
void Graph::setWeight(int i, int j, int w) { weight[i][j] = w;}


int Graph::getN() { return N; }
vector<int> Graph::getNeighbors(int node)
{
    return adjacencyList[node];
}

const vector<vector<int> >& Graph::getAdjacencyList() { return adjacencyList; }
const vector<vector<double> >& Graph::getWeights() {return weight; }

void Graph::setAdjancecyList(vector<vector<int>> adjList) { adjacencyList = adjList; }
void Graph::addNeighbor(int node, int neighbor)
{
    adjacencyList[node].push_back(neighbor);
    adjacencyList[neighbor].push_back(node);
}

void Graph::addNeighborOneWay(int node, int neighbor) { // for testing. 
    adjacencyList[node].push_back(neighbor);
}

void Graph::removeNeighbor(int node, int neighbor)
{

    auto it_node = std::find(adjacencyList[node].begin(), adjacencyList[node].end(), neighbor);
    if (it_node != adjacencyList[node].end()) {
        adjacencyList[node].erase(it_node); 
    }

    auto it_neighbor = std::find(adjacencyList[neighbor].begin(), adjacencyList[neighbor].end(), node);
    if (it_neighbor != adjacencyList[neighbor].end()) {
        adjacencyList[neighbor].erase(it_neighbor); 
    }
    
}

//----------------------- HELPER FUNCTIONS -----------------------//
double calculateEuclidianDistance(const tuple<double, double> &p1, const tuple<double, double> &p2)
{
    double dx = get<0>(p1) - get<0>(p2);
    double dy = get<1>(p1) - get<1>(p2);

    return round(sqrt(dx * dx + dy * dy)); // Round as per instructions
};

void Graph::receiveInput(string filename)
{
    if (filename != "")
    {
        if (!freopen(filename.c_str(), "r", stdin))
        {
            cout << "ERROR: Filename not valid (Kom ihåg att redirecta från rätt mapp, så typ '../sampleInput1.txt')" << endl;
            exit(1);
        }
    }

    cin >> N;
    adjacencyList = vector<vector<int>>(N);
    vector<tuple<double, double>> points(N);
    weight = vector<vector<double>>(N, vector<double>(N));
    
    double x, y;
    for (int i = 0; i < N; ++i)
    {
        cin >> x >> y;
        points[i] = make_tuple(x, y);
        for (int j = 0; j < i; j++) {
            if(i == j) {
                weight[i][j] = 0;
                weight[j][i] = 0;
                continue; 
            }
            
            
            double distance = calculateEuclidianDistance(points[i], points[j]);

            weight[i][j] = distance;
            weight[j][i] = distance;
            
        }
    }
};

void Graph::printAdjacencyList()
{
    for (int i = 0; i < N; ++i)
    {
        cout << i << ": ";
        for (int j = 0; j < adjacencyList[i].size(); ++j)
        {
            cout << adjacencyList[i][j] << " ";
        }
        cout << endl;
    }
};

void Graph::printWeightMatrix()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << i << " -- " << weight[i][j] << " -- " << j << endl;
        }
    }
};


