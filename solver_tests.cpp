
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "grid.hpp"
#include "solver.hpp"


using testing::Contains;

TEST(SolverTest, easyPuzzle1)
{
    const Grid<int> grid
    {
        { 0, 2, 0,  4, 5, 6,  7, 8, 9 },
        { 4, 5, 7,  0, 8, 0,  2, 3, 6 },
        { 6, 8, 9,  2, 3, 7,  0, 4, 0 },

        { 0, 0, 5,  3, 6, 2,  9, 7, 4 },
        { 2, 7, 4,  0, 9, 0,  6, 5, 3 },
        { 3, 9, 6,  5, 7, 4,  8, 0, 0 },

        { 0, 4, 0,  6, 1, 8,  3, 9, 7 },
        { 7, 6, 1,  0, 4, 0,  5, 2, 8 },
        { 9, 3, 8,  7, 2, 5,  0, 6, 0 }
    };

    Solver solver(grid);

    const auto steps = solver.generateSteps();

    ASSERT_EQ(steps.size(), 18);
    EXPECT_THAT(steps, Contains( std::make_tuple(0, 0, 1)) );
    EXPECT_THAT(steps, Contains( std::make_tuple(0, 2, 3)) );
    EXPECT_THAT(steps, Contains( std::make_tuple(1, 3, 1)) );
    EXPECT_THAT(steps, Contains( std::make_tuple(1, 5, 9)) );
    EXPECT_THAT(steps, Contains( std::make_tuple(2, 6, 1)) );
    EXPECT_THAT(steps, Contains( std::make_tuple(2, 8, 5)) );
    EXPECT_THAT(steps, Contains( std::make_tuple(3, 0, 8)) );
    EXPECT_THAT(steps, Contains( std::make_tuple(3, 1, 1)) );
    EXPECT_THAT(steps, Contains( std::make_tuple(4, 3, 8)) );
    EXPECT_THAT(steps, Contains( std::make_tuple(4, 5, 1)) );
    EXPECT_THAT(steps, Contains( std::make_tuple(5, 7, 1)) );
    EXPECT_THAT(steps, Contains( std::make_tuple(5, 8, 2)) );

    EXPECT_THAT(steps, Contains( std::make_tuple(6, 0, 5)) );
    EXPECT_THAT(steps, Contains( std::make_tuple(6, 2, 2)) );
    EXPECT_THAT(steps, Contains( std::make_tuple(7, 3, 9)) );
    EXPECT_THAT(steps, Contains( std::make_tuple(7, 5, 3)) );
    EXPECT_THAT(steps, Contains( std::make_tuple(8, 6, 4)) );
    EXPECT_THAT(steps, Contains( std::make_tuple(8, 8, 1)) );
}
