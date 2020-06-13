
#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <optional>
#include <tuple>
#include <vector>

#include "igrid.hpp"


class Solver
{
public:
    Solver(const IGrid<int> &);

    std::vector<std::tuple<int, int, int>> findObvious();
    int solve(int r, int c);

private:
    typedef std::pair<int, int> Gap;

    const IGrid<int>& m_grid;

    std::vector<Gap> findGaps() const;
};

#endif // SOLVER_HPP
