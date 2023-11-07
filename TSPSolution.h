#ifndef TSPSOLUTION_H
#define TSPSOLUTION_H

struct TSPSolution {
    vector<int> tour;
    double cost;
    TSPSolution(vector<int> tour, double cost) : tour(tour), cost(cost) {};
    TSPSolution() : tour(vector<int>{}), cost(0) {};
    TSPSolution(vector<int> tour) : tour(tour), cost(0) {};
    TSPSolution(int size) : tour(vector<int>(size)), cost(0) {};
};

#endif