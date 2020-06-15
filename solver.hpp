
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
    std::vector<std::tuple<int, int, int>> findHidden();

private:
    typedef std::pair<int, int> Gap;

    std::vector<Gap> m_gaps;
    const IGrid<int>& m_grid;

    int allRulesOneCell(int r, int c);
    std::vector<Gap> findGaps() const;
};

#endif // SOLVER_HPP
