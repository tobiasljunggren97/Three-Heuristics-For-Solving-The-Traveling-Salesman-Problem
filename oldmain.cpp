#include "receiveInput.cpp"
using namespace std;

int main() {
    // Read input
    // int N = 

    // vector<double> inner(N);
    // vector<vector<double>> weight(N,inner);
    // weight = receiveInput();


    // Call heuristics from other files
    int numPoints;
    cin >> numPoints;
    vector<vector<double> > weights(numPoints, vector<double>(numPoints));
    weights = receiveInput(numPoints);
    
    return 0;
}