
#ifndef GRID_HPP
#define GRID_HPP

#include <initializer_list>

#include "igrid.hpp"


template<typename T>
class Grid: public IGrid<T>
{
    public:
        typedef std::vector<T> Row;
        typedef std::vector<Row> Rows;

        Grid(int rows, int cols)
            : m_rows(rows)
            , m_cols(cols)
        {
            m_matrix.reserve(rows);

            for(int i = 0; i < rows; i++)            // fill rows
                m_matrix.push_back(Row(cols, {}));   // with Row filled with 'cols` items
        }

        Grid(std::initializer_list<Row> l)
            : m_matrix(l)
            , m_rows(m_matrix.size())
            , m_cols(m_matrix.front().size())
        {

        }

        int rows() const override
        {
            return m_rows;
        }

        int columns() const override
        {
            return m_cols;
        }

        void set(int r, int c, const T& v) override
        {
            m_matrix[r][c] = v;
        }

        const T& get(int r, int c) const override
        {
            return m_matrix[r][c];
        }

    private:
        Rows m_matrix;
        const int m_rows;
        const int m_cols;
};

#endif // GRID_HPP
