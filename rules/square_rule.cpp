
#include "square_rule.hpp"
#include "utils.hpp"


SquareRule::SquareRule(const IGrid<int>& grid)
    : m_grid(grid)
{

}


std::vector<int> SquareRule::validNumbers(int row, int col) const
{
    std::vector<int> valid;

    valid.reserve(3 * 3);
    valid = utils::fill(3 * 3);

    const int base_row = (row / 3) * 3;
    const int base_col = (col / 3) * 3;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            const int cell_value = m_grid.get(base_row + i, base_col + j);
            if (cell_value > 0)
                utils::erase(valid, cell_value);
        }

    return valid;
}
