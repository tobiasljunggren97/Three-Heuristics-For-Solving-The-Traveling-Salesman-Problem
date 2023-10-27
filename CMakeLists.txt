cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") # Maybe higher version is needed???

project(TSPAVALG)

add_executable(
    tsp
    main.cpp
)