
project(sudoku_solver)

cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)

add_executable(sudoku_solver
    main.cpp
    grid.hpp
)

enable_testing()

add_executable(sudoku_solver_tests
    column_rule_tests.cpp
    grid_tests.cpp
    row_rule_tests.cpp
    solver_tests.cpp
    square_rule_tests.cpp
    utils_tests.cpp

    rules/column_rule.cpp
    rules/row_rule.cpp
    rules/square_rule.cpp
    rules/utils.cpp
    solver.cpp
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
