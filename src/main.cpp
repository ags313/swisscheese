#include <iostream>

#include "MeasurementStick.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    auto stick = DcsMeasurementStick{};
    stick.nameEvent("om");
    stick.nameEvent("om");
    stick.nameEvent("nom");

    std::cout << stick.nameAtIdx(0) << std::endl;
    std::cout << stick.nameAtIdx(1) << std::endl;
    std::cout << stick.nameAtIdx(2) << std::endl;
    std::cout << stick.nameAtIdx(3) << std::endl;

    stick.setMeasurementDirectory("/tmp/");
    stick.startMeasurementStream("ala");

    stick.startObservation();
    stick.observeSinceStart(1);
    stick.start(2);
    stick.finish(2);
    stick.endObservation();
    return 0;
}


