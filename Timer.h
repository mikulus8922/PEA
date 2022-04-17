#pragma once
#include <chrono>


class Timer {

public:

    std::chrono::high_resolution_clock::time_point startingTime;
    std::chrono::high_resolution_clock::time_point finishTime;

    Timer()
    {

    }

    void startTimer();
    void stopTimer();
    long long int calculateTime();

};

