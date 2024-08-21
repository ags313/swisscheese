#pragma once
#include <chrono>

namespace SwissMeter {
    class MeasurementSession {
    public:
        void record(int idx);

        void end();

        MeasurementSession(const std::string & name,
                       const std::vector<std::string> &vector) : name_(name), columns_(vector) {};

    private:
        std::string name_;
        std::vector<std::string> columns_;
    };

    inline void MeasurementSession::end() {
    }
}




