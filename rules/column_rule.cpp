
#include "column_rule.hpp"
#include "utils.hpp"


ColumnRule::ColumnRule(const IGrid<int>& grid)
    : m_grid(grid)
{

}


std::vector<int> ColumnRule::validNumbers(int row, int col) const
{
    std::vector<int> valid;

    const int rows = m_grid.rows();
    const int numbers = rows;            // possible numbers == number of row in grid

    valid.reserve(numbers);
    valid = utils::fill(numbers);

    for(int i = 0; i < rows; i++)
    {
        const int cell_value = m_grid.get(i, col);
        if (cell_value > 0)
            utils::erase(valid, cell_value);
    }

    return valid;
}
