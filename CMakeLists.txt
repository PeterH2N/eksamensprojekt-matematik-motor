# CMakeList.txt : CMake project for Eksamensprojekt-mathengine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project ("Eksamensprojekt-mathengine")

file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HDR_FILES ${PROJECT_SOURCE_DIR}/src/*.hpp)

include_directories(${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/src/factors)

# Add source to this project's executable.
add_executable (Eksamensprojekt-mathengine "application.cpp" ${SRC_FILES} ${HDR_FILES} )


# TODO: Add tests and install targets if needed.
