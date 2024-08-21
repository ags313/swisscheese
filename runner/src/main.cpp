#include <thread>

#include "../../library/src/swiss_meter/MeasurementApi.h"

#include <iostream>

int main() {
    auto m = SwissMeter::MeasurementApi{};
    m.nameEvent("beforSubcallMicros");
    m.nameEvent("frameMicros");
    m.nameEvent("frameStartToOnCallbackMicros");
    m.nameEvent("afterSubcallMicros");
    m.nameEvent("players");

    m.setMeasurementDirectory("c:/temp/swisstest/");
    m.startMeasurementStream("ala");

    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() << std::endl;

    for (int missions = 0; missions < 2; missions++) {
        m.startMeasurementStream(std::format("ala {}", missions));
        for (int i = 0; i < 128 * 1024; i++) {
            m.startObservation();

            m.observeSinceStart(1);
            m.start(2);
            m.observeSinceStart(3);
            std::this_thread::sleep_for(std::chrono::nanoseconds(1));
            m.finish(2);
            m.start(4);
            std::this_thread::sleep_for(std::chrono::nanoseconds(1));
            m.finish(4);

            m.observerRawValue(5, i);
            m.endObservation();
            std::this_thread::sleep_for(std::chrono::nanoseconds(1));
        }
    }

    const auto now = std::chrono::high_resolution_clock::now();
    const auto seconds = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
    std::cout << seconds << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(600));
    m.shutdown();

    return 0;
}


