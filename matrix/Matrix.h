#ifndef MATRIX_H
#define MATRIX_H

#include <map>
#include <iostream>
#include <tuple>

using namespace std;

// --------------------------------------------------------



template <typename T>
class TypeWrapper
{
public:
    TypeWrapper(const T& _def_value, map<size_t, map<size_t, T>>& _ref_map, size_t _row, size_t _column, size_t& _size) :
        def_value (_def_value),
        ref_map(_ref_map),
        m_row (_row),
        m_column (_column),
        ref_size(_size)
    {}

    T operator = (T _value)
    {
        if (_value == def_value)
        {
            if (ref_map.find(m_row) != ref_map.end())
            {
                map<size_t, T>& row = ref_map.at(m_row);
                if (row.find(m_column) != row.end())
                {
                    row.erase(m_column);
                    --ref_size;
                    if (row.empty())
                    {
                        ref_map.erase(m_row);
                    }
                }
            }
        } else
        {
            ref_map[m_row][m_column] = _value;
            ++ref_size;
        }
    }

    operator T ()
    {
        T result = def_value;
        if (ref_map.find(m_row) != ref_map.end())
        {
            map<size_t, T>& row = ref_map.at(m_row);
            if (row.find(m_column) != row.end())
            {
                return row.at(m_column);
            }
        }

        return result;
    }

private:
    map<size_t, map<size_t, T>>& ref_map;
    size_t m_row, m_column;
    size_t& ref_size;
    T def_value;
};




// --------------------------------------------------------




template <typename T>
class RowWrapper
{
public:
    RowWrapper (const T& _def_value, map<size_t, map<size_t, T>>& _ref_map, size_t _row, size_t& _size) :
        ref_map (_ref_map),
        m_row (_row),
        ref_size(_size),
        def_value(_def_value)
    {}

    TypeWrapper<T> operator[](size_t _column)
    {
        TypeWrapper<T> type_wrapper (def_value, ref_map, m_row, _column, ref_size);
        return type_wrapper;
    }

private:
    const T& def_value;
    size_t& ref_size;
    size_t m_row;
    map<size_t, map<size_t, T>>& ref_map;
};




// --------------------------------------------------------




template <typename T>
class Iterator
{
public:
    Iterator(map<size_t, map<size_t, T>>& _ref_data,
             typename map<size_t, map<size_t, T>>::iterator _iterator) :
        ref_data(_ref_data),
        m_row_iterator(_iterator)
    {
        if (m_row_iterator != ref_data.end())
        {
            m_column_iterator = m_row_iterator->second.begin();
        }
    }

    void operator++()
    {
        if (m_row_iterator != ref_data.end())
        {
            if (++m_column_iterator == m_row_iterator->second.end())
            {
                m_row_iterator++;
                if (m_row_iterator != ref_data.end())
                {
                    m_column_iterator = m_row_iterator->second.begin();
                }
                else
                {
                    m_column_iterator = typename map<size_t, T>::iterator();
                }
            }
        }
    }

    tuple<size_t, size_t, T> operator*()
    {
        size_t row = m_row_iterator->first;
        size_t column = m_column_iterator->first;

        return make_tuple(row, column, m_column_iterator->second);
    }

    bool operator==(const Iterator& _iterator) const
    {
        return (m_row_iterator    == _iterator.m_row_iterator) &&
               (m_column_iterator == _iterator.m_column_iterator);
    }

    bool operator!=(const Iterator& _iterator) const
    {
        return !(*this == _iterator);
    }

private:
    size_t m_row, m_column;
    typename map<size_t, map<size_t, T>>::iterator m_row_iterator;
    typename map<size_t, T>::iterator m_column_iterator;
    map<size_t, map<size_t, T>>& ref_data;
};




// --------------------------------------------------------




template <typename T>
class Matrix
{
public:
    Matrix(const T& _def_value) :
        def_value(_def_value)
    {}

    Iterator<T> begin()
    {
        Iterator<T> begin(m_data, m_data.begin());
        return begin;
    }

    Iterator<T> end()
    {
        Iterator<T> end(m_data, m_data.end());
        return end;
    }

    RowWrapper<T> operator[](size_t _row)
    {
        RowWrapper<T> row_wrapper (def_value, m_data, _row, m_size);
        return row_wrapper;
    }

    size_t size()
    {
        return m_size;
    }

private:
    const T def_value;
    size_t m_size = 0;
    map<size_t, map<size_t, T>> m_data;
};

#endif // MATRIX_H
