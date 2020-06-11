#ifndef GRID_HPP
#define GRID_HPP

template<typename T>
class Grid
{
    public:
        Grid(int rows, int cols)
            : m_rows(rows)
            , m_cols(cols)
        {

        }

        int rows() const
        {
            return m_rows;
        }

        int columns() const
        {
            return m_cols;
        }

    private:
        const int m_rows;
        const int m_cols;
};

#endif // GRID_HPP
