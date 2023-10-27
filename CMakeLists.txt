cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") # Maybe higher version is needed???

set(This TSPAVALG)



project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)

set(Headers
    Christofides.h
    BinaryHeapChristofides.h
    GlobalsChristofides.h
    GraphChristofides.h
    MatchingChristofides.h
    Graph.h
)

set(Sources
    Christofides.cpp
    BinaryHeapChristofides.cpp
    GraphChristofides.cpp
    MatchingChristofides.cpp
    Graph.cpp
    main.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})

add_subdirectory(test)

add_executable(
    tsp
    main.cpp
    Graph.cpp
    Christofides.cpp
    BinaryHeapChristofides.cpp
    GraphChristofides.cpp
    MatchingChristofides.cpp
)
