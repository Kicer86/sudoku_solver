
#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "grid.hpp"
#include "solver.hpp"


template<typename T>
std::ostream& operator<<(std::ostream& os, const IGrid<T>& g)
{
    for(int i = 0; i < g.rows(); i++)
    {
        if ( i % 3 == 0)
            os << "+------+------+------+\n";

        for(int j = 0; j < g.columns(); j++)
        {
            if ( j % 3 == 0)
                os << "|";

            const int val = g.get(i, j);
            if (val == 0)
                os << "_";
            else
                os << val;

            os << " ";
        }

        os << "|\n";
    }

    os << "+------+------+------+\n";

    return os;
}


using testing::Contains;

TEST(SolverTest, easyPuzzle1StepByStep)
{
    Grid<int> grid
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
        // http://www.sudokuessentials.com/sudoku_for_kids.html
    };

    // step #1
    {
        Solver solver(grid);

        const auto steps = solver.findObvious();

        ASSERT_EQ(steps.size(), 10);
        EXPECT_THAT( steps, Contains( std::make_tuple(0, 0, 1)) );
        EXPECT_THAT( steps, Contains( std::make_tuple(0, 2, 3)) );
        EXPECT_THAT( steps, Contains( std::make_tuple(2, 6, 1)) );
        EXPECT_THAT( steps, Contains( std::make_tuple(3, 1, 1)) );
        EXPECT_THAT( steps, Contains( std::make_tuple(4, 5, 1)) );
        EXPECT_THAT( steps, Contains( std::make_tuple(5, 7, 1)) );
        EXPECT_THAT( steps, Contains( std::make_tuple(6, 0, 5)) );
        EXPECT_THAT( steps, Contains( std::make_tuple(6, 2, 2)) );
        EXPECT_THAT( steps, Contains( std::make_tuple(7, 3, 9)) );
        EXPECT_THAT( steps, Contains( std::make_tuple(8, 8, 1)) );

        grid.set(steps.begin(), steps.end());
    }

    // step #2
    {
        Solver solver(grid);

        const auto steps = solver.findObvious();

        ASSERT_EQ(steps.size(), 8);
        EXPECT_THAT( steps, Contains( std::make_tuple(1, 3, 1)) );
        EXPECT_THAT( steps, Contains( std::make_tuple(1, 5, 9)) );
        EXPECT_THAT( steps, Contains( std::make_tuple(2, 8, 5)) );
        EXPECT_THAT( steps, Contains( std::make_tuple(3, 0, 8)) );
        EXPECT_THAT( steps, Contains( std::make_tuple(4, 3, 8)) );
        EXPECT_THAT( steps, Contains( std::make_tuple(5, 8, 2)) );
        EXPECT_THAT( steps, Contains( std::make_tuple(7, 5, 3)) );
        EXPECT_THAT( steps, Contains( std::make_tuple(8, 6, 4)) );
    }
}


TEST(SolverTest, hardPuzzle1)
{
    const Grid<int> grid
    {
        { 1, 0, 0,  0, 7, 0,  0, 3, 0 },
        { 8, 3, 0,  6, 0, 0,  0, 0, 0 },
        { 0, 0, 2,  9, 0, 0,  6, 0, 8 },

        { 6, 0, 0,  0, 0, 4,  9, 0, 7 },
        { 0, 9, 0,  0, 0, 0,  0, 5, 0 },
        { 3, 0, 7,  5, 0, 0,  0, 0, 4 },

        { 2, 0, 3,  0, 0, 9,  1, 0, 0 },
        { 0, 0, 0,  0, 0, 2,  0, 4, 3 },
        { 0, 4, 0,  0, 8, 0,  0, 0, 9 }
        // by M. Feenstra, Den Haag - https://www.sudoku.ws/3-20.png
    };

    Solver solver(grid);

    const auto steps = solver.findObvious();

    ASSERT_EQ(steps.size(), 1);
    EXPECT_THAT( steps, Contains( std::make_tuple(4, 0, 4)) );

    const auto hidden = solver.findHidden();
    ASSERT_EQ(hidden.size(), 5);
    EXPECT_THAT( hidden, Contains( std::make_tuple(0, 2, 9)) );
    EXPECT_THAT( hidden, Contains( std::make_tuple(1, 7, 9)) );
    EXPECT_THAT( hidden, Contains( std::make_tuple(4, 6, 3)) );
    EXPECT_THAT( hidden, Contains( std::make_tuple(5, 4, 9)) );
    EXPECT_THAT( hidden, Contains( std::make_tuple(7, 0, 9)) );
}


TEST(SolverTest, hardPuzzleFullSolve)
{
    Grid<int> grid
    {
        { 1, 0, 0,  0, 7, 0,  0, 3, 0 },
        { 8, 3, 0,  6, 0, 0,  0, 0, 0 },
        { 0, 0, 2,  9, 0, 0,  6, 0, 8 },

        { 6, 0, 0,  0, 0, 4,  9, 0, 7 },
        { 0, 9, 0,  0, 0, 0,  0, 5, 0 },
        { 3, 0, 7,  5, 0, 0,  0, 0, 4 },

        { 2, 0, 3,  0, 0, 9,  1, 0, 0 },
        { 0, 0, 0,  0, 0, 2,  0, 4, 3 },
        { 0, 4, 0,  0, 8, 0,  0, 0, 9 }
        // by M. Feenstra, Den Haag - https://www.sudoku.ws/3-20.png
    };

    bool work = true;

    while(work)
    {
        work = false;

        for(;;)
        {
            Solver solver(grid);
            const auto steps = solver.findObvious();

            if (steps.empty())
                break;
            else
            {
                grid.set(steps.begin(), steps.end());
                work = true;
                continue;
            }
        }

        for(;;)
        {
            Solver solver(grid);
            const auto steps = solver.findHidden();

            if (steps.empty())
                break;
            else
            {
                grid.set(steps.begin(), steps.end());
                work = true;
                continue;
            }
        }
    }

    // @TODO: here grid should be solved
    std::cout << grid << '\n';
}
