
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

        Grid(const Grid<T>& other) = default;

        Grid(const IGrid<T>& other): Grid(other.rows(), other.columns())
        {
            for (int i = 0; i < m_rows; i++)
                for (int j = 0; j < m_cols; j++)
                    set(i, j, other.get(i, j));
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

        template<typename TI>
        void set(TI first, TI last)
        {
            for(auto it = first; it != last; ++it)
                set(std::get<0>(*it),       // row
                    std::get<1>(*it),       // column
                    std::get<2>(*it));      // value
        }

        const T& get(int r, int c) const override
        {
            return m_matrix[r][c];
        }

        bool operator==(const Grid<T>& other) const
        {
            return m_rows == other.m_rows &&
                   m_cols == other.m_cols &&
                   m_matrix == other.m_matrix;
        }

        bool operator!=(const Grid<T>& other) const
        {
            return (*this == other) == false;
        }

    private:
        Rows m_matrix;
        const int m_rows;
        const int m_cols;
};

#endif // GRID_HPP
