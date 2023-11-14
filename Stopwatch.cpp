#include "Stopwatch.h"
#define DEBUG 1

void Stopwatch::start(string name)
{
    if(DEBUG){
    this->name = name;
    startTime = std::chrono::system_clock::now();
    }
}

double Stopwatch::stop()
{
    if(DEBUG){
    endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = endTime - startTime;
    if(print){
        //Print in milliseconds and cut off after 5 decimals 
        cout << name << " took " << std::setprecision(5) << elapsed_seconds.count() * 1000 << " milliseconds" << endl;
    }
    return elapsed_seconds.count();
    } else {
        return 0;
    }
}