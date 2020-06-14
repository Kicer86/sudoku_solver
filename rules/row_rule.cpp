
#include "row_rule.hpp"
#include "utils.hpp"


RowRule::RowRule(const IGrid<int>& grid)
    : m_grid(grid)
{

}


std::vector<int> RowRule::validNumbers(int row, int col) const
{
    std::vector<int> valid;

    const int columns = m_grid.columns();
    const int numbers = columns;            // possible numbers == number of columns in grid

    valid.reserve(numbers);
    valid = utils::fill(numbers);

    for(int i = 0; i < columns; i++)
    {
        const int cell_value = m_grid.get(row, i);
        if (cell_value > 0)
            utils::erase(valid, cell_value);
    }

    return valid;
}


std::vector<std::pair<int, int>> RowRule::possibleLocations(int row, int col, int value) const
{
    std::vector<std::pair<int, int>> locations;

    const int columns = m_grid.columns();
    bool contains_value = false;

    for(int i = 0; i < columns; i++)
    {
        const int cell_value = m_grid.get(row, i);
        if (cell_value == value)
        {
            contains_value = true;
            break;
        }
    }

    if (contains_value == false)
        for(int i = 0; i < columns; i++)
        {
            const int cell_value = m_grid.get(row, i);
            if (cell_value == 0)
                locations.emplace_back(row, i);
        }

    return locations;
}
