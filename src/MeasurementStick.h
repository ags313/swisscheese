#pragma once
#include <set>
#include <string>
#include <vector>

#include "MeasurementRun.h"
#include "SingleMeasure.h"

class DcsMeasurementStick {
public:
    DcsMeasurementStick();

    void setMeasurementDirectory(const std::string & path);

    void nameEvent(std::string name);

    void startMeasurementStream(const std::string & name);

    void endMeasurementStream();

    void record(int idx);

    std::string nameAtIdx(int i);

    void startObservation();

    void endObservation();

    void start(int i);

    void finish(int i);

    void observeSinceStart(int i);

private:
    std::set<std::string> uniqueColumns;
    std::vector<std::string> columns;
    std::string name = std::string{"none"};
    MeasurementRun currentRun = {name, std::vector<std::string>{}};
    int counter = 0;
    SingleMeasure current;
    std::string m_directory;
};
