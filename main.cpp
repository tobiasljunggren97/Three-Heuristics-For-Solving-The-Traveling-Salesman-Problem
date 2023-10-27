#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include "Christofides.cpp"
#include <tuple>
#include "graph.cpp"
#include "graph.h"

using namespace std;

int main() {
    //Initializing Graph will read input and create weight matrix
    Graph g = Graph();
    cout << "Calling Cristofides from main.cpp" << endl;
    cristofides(g);  
    return 0;
}


