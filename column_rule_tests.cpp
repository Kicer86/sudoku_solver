
#include <gtest/gtest.h>

#include "rules/column_rule.hpp"
#include "grid.hpp"

TEST(ColumnRuleTest, emptyColumn)
{
    Grid<int> grid(5, 9);

    ColumnRule rule(grid);

    const auto valid_numbers = rule.validNumbers(3, 2);
    EXPECT_EQ(valid_numbers, (std::vector{1, 2, 3, 4, 5}));
}


TEST(ColumnRuleTest, mixedColumn)
{
    const Grid<int> grid
    {
        {6, 0, 1, 5, 0, 0},
        {0, 2, 0, 3, 1, 0},
        {5, 4, 6, 0, 3, 1}
    };

    ColumnRule rule(grid);

    const auto valid_numbers = rule.validNumbers(1, 4);
    EXPECT_EQ(valid_numbers, (std::vector{2}));
}


TEST(ColumnRuleTest, fullColumn)
{
    const Grid<int> grid
    {
        {6, 0, 1, 1, 0, 0},
        {0, 2, 0, 3, 1, 0},
        {1, 2, 6, 2, 4, 3}
    };

    const ColumnRule rule(grid);
    const auto valid_numbers = rule.validNumbers(1, 3);

    EXPECT_TRUE(valid_numbers.empty());
}
