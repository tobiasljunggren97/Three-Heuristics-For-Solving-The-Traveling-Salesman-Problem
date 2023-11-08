#include "Stopwatch.h"


void Stopwatch::start(string name)
{
    this->name = name;
    startTime = std::chrono::system_clock::now();
}

void Stopwatch::stop()
{
    endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = endTime - startTime;
    //Print in milliseconds and cut off after 5 decimals 
    cout << name << " took " << std::setprecision(5) << elapsed_seconds.count() * 1000 << " milliseconds" << endl;

}