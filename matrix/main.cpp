#include <iostream>
#include "Matrix.h"

#include <vector>


using namespace std;


int main()
{
    Matrix<int> m(0);

    for (int pos = 0; pos < 10; ++pos)
    {
        m[pos][pos] = pos;
    }

    for (int pos = 0; pos < 10; ++pos)
    {
        m[pos][9 - pos] = 9 - pos;
    }

    for (int ix = 1; ix < 9; ++ix)
    {
        for (int iy = 1; iy < 9; ++ iy)
        {
            if (m[ix][iy] == 0)
            {
                cout << "* ";
            } else
            {
                cout << m[ix][iy] << " ";
            }
        } cout << endl;
    } cout << endl;

    cout << "size = " << m.size() << endl << endl;

    auto begin = m.begin();
    auto end = m.end();

    while (begin != end)
    {
        size_t row, column;
        int value;

        tie(row, column, value) = *begin;
        cout << "row: " << row << " column: " << column << " value: " << value << endl;

        ++begin;
    }

    cout << endl;

    return 0;
}
