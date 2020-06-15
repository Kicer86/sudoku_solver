
#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <optional>
#include <tuple>
#include <vector>

#include "igrid.hpp"

class IRule;

class Solver
{
public:
    Solver(const IGrid<int> &);

    std::vector<std::tuple<int, int, int>> findObvious();

private:
    typedef std::pair<int, int> Gap;

    std::vector<Gap> m_gaps;
    const IGrid<int>& m_grid;

    int allRulesOneCell(const std::vector<const IRule *> &, int r, int c);
    std::vector<std::tuple<int, int, int>> valueAllowedSomewhereElse(const std::vector<const IRule *> &, int r, int c);
    std::vector<Gap> findGaps() const;
};

#endif // SOLVER_HPP
