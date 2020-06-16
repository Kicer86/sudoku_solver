
#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <memory>
#include <optional>
#include <tuple>
#include <vector>

#include "igrid.hpp"

class IRule;

class Solver
{
public:
    Solver(const IGrid<int> &);
    ~Solver();

    std::vector<std::tuple<int, int, int>> solvable();

private:
    typedef std::pair<int, int> Gap;

    std::vector<Gap> m_gaps;
    std::vector<std::shared_ptr<IRule>> m_rules;
    const IGrid<int>& m_grid;

    std::vector<int> valuesMatchingAllRules(int r, int c);
    std::vector<int> valuesDissallowedInOtherCellsOfRule(int r, int c);
    std::vector<Gap> findGaps() const;
};

#endif // SOLVER_HPP
