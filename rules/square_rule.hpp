
#ifndef SQUARERULE_HPP
#define SQUARERULE_HPP

#include "../igrid.hpp"
#include "irule.hpp"


class SquareRule: public IRule
{
public:
    SquareRule(const IGrid<int> &);

    virtual std::vector<int> validNumbers(int row, int col) const override;

private:
    const IGrid<int>& m_grid;
};

#endif // SQUARERULE_HPP
