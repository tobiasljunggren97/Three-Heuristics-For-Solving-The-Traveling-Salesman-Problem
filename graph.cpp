#include "graph.h"

using namespace std;

//----------------------- GETTERS AND SETTERS --------------------//
int Graph::getWeight(int x, int y) { return weight[x][y]; }
int Graph::getN() { return N; }
vector<int> Graph::getNeighbors(int node)
{
    return adjacencyList[node];
}

void Graph::setAdjancecyList(vector<vector<int>> adjList) { adjacencyList = adjList; }
void Graph::addNeighbor(int node, int neighbor)
{
    adjacencyList[node].push_back(neighbor);
    adjacencyList[neighbor].push_back(node);
}

// ONLY REMOVES ONE NEIGHBOR NODE IF THERE ARE DUPLICATE EDGES
void Graph::removeNeighbor(int node, int neighbor)
{
    for (int i = 0; i < adjacencyList[node].size(); i++)
    {
        if (adjacencyList[node][i] == neighbor)
        {
            adjacencyList[node].erase(adjacencyList[node].begin() + i);
            return;
        }
    }
    for (int i = 0; i < adjacencyList[neighbor].size(); i++)
    {
        if (adjacencyList[neighbor][i] == node)
        {
            adjacencyList[neighbor].erase(adjacencyList[neighbor].begin() + i);
            return;
        }
    }
}

//----------------------- HELPER FUNCTIONS -----------------------//
double calculateEuclidianDistance(const tuple<double, double> &p1, const tuple<double, double> &p2)
{
    double dx = get<0>(p1) - get<0>(p2);
    double dy = get<1>(p1) - get<1>(p2);

    return round(sqrt(dx * dx + dy * dy)); // Round as per instructions
};

void Graph::receiveInput()
{
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
}