
#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <optional>
#include <tuple>
#include <vector>

#include "grid.hpp"


class Solver
{
public:
    Solver(const IGrid<int> &);

    std::vector<std::tuple<int, int, int>> generateSteps();
    int solve(int r, int c);

private:
    Grid<int> m_grid;

    std::vector<std::pair<int, int>> findGaps() const;
};

#endif // SOLVER_HPP
