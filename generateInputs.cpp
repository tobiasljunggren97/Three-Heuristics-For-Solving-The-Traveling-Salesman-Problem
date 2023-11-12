#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <tuple>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <filename> <numPoints>" << endl;
        return 1;
    }

    // Initialize random seed based on current time
    srand(static_cast<unsigned>(time(nullptr)));

    // Take the filename and number of points from command-line arguments
    string filename = argv[1];
    int numPoints = atoi(argv[2]);

    // Write to file
    ofstream myfile;
    myfile.open(filename);

    // Write the number of points on the first line
    myfile << numPoints << endl;

    vector<tuple<double, double>> points;
    int counter = 0;  // Initialize counter

    while (counter < numPoints) {
        // Generate random x and y double coordinates between 0 and 10000
        double x = (double)rand() / RAND_MAX * 10000.0;
        double y = (double)rand() / RAND_MAX * 10000.0;

        // Write to file if they are not the same and they don't already exist
        if (x != y && find(points.begin(), points.end(), make_tuple(x, y)) == points.end()) {
            myfile << x << " " << y << endl;
            points.push_back(make_tuple(x, y));
            counter++;
        }
    }

    // Close the file
    myfile.close();

    return 0;
}
