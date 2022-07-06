#include <random>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

template <typename Number>
class Uniform
{
    mt19937 rng;
    uniform_real_distribution<Number> vg;

public:
    explicit Uniform(size_t seed = 5512943)
        : rng(seed), vg(Number(-1), Number(+1)) {}

    Number operator()() { return vg(rng); }
};

template <typename RanIT>
void n_dimensional_ball_hit(RanIT from, RanIT to)
{
    Uniform <double> rng;
    auto next_number = [&]() { return rng(); };
    while (from != to)
    {
        for_each(from, to, [&](vector <double>& coordinates)
            {
                generate(coordinates.begin(), coordinates.end(), next_number);
            });
        from = remove_if(from, to, [](vector<double>& coordinates)
            {
                return  (inner_product(coordinates.begin(), coordinates.end(),
                    coordinates.begin(), 0.0)) > 1;
            });
    }
}

bool test_n_dimensional_ball_hit()
{
    vector<vector<double>> stream_of_vectors(5, vector <double>(3));
    n_dimensional_ball_hit(begin(stream_of_vectors), end(stream_of_vectors));
    vector<vector <double>> test
    {
        {-0.830508, -0.139675, -0.407188},
        {-0.443585,  0.225562,  0.626196},
        { 0.442063, -0.715626, -0.174186},
        { 0.254097, -0.137857, -0.765634},
        {-0.043123,  0.598222, -0.361166}
    };
    return !equal(begin(stream_of_vectors), end(stream_of_vectors), begin(test), end(test),
        [](vector <double>& x, vector <double>& y)
        {
            double EPS = 1e-5;
            if ((x.size() == y.size()))
                for (size_t i = 0; i < x.size(); ++i)
                {
                    if (fabs(x[i] - y[i]) > EPS)
                        return false;
                }
            else return false;
            return true;
        });
}

int main()
{
    cout << test_n_dimensional_ball_hit();
    return 0;
}