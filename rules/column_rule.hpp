
#ifndef COLUMNRULE_HPP
#define COLUMNRULE_HPP

#include "../igrid.hpp"
#include "irule.hpp"


class ColumnRule: public IRule
{
public:
    ColumnRule(const IGrid<int> &);

    std::vector<int> validNumbers(int row, int col) const override;
    std::vector<std::pair<int, int>> possibleLocations(int row, int col, int value) const override;

private:
    const IGrid<int>& m_grid;
};

#endif // COLUMNRULE_HPP
