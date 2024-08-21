#include "MeasurementApi.h"

#include <string>

#include "MeasurementSession.h"

void SwissMeter::MeasurementApi::setMeasurementDirectory(const std::string &path) {
    directory_ = path;
}

void SwissMeter::MeasurementApi::nameEvent(const std::string &name) {
    if (!uniqueColumns_.contains(name)) {
        columns_[uniqueColumns_.size()] = name;
        uniqueColumns_.insert(name);
    }
}

void SwissMeter::MeasurementApi::startMeasurementStream(const std::string &name) {
    currentRun_->end();
    counter_ = 0;
    auto copied = std::string(name);
    copied.erase(std::remove_if(copied.begin(),
                              copied.end(),
                              [](unsigned char c) {
                                  return !(std::isalnum(c) || c == '_' || c == '.' || c == '-');
                              }),
               copied.end());
    currentRun_ = new MeasurementSession{copied, columns_};
    q_.emplace(SwitchFiles(copied));
}

std::string SwissMeter::MeasurementApi::getNameAtIdx(const int i) {
    if (columns_.size() > i) {
        return columns_.at(i);
    } else {
        return std::string{"Undefined"};
    }
}

void SwissMeter::MeasurementApi::startObservation() {
    if(currentMeasure_ != nullptr) {
        q_.enqueue(*currentMeasure_);
        delete currentMeasure_;
    }
    currentMeasure_ = new SingleMeasure(counter_);
    counter_++;
}

void SwissMeter::MeasurementApi::endObservation() {
    q_.enqueue(*currentMeasure_);
    delete currentMeasure_;
    currentMeasure_ = nullptr;
}

void SwissMeter::MeasurementApi::start(const int column) {
    currentMeasure_->start(column);
}

void SwissMeter::MeasurementApi::finish(const int column) {
    currentMeasure_->finish(column);
}

void SwissMeter::MeasurementApi::observeSinceStart(const int column) {
    currentMeasure_->observeSinceStart(column);
}

void SwissMeter::MeasurementApi::observerRawValue(int column, long long value) {
    currentMeasure_->observeRaw(column, value);
}

void SwissMeter::MeasurementApi::shutdown() {
    shouldRun_ = false;
}
