cmake_minimum_required(VERSION 3.10)

project(TaskTrackerCLI VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_library(src
        src/command.cpp
        src/task.cpp
)

add_executable(tt TaskTrackerCLI.cpp)

target_link_libraries(tt src)
