#include <cstddef> 
#include <iterator> 
#include <iostream> 
#include <cstring>
#include <algorithm>

using namespace std;


double sorting_and_finding_the_median(double a[], size_t i)
{
    double g;
    double n = i + 2;
    for (size_t k = i; k < n; ++k)
        if (a[k] > a[k + 1])
        {
            swap(a[k], a[k + 1]);
        }
    return a[i + 1];
}

double finding_the_arithmetic_mean(double a[], size_t n)
{
    double average = 0;
    size_t quantity = 0;
    for (size_t i = 0; i < n; i += 3)
    {
        if (n - i >= 3)
            average += sorting_and_finding_the_median(a, i);
        if (n - i == 2)
            average += (a[i] + a[i + 1]) / 2;
        if (n - i == 1)
            average += a[i];
        quantity++;
    }
    return average / quantity;
}

// Тест. 

int test_max_common_prefix()
{
    double a[] = { 1, 5, 1, 4, 5, 6, 2, 1, 3, 4, 4, 4, 5, 7 };
    if (finding_the_arithmetic_mean(a, size(a)) != 3.6)
        return 1;
    return 0;
}

int main()
{
    cout << "The output should be 0: ";
    cout << test_max_common_prefix() << ' ';
    return 0;
}
