cmake_minimum_required(VERSION 3.28)
project(runner)

set(CMAKE_CXX_STANDARD 23)

set(EXE_SOURCES
        src/main.cpp
        ../library/src/swiss_meter/MeasurementApi.h
        ../library/src/swiss_meter/MeasurementApi.cpp
        ../library/src/swiss_meter/Output.h
        ../library/src/swiss_meter/Output.cpp
        ../library/src/swiss_meter/Output.cpp
        ../library/src/swiss_meter/SingleMeasure.cpp
        ../library/src/swiss_meter/SingleMeasure.h
)

add_executable(exeTest ${EXE_SOURCES})
