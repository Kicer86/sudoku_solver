
#include <algorithm>

#include "rules/column_rule.hpp"
#include "rules/row_rule.hpp"
#include "rules/square_rule.hpp"
#include "solver.hpp"


Solver::Solver(const IGrid<int>& grid)
    : m_grid(grid)
{

}


std::vector<std::tuple<int, int, int>> Solver::generateSteps()
{
    std::vector<std::tuple<int, int, int> > steps;

    const ColumnRule column_rule(m_grid);
    const RowRule row_rule(m_grid);
    const SquareRule square_rule(m_grid);

    bool work = true;
    while (work)
    {
        work = false;

        for (int i = 0; i < m_grid.rows(); i++)
            for (int j = 0; j < m_grid.columns(); j++)
                if (m_grid.get(i, j) == 0)
                {
                    const auto valid1 = column_rule.validNumbers(i, j);
                    const auto valid2 = row_rule.validNumbers(i, j);
                    const auto valid3 = square_rule.validNumbers(i, j);

                    std::vector<int> all12, all;
                    std::set_intersection(valid1.begin(), valid1.end(),
                                        valid2.begin(), valid2.end(),
                                        std::back_inserter(all12));

                    std::set_intersection(valid3.begin(), valid3.end(),
                                        all12.begin(), all12.end(),
                                        std::back_inserter(all));

                    if (all.size() == 1)
                    {
                        const int value = all.front();
                        steps.emplace_back(i, j, value);
                        m_grid.set(i, j, value);
                        work = true;
                    }
                }
    }

    return steps;
}
