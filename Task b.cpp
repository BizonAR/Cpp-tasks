#include <iostream>
#include <iterator>
#include <vector>
#include <cmath>

using namespace std;

template <typename M>
bool is_matrix(M const& m)
{
    if (empty(m))
        return true;
    auto const cols = size(*begin(m));
    for (auto& row : m)
        if (size(row) != cols)
            return false;

    return true;
}

template <typename M>
bool is_switch_matrix(M const& m)
{
    if (!is_matrix(m))
        return false;
    auto const cols = size(*begin(m));
    for (size_t i = 1; i < cols; i++)
        for (size_t j = 1; j < cols; j++)
            if ((i != j) && (m[i][j] != 0))
                return false;
    return true;
}

int test_is_switch_matrix()
{
    // Тест для обычного массива.
    double m1[5][5]
    {
       1, 2,  3,  4,  5,
       7, 8,  0,  0,  0,
       9, 0,  1,  0,  0,
       3, 0,  0,  2,  0,
       5,  0,  0, 0,  3.
    };

    if (!is_switch_matrix(m1))
        return 1;
    m1[2][1] = 3;
    if (is_switch_matrix(m1))
        return 2;

    // Тест для вектора векторов.
    std::vector<std::vector<double>> m2
    {
      {  0., 0.1,  1.  },
      { 1.1, 0.9, 0.9  },
      {  0.,  1., 1.1  }
    };

    if (is_switch_matrix(m2))
        return 3;
    m2[1][2] = 0;
    m2[2][1] = 0;
    if (!is_switch_matrix(m2))
        return 4;

    return 0;
}

int main()
{
    std::cout << test_is_switch_matrix();
    return 0;
}