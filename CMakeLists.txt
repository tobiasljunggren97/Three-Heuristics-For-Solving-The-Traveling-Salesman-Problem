cmake_minimum_required(VERSION 3.16)

set(This TSPAVALG)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)

set(Headers
    Christofides.h
    # BinaryHeapChristofides.h
    # GlobalsChristofides.h
    # GraphChristofides.h
    # MatchingChristofides.h
    Graph.h
    Stopwatch.h
    hungarian.h
    LocalImprovements.h
    Greedy.h
)

set(Sources
    Christofides.cpp
    # BinaryHeapChristofides.cpp
    # GraphChristofides.cpp
    # MatchingChristofides.cpp
    Graph.cpp
    main.cpp
    Stopwatch.cpp
    hungarian.cpp
    LocalImprovements.cpp
    Greedy.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})

add_subdirectory(test)

add_executable(
    tsp
    main.cpp
    Graph.cpp
    Christofides.cpp
    # BinaryHeapChristofides.cpp
    # GraphChristofides.cpp
    # MatchingChristofides.cpp
    Stopwatch.cpp
    hungarian.cpp
    LocalImprovements.cpp
    Greedy.cpp
)
