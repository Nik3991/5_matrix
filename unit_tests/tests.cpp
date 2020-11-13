#define BOOST_TEST_MODULE matrix_test
#include <boost/test/included/unit_test.hpp>

#include <string>
using namespace std;

#include "../matrix/Matrix.h"

BOOST_AUTO_TEST_SUITE(matrix_test_suite)

BOOST_AUTO_TEST_CASE(matrix_test)
{
    const int default_value = 0;
    Matrix<int> m(default_value);

    for (int pos = 0; pos < 10; ++pos)
    {
        m[pos][pos] = pos;
    }

    for (int pos = 0; pos < 10; ++pos)
    {
        m[pos][9 - pos] = 9 - pos;
    }

    BOOST_CHECK(m.size() == 18);

    m[9][9] = default_value;

    BOOST_CHECK(m.size() == 17);
}

BOOST_AUTO_TEST_SUITE_END()
