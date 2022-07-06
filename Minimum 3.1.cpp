#include <iostream>
#include <cmath>
#include <cassert>

using namespace std;

int const INFINITE_ROOTS = -1;

using NT = float;

NT const
HALF_PI = 1.5707963267948966, // половина пи, 

PI = 3.1415926535897932, // число пи, 

DOUBLE_PI = 6.2831853071795865, // два пи, 

TOLERANCE = 1e-10; // граница между "нулём" и "ненулём".

// Проверка значения на близость нулю.    
bool is_almost_zero(NT x, NT tollerance = TOLERANCE)
{
    return fabs(x) <= tollerance;
}

// Левая часть уравнения. 
NT f(NT a, NT b, NT c, NT x)
{
    NT j = tan(b * b * x * x - a * a * a * a);
    NT l = c * c * c;
    NT zzz = exp(a * tan(b * b * x * x - a * a * a * a));
    return exp(a * tan(b * b * x * x - a * a * a * a)) - c * c * c;
}

int solve_f(NT a, NT b, NT c, NT& root)
{
    if (c <= 0 || b == 0)
        return 0;
    if (a == 0)
        return is_almost_zero(f(a, b, c, 1)) ?
        INFINITE_ROOTS : 0;
    NT const
        expr_part = atan(log(c * c * c) / a),
        n = 1 + ceil(-expr_part / PI - a * a * a * a / PI),
        sqr = (expr_part + PI * n + a * a * a * a) / (b * b);
    assert(sqr > 0);
    root = sqrt(sqr);
    return 1;
}

int main()
{
    cout << "Solving f(a, b, c, x) = 0," << " enter a, b, c:\n";
    cout.precision(16);
    for (NT a, b, c, x; cin >> a >> b >> c;)
    {

        switch (solve_f(a, b, c, x))
        {
        case 0:
            cout << "no roots\n";
            break;
        case INFINITE_ROOTS:
            cout << "any number is a root\n";
            break;
        case 1: // один корень, записан в x 
            cout << "x == " << x << ", error is " << f(a, b, c, x) << endl;
            break;
        default:
            assert(!"impossible roots quantity");
            cout << "unknown error\n";
            return 1; // ошибка. 
        }
    }
    return 0;
}
