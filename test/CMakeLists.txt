cmake_minimum_required(VERSION 3.16)


set(This TestingSuite)

set(Sources 
    TestingSuite.cpp
    MinWeightTests.cpp
    GraphClassTests.cpp
    PrimsTest.cpp
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


