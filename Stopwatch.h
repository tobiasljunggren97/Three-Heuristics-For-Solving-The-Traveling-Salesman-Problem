#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <iostream>
#include <chrono>
#include <string>
#include <ctime>
#include <iomanip>
#include <limits>
#include <numbers>

using namespace std;

class Stopwatch
{
private:
    std::chrono::time_point<std::chrono::system_clock> startTime, endTime;
    string name;
public:
    Stopwatch(){};
    void start(string name);
    void stop();
};


#endif 