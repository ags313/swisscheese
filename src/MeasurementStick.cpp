#include "MeasurementStick.h"

#include <iostream>
#include <string>

#include "MeasurementRun.h"

DcsMeasurementStick::DcsMeasurementStick() {
    columns.emplace_back("frame");
    uniqueColumns.insert("frame");
}

void DcsMeasurementStick::setMeasurementDirectory(const std::string & path) {
    m_directory = path;
}

void DcsMeasurementStick::nameEvent(const std::string name) {
    if (!uniqueColumns.contains(name)) {
        columns.emplace_back(name);
        uniqueColumns.insert(name);
    }
}

void DcsMeasurementStick::startMeasurementStream(const std::string& name) {
    currentRun.end();
    currentRun = MeasurementRun{name, columns};
}

std::string DcsMeasurementStick::nameAtIdx(const int i) {
    if(columns.size() > i) {
        return columns.at(i);
    } else {
        return std::string{"Undefined"};
    }
}

void DcsMeasurementStick::startObservation() {
    current = SingleMeasure{};
    current.counter = counter;
    counter++;
}

void DcsMeasurementStick::endObservation() {
    for (auto column: columns) {
        std::cout << column << ";";
    }
    std::cout << std::endl;
    std::cout << current.counter << "\t" << current.whenNanos << "\t";
    for (int i = 0; i < 8; ++i) {
        std::cout << current.measures[i] << "\t";
    }
    std::cout << std::endl;
}

void DcsMeasurementStick::start(int i) {
    auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
    auto nanos = std::chrono::duration_cast<std::chrono::nanoseconds>(now).count();
    current.measures[i - 1] = nanos;
}

void DcsMeasurementStick::finish(int i) {
    auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
    auto endNanos = std::chrono::duration_cast<std::chrono::nanoseconds>(now).count();
    long long nanos = endNanos - current.measures[i - 1];
    current.measures[i - 1] = nanos;
}

void DcsMeasurementStick::observeSinceStart(int i) {
    auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
    auto endNanos = std::chrono::duration_cast<std::chrono::nanoseconds>(now).count();
    auto nanos = endNanos - current.whenNanos;
    current.measures[i - 1] = nanos;
}
