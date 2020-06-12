
#include <gtest/gtest.h>

#include "rules/row_rule.hpp"
#include "grid.hpp"

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

    const auto valid_numbers = rule.validNumbers(0, 0);
    EXPECT_EQ(valid_numbers, (std::vector{2, 3, 4}));
}
