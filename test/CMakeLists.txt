cmake_minimum_required(VERSION 3.16)


set(This TestingSuite)

set(Sources 
    TestingSuite.cpp
    #MinWeightTests.cpp
    GraphClassTests.cpp
    EularianTSPTourTests.cpp
    PrimsTest.cpp
    GreedyAlgorithmsTests.cpp
    TwoOptTests.cpp
)

add_executable(${This} ${Sources})

target_link_libraries(${This} PUBLIC
    gtest_main
    TSPAVALG
)

add_test(
    NAME ${This}
    COMMAND ${This}
)


#set_tests_properties(${This} PROPERTIES ENVIRONMENT "GTEST_FILTER=EularianTour*")


