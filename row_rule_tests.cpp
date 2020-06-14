
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "rules/row_rule.hpp"
#include "grid.hpp"

using testing::Contains;


TEST(RowRuleTest, emptyRow)
{
    Grid<int> grid(2, 9);

    RowRule rule(grid);

    const auto valid_numbers = rule.validNumbers(0, 0);
    EXPECT_EQ(valid_numbers, (std::vector{1, 2, 3, 4, 5, 6, 7, 8, 9}));
}


TEST(RowRuleTest, mixedRow)
{
    const Grid<int> grid
    {
        {6, 0, 1, 5, 0, 0},
        {0, 2, 0, 3, 1, 0}
    };

    RowRule rule(grid);

    const auto valid_numbers = rule.validNumbers(1, 0);
    EXPECT_EQ(valid_numbers, (std::vector{4, 5, 6}));
}


TEST(RowRuleTest, fullRow)
{
    const Grid<int> grid
    {
        {6, 0, 1, 5, 0, 0},
        {0, 2, 0, 3, 1, 0},
        {1, 2, 6, 5, 4, 3}
    };

    const RowRule rule(grid);
    const auto valid_numbers = rule.validNumbers(2, 4);

    EXPECT_TRUE(valid_numbers.empty());
}


TEST(RowRuleTest, alternativeLocations)
{
    const Grid<int> grid
    {
        {6, 0, 1, 5, 0, 0},
        {0, 2, 0, 3, 9, 0},
        {5, 4, 6, 0, 2, 1},
        {7, 0, 0, 0, 0, 0},
        {0, 3, 0, 0, 1, 0},
        {0, 0, 2, 0, 3, 0}
    };

    RowRule rule(grid);

    const auto valid_positions = rule.possibleLocations(3, 5, 4);
    ASSERT_EQ(valid_positions.size(), 5);
    EXPECT_THAT(valid_positions, Contains( std::pair(3, 1)) );
    EXPECT_THAT(valid_positions, Contains( std::pair(3, 2)) );
    EXPECT_THAT(valid_positions, Contains( std::pair(3, 3)) );
    EXPECT_THAT(valid_positions, Contains( std::pair(3, 4)) );
    EXPECT_THAT(valid_positions, Contains( std::pair(3, 5)) );
}


TEST(RowRuleTest, noAlternativeLocations)
{
    const Grid<int> grid
    {
        {6, 0, 1, 5, 0, 0},
        {0, 2, 0, 3, 9, 0},
        {5, 4, 6, 0, 2, 1},
        {7, 0, 0, 0, 0, 0},
        {0, 3, 0, 0, 1, 0},
        {0, 0, 2, 0, 3, 0}
    };

    RowRule rule(grid);

    const auto valid_positions = rule.possibleLocations(3, 5, 7);
    ASSERT_TRUE(valid_positions.empty());
}
