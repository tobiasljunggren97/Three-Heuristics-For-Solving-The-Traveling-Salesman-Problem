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

int prims(vector<vector<double> > weight, int numPoints){
  int no_edge;  // number of edge

  // create a array to track selected vertex
  // selected will become true otherwise false
  vector<int> selected(numPoints);

  // set number of edge to 0
  no_edge = 0;

  // the number of egde in minimum spanning tree will be
  // always less than (V -1), where V is number of vertices in
  //graph

  // choose 0th vertex and make it true
  selected[0] = true;

  int x;  //  row number
  int y;  //  col number

  // print for edge and weight
  cout << "Edge"
     << " : "
     << "Weight";
  cout << endl;
  while (no_edge < numPoints - 1) {
    //For every vertex in the set S, find the all adjacent vertices
    // , calculate the distance from the vertex selected at step 1.
    // if the vertex is already in the set S, discard it otherwise
    //choose another vertex nearest to selected vertex  at step 1.

    int min = 999999;
    x = 0;
    y = 0;

    for (int i = 0; i < numPoints; i++) {
      if (selected[i]) {
        // cout << "selected[i]: " << i << endl;
        for (int j = 0; j < numPoints; j++) {
          if (!selected[j] && weight[i][j] && i != j) {  // not in selected and there is an edge
            // cout << "selected[j] not selected found: " << j << endl;
            if (min > weight[i][j] && i != j) {
            //  cout << "new min: " << weight[i][j] << " between " << i << " and " << j << endl;
              min = weight[i][j];
              x = i;
              y = j;
            }
          }
        }
      }
    }
    cout << x << " - " << y << " :  " << weight[x][y];
    cout << endl;
    selected[y] = true;
    no_edge++;
  }

  return 0;    
}


int main() {
    // Read input
    int N;
    cin >> N;
    cout << "heklk" << endl;
    vector<double> inner_vector(N);
    vector<vector<double> > weight(N,inner_vector);
    weight = receiveInput(N);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << "Distance between points " << i << " and " << j << ": " << weight[i][j] << endl;
        }
        cout << endl;
    }
    
    cout << "N is " << N << endl;
    prims(weight, N);

    return 0;
}


