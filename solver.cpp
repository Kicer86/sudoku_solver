
#include <algorithm>
#include <cassert>

#include "rules/column_rule.hpp"
#include "rules/row_rule.hpp"
#include "rules/square_rule.hpp"
#include "solver.hpp"


Solver::Solver(const IGrid<int>& grid)
    : m_grid(grid)
{
    m_gaps = findGaps();
}


std::vector<std::tuple<int, int, int>> Solver::findObvious()
{
    std::vector<std::tuple<int, int, int>> solutions;

    for(const auto& gap: m_gaps)
    {
        const int r = gap.first;
        const int c = gap.second;
        const int value = solve(r, c);

        if (value > 0)
            solutions.emplace_back(r, c, value);
    }

    return solutions;
}


std::vector<std::tuple<int, int, int>> Solver::findHidden()
{
    std::vector<std::tuple<int, int, int>> solutions;

    const ColumnRule column_rule(m_grid);
    const RowRule row_rule(m_grid);
    const SquareRule square_rule(m_grid);

    std::vector<const IRule *> rules = {&square_rule, &column_rule, &row_rule};
    std::sort(rules.begin(), rules.end());

    for(const auto& gap: m_gaps)
    {
        const int r = gap.first;
        const int c = gap.second;

        do
        {
            std::vector valid = rules.front()->validNumbers(r, c);
            for(const int value: valid)
            {
                std::vector possible_locations = rules.front()->possibleLocations(r, c, value);

                assert(possible_locations.empty() || possible_locations.size() > 1);

                if (possible_locations.size() > 1)
                {
                    std::vector<std::pair<int, int>> locations_after_elimination;

                    for(const auto& location: possible_locations)
                    {
                        bool allowed = true;
                        for (int i = 1; allowed && i < rules.size(); i++)
                        {
                            const auto valid_for_rule = rules[i]->validNumbers(location.first, location.second);
                            const bool rule_allows = std::any_of(valid_for_rule.cbegin(), valid_for_rule.cend(), [value](int i) { return i == value;} );

                            allowed &= rule_allows;
                        }

                        if (allowed)
                            locations_after_elimination.push_back(location);
                    }

                    if (locations_after_elimination.size() == 1)
                        solutions.emplace_back(locations_after_elimination.front().first,
                                            locations_after_elimination.front().second,
                                            value);
                }
            }
        }
        while(std::next_permutation(rules.begin(), rules.end()));
    }

    std::sort(solutions.begin(), solutions.end());
    const auto it = std::unique(solutions.begin(), solutions.end());
    solutions.erase(it, solutions.end());

    return solutions;
}


int Solver::solve(int r, int c)
{
    int v = 0;

    const ColumnRule column_rule(m_grid);
    const RowRule row_rule(m_grid);
    const SquareRule square_rule(m_grid);

    const auto valid1 = column_rule.validNumbers(r, c);
    const auto valid2 = row_rule.validNumbers(r, c);
    const auto valid3 = square_rule.validNumbers(r, c);

    std::vector<int> all12, all;
    std::set_intersection(valid1.begin(), valid1.end(),
                          valid2.begin(), valid2.end(),
                          std::back_inserter(all12));

    std::set_intersection(valid3.begin(), valid3.end(),
                          all12.begin(), all12.end(),
                          std::back_inserter(all));

    if (all.size() == 1)
        v = all.front();

    return v;
}


std::vector<std::pair<int, int>> Solver::findGaps() const
{
    std::vector<std::pair<int, int>> gaps;

    for (int i = 0; i < m_grid.rows(); i++)
        for (int j = 0; j < m_grid.columns(); j++)
            if (m_grid.get(i, j) == 0)
                gaps.emplace_back(i, j);

    return gaps;
}
