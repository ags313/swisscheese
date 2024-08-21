cmake_minimum_required(VERSION 3.21)
project(swisscheese)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)

FetchContent_Declare(
        readerwriterqueue
        GIT_REPOSITORY    https://github.com/cameron314/readerwriterqueue
        GIT_TAG           master
)

FetchContent_MakeAvailable(readerwriterqueue)

set(LIBRARY_SOURCES
        src/swiss_meter/MeasurementApi.h
        src/swiss_meter/MeasurementSession.h
        src/swiss_meter/MeasurementApi.cpp
        src/swiss_meter/SingleMeasure.h
        src/swiss_meter/Output.cpp
        src/swiss_meter/Output.h
        src/swiss_meter/SingleMeasure.cpp
        src/library.cpp
        src/library.h
        src/swiss_meter/lua_interop.h
)

include_directories("../lua/include")
link_directories(
        "../lua"
)
find_library(LUA_LIB lua "../lua")

include(GenerateExportHeader)
add_library(swisscheese SHARED ${LIBRARY_SOURCES})

set_target_properties(swisscheese PROPERTIES PREFIX "")

target_link_libraries(swisscheese
        ${LUA_LIB}
        readerwriterqueue
)

target_include_directories(swisscheese PUBLIC ${LIBRARY_SOURCES} ${readerwriterqueue_SOURCE_DIR})