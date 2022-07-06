#include <vector>
#include <iostream>

using namespace std;

template <typename A>
using Value_t = decay_t<decltype(*begin(declval<A>()))>;

template <typename A>
vector<Value_t<A>> extremum_vector(A const& a)
{
    bool previous_result, result;
    vector<Value_t<A>> b;
    for (size_t i = 1; i < a.size(); i++)
    {
        auto item = a[i], item1 = a[i - 1];
        if (item != item1)
        {
            result = (item < item1);
            if (i == 1)
                previous_result = result;
            if (result != previous_result)
                b.push_back(a[i - 1]);
            previous_result = result;
        }
    }
    return b;
}

template <typename Range>
void print(Range const& r)
{
    char const* delim = "{ ";
    for (auto& item : r)
    {
        cout << delim << item;
        delim = ", ";
    }
    cout << " }\n";
}

int main()
{
    print(extremum_vector(vector<int>{ 1, 3, 10, 20, 5, 6, 4, 0, -1, -1, -1, -2, 4, 40 }));
    return 0;
}