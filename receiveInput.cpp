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
    vector<vector<double> > weights(numPoints, vector<double>(numPoints));

    for (int i = 0; i < numPoints; ++i) {
        cin >> points[i].x >> points[i].y;
    }

    for (int i = 0; i < numPoints; ++i) {
        for (int j = i + 1; j < numPoints; ++j) {
            double distance = calculateEuclidianDistance(points[i], points[j]);
            // cout << "Distance between points " << i << " and " << j << ": " << distance << endl;
            weights[i][j] = distance;
        }
    }
    //Kör alla heursiticis och shit

    return weights;

};

int main() {
    // Read input
    int N;
    cin >> N;

    vector<double> inner_vector(N);
    vector<vector<double> > weight(N,inner_vector);
    weight = receiveInput(N);
    //print weights

    return 0;
}
