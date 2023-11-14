#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <iostream>
#include <chrono>
#include <string>
#include <ctime>
#include <iomanip>
#include <limits>
using namespace std;

class Stopwatch
{
private:
    std::chrono::time_point<std::chrono::system_clock> startTime, endTime;
    string name;
    bool print;
public:
    Stopwatch(){print = true;};
    Stopwatch(bool print){this->print = print;}
    void start(string name);
    double stop();
};


#endif 