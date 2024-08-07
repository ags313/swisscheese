#pragma once

#include <chrono>

struct SingleMeasure {
    long counter = 0;
    std::chrono::time_point<std::chrono::system_clock> when = std::chrono::high_resolution_clock::now();
    long long whenNanos = std::chrono::time_point_cast<std::chrono::nanoseconds>(when).time_since_epoch().count();
    long long measures[8] = {0, 0, 0, 0, 0, 0, 0, 0};
};
