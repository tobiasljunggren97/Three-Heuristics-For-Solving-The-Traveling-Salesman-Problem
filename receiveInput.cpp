#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

struct Point {
    double x, y;
};

double calculateDistance(const Point& p1, const Point& p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return round(sqrt(dx * dx + dy * dy));
}

int main() {
    int numPoints;
    cin >> numPoints;

    vector<Point> points(numPoints);

    for (int i = 0; i < numPoints; ++i) {
        cin >> points[i].x >> points[i].y;
    }

    // Calculate and print the distances between all pairs of points
    for (int i = 0; i < numPoints; ++i) {
        for (int j = i + 1; j < numPoints; ++j) {
            double distance = calculateDistance(points[i], points[j]);
            cout << "Distance between points " << i << " and " << j << ": " << fixed << setprecision(0) << distance << endl;
        }
    }

    return 0;
}
