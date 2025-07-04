cmake_minimum_required(VERSION 3.10)

project(TaskTrackerCLI VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(tt TaskTrackerCLI.cpp ${PROJECT_SOURCE_DIR}/src/cil.cpp)
