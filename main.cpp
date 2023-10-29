#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <tuple>
#include "main.h"

using namespace std;

int main() {
    //Initializing Graph will read input and create weight matrix
    Graph g = Graph();
    christofides(g);  
    return 0;
}


