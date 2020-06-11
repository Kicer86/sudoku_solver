
#include <gtest/gtest.h>

#include "grid.hpp"


TEST(GridTest, constructor)
{
    Grid<int> grid(1, 1);
}


TEST(GridTest, dimensions)
{
    Grid<int> g1(10, 20);

    EXPECT_EQ(g1.rows(), 10);
    EXPECT_EQ(g1.columns(), 20);

    Grid<float> g2(3, 6);

    EXPECT_EQ(g2.rows(), 3);
    EXPECT_EQ(g2.columns(), 6);
}


TEST(GridTest, values)
{
    Grid<int> grid(3, 3);

    grid.set(0, 0, 5);
    grid.set(2, 1, 10);

    EXPECT_EQ(grid.get(0, 0), 5);
    EXPECT_EQ(grid.get(2, 1), 10);
    EXPECT_EQ(grid.get(2, 2), 0);
}
