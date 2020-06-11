
project(sudoku_solver)

cmake_minimum_required(VERSION 3.17)

find_package(GTest REQUIRED)

add_executable(sudoku_solver
    main.cpp
    grid.hpp
)

enable_testing()

add_executable(sudoku_solver_tests
    grid_tests.cpp
    row_rule_tests.cpp
)


target_link_libraries(sudoku_solver_tests
    PRIVATE
        GTest::gtest
        GTest::gtest_main
)

add_test(AllTests
    sudoku_solver_tests
)

add_custom_target(RunUnitTests ALL
    COMMAND ctest
    DEPENDS sudoku_solver_tests
)
