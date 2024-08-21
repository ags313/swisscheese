#include "SingleMeasure.h"

#include <iostream>

namespace SwissMeter {
    SingleMeasure::SingleMeasure(): counter_(0),
                                    measures_(std::array<long long, 8>()),
                                    whenSystem_(std::chrono::system_clock::now()),
                                    whenHighRes_(std::chrono::high_resolution_clock::now()) {

    }

    SingleMeasure::SingleMeasure(const long p_counter): counter_(p_counter),
                                                        measures_(std::array<long long, 8>()),
                                                        whenSystem_(std::chrono::system_clock::now()),
                                                        whenHighRes_(std::chrono::high_resolution_clock::now()) {

    };

    void SingleMeasure::observeSinceStart(int column) {
        const auto now = std::chrono::high_resolution_clock::now();
        const auto difference = now - whenHighRes_;
        const auto micros = std::chrono::duration_cast<std::chrono::microseconds>(difference).count();
        measures_.at(column - 1) = micros;
    }

    void SingleMeasure::observeRaw(int column, long long value) {
        measures_.at(column - 1) = value;
    }

    void SingleMeasure::start(int column) {
        const auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
        const auto micros = std::chrono::duration_cast<std::chrono::microseconds>(now).count();
        measures_.at(column - 1) = micros;
    }

    void SingleMeasure::finish(int column) {
        const auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
        const auto endMicros = std::chrono::duration_cast<std::chrono::microseconds>(now).count();
        const long long micros = endMicros - measures_.at(column - 1);
        measures_.at(column - 1) = micros;
    }

    long long SingleMeasure::getEpochSeconds() const {
        return std::chrono::duration_cast<std::chrono::seconds>(whenSystem_.time_since_epoch()).count();
    }

    std::array<long long, 8> SingleMeasure::getMeasures() const {
        return measures_;
    }
}
