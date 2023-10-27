#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include "cristofides.cpp"
#include <tuple>

using namespace std;

double calculateEuclidianDistance(const tuple<double, double>& p1, const tuple<double, double>& p2) {
    double dx = get<0>(p1) - get<0>(p2);
    double dy = get<1>(p1) - get<1>(p2); 
    
    return round(sqrt(dx * dx + dy * dy)); //Round as per instructions
};

vector<vector<double> > receiveInput(int numPoints) {
    vector<tuple<double, double> > ponts(numPoints);
    //Initiera 2d array
    vector<vector<double> > weight(numPoints, vector<double>(numPoints));
    double point1, point2;
    for (int i = 0; i < numPoints; ++i) {
        cin >> point1 >> point2;
        ponts[i] = make_tuple(point1, point2);
        // cin >> points[i].x >> points[i].y;
    }

    for (int i = 0; i < numPoints; ++i) {
        for (int j = i + 1; j < numPoints; ++j) {
            double distance = calculateEuclidianDistance(ponts[i], ponts[j]);
            // cout << "Distance between points " << i << " and " << j << ": " << distance << endl;
            weight[i][j] = distance;
            weight[j][i] = distance;
        }
    }
    return weight;

};



int main() {
    // Read input
    int N;
    cin >> N;
    
    vector<double> inner_vector(N);
    vector<vector<double> > weight(N,inner_vector);
    weight = receiveInput(N);
    cout << "Calling Cristofides from main.cpp" << endl;
    cristofides(weight, N);
    
    // for(int i = 0; i < N; i++){
    //     for(int j = 0; j < N; j++){
    //         cout << "Distance between points " << i << " and " << j << ": " << weight[i][j] << endl;
    //     }
    //     cout << endl;
    // }
  
    return 0;
}


