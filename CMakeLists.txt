cmake_minimum_required(VERSION 3.21)

project ("swisswatch-parent")

set(CMAKE_CXX_STANDARD 23)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(library)
add_subdirectory(runner)