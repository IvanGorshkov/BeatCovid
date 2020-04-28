cmake_minimum_required(VERSION 3.16)
project(COVID19)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)

add_executable(COVID19 main.cpp)

INCLUDE_DIRECTORIES(project/include)

add_library(level project/src/Level_map.cpp)

include_directories(project/include/tinyxml)

add_subdirectory(project/include/tinyxml)

target_link_libraries(level tinyxml)

target_link_libraries(COVID19 sfml-graphics sfml-audio level)

