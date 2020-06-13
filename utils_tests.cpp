
#include <gtest/gtest.h>

#include "rules/utils.hpp"


TEST(RulesUtilsTest, fill)
{
    const std::vector<int> f1 = utils::fill(5);
    const std::vector<int> f2 = utils::fill(10);

    EXPECT_EQ(f1, (std::vector{1, 2, 3, 4, 5}));
    EXPECT_EQ(f2, (std::vector{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}));
}


TEST(RulesUtilsTest, erase)
{
    std::vector values = { 1, 2, 4, 9};
    utils::erase(values, 4);

    EXPECT_EQ(values, (std::vector{1, 2, 9}));
}
