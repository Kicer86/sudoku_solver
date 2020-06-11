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
            m_matrix.reserve(rows);

            for(int i = 0; i < rows; i++)            // fill rows
                m_matrix.push_back(Row(cols, {}));   // with Row filled with 'cols` items
        }

        int rows() const
        {
            return m_rows;
        }

        int columns() const
        {
            return m_cols;
        }

        void set(int r, int c, const T& v)
        {
            m_matrix[r][c] = v;
        }

        const T& get(int r, int c) const
        {
            return m_matrix[r][c];
        }

    private:
        typedef std::vector<T> Row;
        typedef std::vector<Row> Rows;

        Rows m_matrix;
        const int m_rows;
        const int m_cols;
};

#endif // GRID_HPP
