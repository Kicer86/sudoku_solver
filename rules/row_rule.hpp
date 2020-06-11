#ifndef ROWRULE_HPP
#define ROWRULE_HPP

#include <vector>

#include "../igrid.hpp"
#include "irule.hpp"


class RowRule: public IRule
{
public:
    RowRule(const IGrid<int> &);

    std::vector<int> validNumbers(int row, int col) const override;

private:
    const IGrid<int>& m_grid;
};

#endif
