
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
}
