#include "Graph.h"
#include <algorithm>

using namespace std;

//----------------------- GETTERS AND SETTERS --------------------//
int Graph::getWeight(int i, int j) { return weight[i][j]; }
void Graph::setWeight(int i, int j, int w) { weight[i][j] = w; }

int Graph::getN() { return N; }
vector<int> Graph::getNeighbors(int node)
{
    return adjacencyList[node];
}

const vector<vector<int> >& Graph::getAdjacencyList() { return adjacencyList; }

void Graph::setAdjancecyList(vector<vector<int>> adjList) { adjacencyList = adjList; }
void Graph::addNeighbor(int node, int neighbor)
{
    adjacencyList[node].push_back(neighbor);
    adjacencyList[neighbor].push_back(node);
}

// ONLY REMOVES ONE NEIGHBOR NODE IF THERE ARE DUPLICATE EDGES
void Graph::removeNeighbor(int node, int neighbor)
{

    auto it_node = std::find(adjacencyList[node].begin(), adjacencyList[node].end(), neighbor);
    if (it_node != adjacencyList[node].end()) {
        adjacencyList[node].erase(it_node); // Removes the element
    }

    auto it_neighbor = std::find(adjacencyList[neighbor].begin(), adjacencyList[neighbor].end(), node);
    if (it_neighbor != adjacencyList[neighbor].end()) {
        adjacencyList[neighbor].erase(it_neighbor); // Removes the element
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
        // Redirect input from file to stdin
        if (!freopen(filename.c_str(), "r", stdin))
        {
            cout << "ERROR: Filename not valid (Kom ihåg att redirecta från rätt mapp, så typ '../sampleInput1.txt')" << endl;
            exit(1);
        }
    }

    cin >> N;
    // Initiate adjancency list
    adjacencyList = vector<vector<int>>(N);
    vector<tuple<double, double>> ponts(N);
    // Initiera 2d array
    weight = vector<vector<double>>(N, vector<double>(N));
    double point1, point2;
    for (int i = 0; i < N; ++i)
    {
        cin >> point1 >> point2;
        ponts[i] = make_tuple(point1, point2);
    }
    for (int i = 0; i < N; ++i)
    {
        for (int j = i + 1; j < N; ++j)
        {
            double distance = calculateEuclidianDistance(ponts[i], ponts[j]);
            weight[i][j] = distance;
            weight[j][i] = distance;
        }
    }
};

// Print adjacency list function
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

// Print weight matrix
void Graph::printWeightMatrix()
{
    for (int i = 1; i < N; i++)
    {
        for (int j = 0; j <= i - 1; j++)
        {
            cout << i << " -- " << weight[i][j] << " -- " << j << endl;
        }
    }
};
