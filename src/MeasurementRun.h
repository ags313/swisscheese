#pragma once
#include <chrono>


class MeasurementRun {
public:
    void record(int idx);

    void end();

    MeasurementRun(const std::string & name,
                   const std::vector<std::string> &vector) : m_name(name), m_columns(vector) {};

private:
    std::string m_name;
    std::vector<std::string> m_columns;
};

inline void MeasurementRun::end() {
}



