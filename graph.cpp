#include "graph.h"

double calculateEuclidianDistance(const tuple<double, double>& p1, const tuple<double, double>& p2) {
    double dx = get<0>(p1) - get<0>(p2);
    double dy = get<1>(p1) - get<1>(p2); 
    
    return round(sqrt(dx * dx + dy * dy)); //Round as per instructions
};

void Graph::receiveInput() {
    
    cin >> N;
    //Initiate adjancency list
    adjacencyList = vector<vector<int> >(N);
    vector<tuple<double, double> > ponts(N);
    //Initiera 2d array
    weight = vector<vector<double>>(N, vector<double>(N));
    double point1, point2;
    for (int i = 0; i < N; ++i) {
        cin >> point1 >> point2;
        ponts[i] = make_tuple(point1, point2);
        // cin >> points[i].x >> points[i].y;
    }

    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            double distance = calculateEuclidianDistance(ponts[i], ponts[j]);
            // cout << "Distance between points " << i << " and " << j << ": " << distance << endl;
            weight[i][j] = distance;
            weight[j][i] = distance;
        }
    }
};


//HELPER FUNCTION
// Print adjacency list function
void Graph::printAdjacencyList() {
    for (int i = 0; i < N; ++i) {
        cout << i << ": ";
        for (int j = 0; j < adjacencyList[i].size(); ++j) {
            cout << adjacencyList[i][j] << " ";
        }
        cout << endl;
    }
}