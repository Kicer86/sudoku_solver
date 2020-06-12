
#include <algorithm>

#include "row_rule.hpp"


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
    for(int i = 1; i <= numbers; i++)
        valid.push_back(i);

    for(int i = 0; i < columns; i++)
    {
        const int cell_value = m_grid.get(row, i);
        if (cell_value > 0)
        {
            const auto last = std::remove(valid.begin(), valid.end(), cell_value);
            valid.erase(last, valid.end());
        }
    }

    return valid;
}

