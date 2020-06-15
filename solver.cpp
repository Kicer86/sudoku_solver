
#include <algorithm>
#include <cassert>

#include "rules/column_rule.hpp"
#include "rules/row_rule.hpp"
#include "rules/square_rule.hpp"
#include "solver.hpp"


namespace
{
    bool doesRuleAllowNumber(const IRule* rule, int r, int c, int value)
    {
        const auto valid_for_rule = rule->validNumbers(r, c);
        const bool rule_allows = std::any_of(valid_for_rule.cbegin(), valid_for_rule.cend(), [value](int i) { return i == value;} );

        return rule_allows;
    }

    void dropDuplicates(std::vector<std::tuple<int, int, int>>& solutions)
    {
        std::sort(solutions.begin(), solutions.end());
        const auto it = std::unique(solutions.begin(), solutions.end());
        solutions.erase(it, solutions.end());
    }
}


Solver::Solver(const IGrid<int>& grid)
    : m_grid(grid)
{
    m_gaps = findGaps();
}


std::vector<std::tuple<int, int, int>> Solver::solvable()
{
    const ColumnRule column_rule(m_grid);
    const RowRule row_rule(m_grid);
    const SquareRule square_rule(m_grid);

    std::vector<std::tuple<int, int, int>> all_solutions;
    std::vector<const IRule *> rules = {&square_rule, &column_rule, &row_rule};

    for(const auto& gap: m_gaps)
    {
        const int r = gap.first;
        const int c = gap.second;

        const int value = allRulesOneCell(rules, r, c);

        if (value > 0)
        {
            all_solutions.emplace_back(r, c, value);
            continue;
        }

        const auto solutions = valueAllowedSomewhereElse(rules, r, c);

        if (solutions.empty() == false)
        {
            all_solutions.insert(all_solutions.end(), solutions.begin(), solutions.end());
            continue;
        }
    }

    dropDuplicates(all_solutions);

    return all_solutions;
}


std::vector<std::tuple<int, int, int>> Solver::valueAllowedSomewhereElse(const std::vector<const IRule *>& source_rules, int r, int c)
{
    std::vector<std::tuple<int, int, int>> solutions;

    auto rules = source_rules;
    std::sort(rules.begin(), rules.end());

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
                    const bool allowed = std::all_of(std::next(rules.begin()), rules.end(), [&location, value](const IRule* rule) {
                        return doesRuleAllowNumber(rule, location.first, location.second, value);
                    });

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

    dropDuplicates(solutions);

    return solutions;
}


int Solver::allRulesOneCell(const std::vector<const IRule *>& rules, int r, int c)
{
    int v = 0;

    std::vector<int> intersection;
    for (const IRule* rule: rules)
    {
        const auto valid = rule->validNumbers(r, c);

        if (intersection.empty())
            intersection = valid;
        else
        {
            std::vector<int> internal_intersection;
            std::set_intersection(valid.begin(), valid.end(),
                                  intersection.begin(), intersection.end(),
                                  std::back_inserter(internal_intersection));

            intersection = internal_intersection;
        }
    }

    if (intersection.size() == 1)
        v = intersection.front();

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
