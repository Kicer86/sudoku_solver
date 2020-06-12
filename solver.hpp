
#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <tuple>
#include <vector>

#include "grid.hpp"


class Solver
{
public:
    Solver(const IGrid<int> &);

    std::vector<std::tuple<int, int, int>> generateSteps();

private:
    Grid<int> m_grid;
};

#endif // SOLVER_HPP
