
project(sudoku_solver)

cmake_minimum_required(VERSION 3.17)

find_package(GTest REQUIRED)

add_executable(sudoku_solver
    main.cpp
    grid.hpp
)

enable_testing()

add_executable(grid_tests
    grid_tests.cpp
)

target_link_libraries(grid_tests
    PRIVATE
        GTest::gtest
        GTest::gtest_main
)

add_test(AllTests
    grid_tests
)

add_custom_target(RunUnitTests ALL
    COMMAND ctest
    DEPENDS grid_tests
)
