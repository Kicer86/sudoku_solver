
#include <gtest/gtest.h>

#include "grid.hpp"


TEST(GridTest, dimensions)
{
    Grid<int> g1(10, 20);

    EXPECT_EQ(g1.rows(), 10);
    EXPECT_EQ(g1.columns(), 20);

    Grid<float> g2(3, 6);

    EXPECT_EQ(g2.rows(), 3);
    EXPECT_EQ(g2.columns(), 6);
}


TEST(GridTest, dimensionsInitializerList)
{
    Grid<int> g1
    {
        {1, 2, 3},
        {4, 5, 6}
    };

    EXPECT_EQ(g1.rows(), 2);
    EXPECT_EQ(g1.columns(), 3);

    Grid<float> g2 =
    {
        {1, 2, 3, 4},
        {4, 5, 6, 7},
        {0, 0, 0, 0}
    };

    EXPECT_EQ(g2.rows(), 3);
    EXPECT_EQ(g2.columns(), 4);
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


TEST(GridTest, valuesInitializerList)
{
    Grid<float> grid
    {
        {1, 2, 3, 4},
        {4, 5, 6, 7},
        {0, 0, 0, 0}
    };

    EXPECT_EQ(grid.get(0, 0), 1);
    EXPECT_EQ(grid.get(2, 1), 0);
    EXPECT_EQ(grid.get(2, 2), 0);
    EXPECT_EQ(grid.get(0, 3), 4);
}
