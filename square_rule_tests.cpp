
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "rules/square_rule.hpp"
#include "grid.hpp"

using testing::Contains;


TEST(SquareRuleTest, emptySquare)
{
    const Grid<int> grid(9, 9);
    const SquareRule rule(grid);

    const auto valid1 = rule.validNumbers(1, 2);
    const auto valid2 = rule.validNumbers(4, 5);

    EXPECT_EQ(valid1, (std::vector{1, 2, 3, 4, 5, 6, 7, 8, 9}));
    EXPECT_EQ(valid2, (std::vector{1, 2, 3, 4, 5, 6, 7, 8, 9}));
}


TEST(SquareRuleTest, mixedSquares)
{
    const Grid<int> grid
    {
        { 1, 2, 3,  0, 0 ,0},
        { 4, 5, 6,  0, 0, 0},
        { 0, 7, 8,  1, 9, 0},

        { 8, 9, 1,  5, 2, 3},
        { 0, 0, 2,  1, 0, 9},
        { 4, 5, 0,  6, 0, 8}
    };

    const SquareRule rule(grid);

    const auto valid1 = rule.validNumbers(2, 2);
    const auto valid2 = rule.validNumbers(3, 3);

    EXPECT_EQ(valid1, (std::vector{9}));
    EXPECT_EQ(valid2, (std::vector{4, 7}));
}


TEST(SquareRuleTest, fullSquares)
{
    const Grid<int> grid
    {
        { 1, 2, 3,  0, 0 ,0},
        { 4, 5, 6,  0, 0, 0},
        { 9, 7, 8,  1, 9, 0},

        { 8, 9, 1,  5, 2, 3},
        { 0, 0, 2,  1, 4, 9},
        { 4, 5, 0,  6, 7, 8}
    };

    const SquareRule rule(grid);

    const auto valid1 = rule.validNumbers(0, 0);
    const auto valid2 = rule.validNumbers(5, 5);

    EXPECT_TRUE(valid1.empty());
    EXPECT_TRUE(valid2.empty());
}



TEST(SquareRuleTest, alternativeLocations)
{
    const Grid<int> grid
    {
        { 1, 2, 3,  0, 0 ,0},
        { 4, 5, 6,  0, 0, 0},
        { 9, 7, 8,  1, 9, 0},

        { 8, 9, 1,  5, 2, 3},
        { 0, 0, 2,  1, 4, 9},
        { 4, 5, 0,  6, 7, 8}
    };

    SquareRule rule(grid);

    const auto valid_positions = rule.possibleLocations(4, 0, 3);
    ASSERT_EQ(valid_positions.size(), 3);
    EXPECT_THAT(valid_positions, Contains( std::pair(4, 0)) );
    EXPECT_THAT(valid_positions, Contains( std::pair(4, 1)) );
    EXPECT_THAT(valid_positions, Contains( std::pair(5, 2)) );
}


TEST(SquareRuleTest, noAlternativeLocations)
{
    const Grid<int> grid
    {
        { 1, 2, 3,  0, 0 ,0},
        { 4, 5, 6,  0, 0, 0},
        { 9, 7, 8,  1, 9, 0},

        { 8, 9, 1,  5, 2, 3},
        { 0, 0, 2,  1, 4, 9},
        { 4, 5, 0,  6, 7, 8}
    };

    SquareRule rule(grid);

    const auto valid_positions = rule.possibleLocations(3, 5, 7);
    ASSERT_TRUE(valid_positions.empty());
}
