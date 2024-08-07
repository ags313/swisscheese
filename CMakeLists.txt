cmake_minimum_required(VERSION 3.28)
project(swissWatch)

set(CMAKE_CXX_STANDARD 23)

add_executable(swissWatch src/main.cpp
        src/MeasurementStick.h
        src/MeasurementRun.h
        src/MeasurementStick.cpp
        src/SingleMeasure.h
        src/MeasurementRun.cpp)
