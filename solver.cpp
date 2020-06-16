
#include <algorithm>
#include <cassert>

#include "rules/column_rule.hpp"
#include "rules/row_rule.hpp"
#include "rules/square_rule.hpp"
#include "solver.hpp"


namespace
{
    bool doesRuleAllowNumber(const std::shared_ptr<IRule>& rule, int r, int c, int value)
    {
        const auto valid_for_rule = rule->validNumbers(r, c);
        const bool rule_allows = std::any_of(valid_for_rule.cbegin(), valid_for_rule.cend(), [value](int i) { return i == value;} );

        return rule_allows;
    }
}


Solver::Solver(const IGrid<int>& grid)
    : m_grid(grid)
{
    m_gaps = findGaps();
    m_rules.emplace_back(std::make_unique<SquareRule>(m_grid));
    m_rules.emplace_back(std::make_unique<RowRule>(m_grid));
    m_rules.emplace_back(std::make_unique<ColumnRule>(m_grid));
}


Solver::~Solver()
{

}


std::vector<std::tuple<int, int, int>> Solver::solvable()
{
    std::vector<std::tuple<int, int, int>> all_solutions;

    for(const auto& gap: m_gaps)
    {
        const int r = gap.first;
        const int c = gap.second;

        int value = valueMatchingAllRules(r, c);

        if (value > 0)
        {
            all_solutions.emplace_back(r, c, value);
            continue;
        }

        value = valueDissallowedInOtherCellsOfRule(r, c);

        if (value > 0)
        {
            all_solutions.emplace_back(r, c, value);
            continue;
        }
    }

    return all_solutions;
}


int Solver::valueMatchingAllRules(int r, int c)
{
    int v = 0;

    std::vector<int> intersection;
    for (const auto& rule: m_rules)
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


int Solver::valueDissallowedInOtherCellsOfRule(int r, int c)
{
    int solution = 0;

    auto rules = m_rules;
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
                    const bool allowed = std::all_of(std::next(rules.begin()), rules.end(), [&location, value](const auto& rule) {
                        return doesRuleAllowNumber(rule, location.first, location.second, value);
                    });

                    if (allowed)
                        locations_after_elimination.push_back(location);
                }

                if (locations_after_elimination.size() == 1 &&
                    locations_after_elimination.front().first == r &&
                    locations_after_elimination.front().second == c)
                {
                    solution = value;
                    break;
                }
            }
        }
    }
    while(solution == 0 && std::next_permutation(rules.begin(), rules.end()));

    return solution;
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
