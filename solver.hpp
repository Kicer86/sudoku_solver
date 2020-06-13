
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

    std::vector<std::pair<int, int>> findGaps() const;
};

#endif // SOLVER_HPP
