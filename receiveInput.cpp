#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

struct Point {
    double x, y;
};

double calculateEuclidianDistance(const Point& p1, const Point& p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y; //CHANGE TO INTS HERE DO NOT FORGET
    //Vill vi har roundat?
    return round(sqrt(dx * dx + dy * dy));
};


vector<vector<double> > receiveInput(int numPoints) {
    vector<Point> points(numPoints);
    //Initiera 2d array
    vector<vector<double> > weight(numPoints, vector<double>(numPoints));

    for (int i = 0; i < numPoints; ++i) {
        cin >> points[i].x >> points[i].y;
    }

    for (int i = 0; i < numPoints; ++i) {
        for (int j = i + 1; j < numPoints; ++j) {
            double distance = calculateEuclidianDistance(points[i], points[j]);
            // cout << "Distance between points " << i << " and " << j << ": " << distance << endl;
            weight[i][j] = distance;
            weight[j][i] = distance;
        }
    }
    //Kör alla heursiticis och shit

    return weight;

};

vector<vector<int>> prims(vector<vector<double> > weight, int numPoints){
  int numEdges = 0;  
  vector<int> handled(numPoints);
  handled[0] = true;
  vector<vector<int> > adjacencyList(numPoints);

  int node1;  
  int node2;  

  while (numEdges < numPoints - 1) {

    int min = numeric_limits<int>::max();
    node1 = 0;
    node2 = 0;

    for (int i = 0; i < numPoints; i++) {
      if (handled[i]) {
        // cout << "selected[i]: " << i << endl;
        for (int j = 0; j < numPoints; j++) {
          if (!handled[j] && weight[i][j]) {  // not in selected and there is an edge
            // cout << "selected[j] not selected found: " << j << endl;
            if (min > weight[i][j] && i != j) {
            //  cout << "new min: " << weight[i][j] << " between " << i << " and " << j << endl;
              min = weight[i][j];
              node1 = i;
              node2 = j;
            }
          }
        }
      }
    }
    
    adjacencyList[node1].push_back(node2);
    adjacencyList[node2].push_back(node1);
    //cout << node1 << " - " << node2 << " :  " << weight[node1][node2];
    cout << endl;
    handled[node2] = true;
    numEdges++;
  }

  return adjacencyList;    
}


int main() {
    // Read input
    int N;
    cin >> N;
    
    vector<double> inner_vector(N);
    vector<vector<double> > weight(N,inner_vector);
    weight = receiveInput(N);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << "Distance between points " << i << " and " << j << ": " << weight[i][j] << endl;
        }
        cout << endl;
    }
    
    vector<vector<int> > adjacencyList(N);
    adjacencyList = prims(weight, N);

    // Print adjacency list
    // for (int i = 0; i < N; ++i) {
    //     cout << i << ": ";
    //     for (int j = 0; j < adjacencyList[i].size(); ++j) {
    //         cout << adjacencyList[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    return 0;
}


