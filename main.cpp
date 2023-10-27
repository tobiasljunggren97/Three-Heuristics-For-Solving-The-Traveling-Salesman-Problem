#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include "Christofides.h"
#include <tuple>

using namespace std;

int main() {
    //Initializing Graph will read input and create weight matrix
    Graph g = Graph();
    cout << "Calling Cristofides from main.cpp" << endl;
    christofides(g);  
    return 0;
}


