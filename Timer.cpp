#include "Timer.h"


void Timer::startTimer() {

    startingTime = std::chrono::high_resolution_clock::now();

}

void Timer::stopTimer() {

    finishTime = std::chrono::high_resolution_clock::now();
}

long long int Timer::calculateTime() {

    return std::chrono::duration_cast<std::chrono::nanoseconds>(Timer::finishTime - Timer::startingTime).count();
}