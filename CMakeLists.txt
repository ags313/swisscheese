cmake_minimum_required(VERSION 3.21)

project ("swisswatch-parent")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_FIND_DEBUG_MODE TRUE)

add_subdirectory(library)
add_subdirectory(runner)
