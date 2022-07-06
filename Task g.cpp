#include <iostream>
#include <string_view>

using namespace std;

// Извлечение из строки значение
string_view string_conversion(string_view in)
{
    auto equal = in.find('='); // Находим позицию равно
    auto pos = in.find_first_not_of(" \t", equal + 1); // Находим первый непробельный символ начиная с равно
    equal = in.find_last_not_of(" \t") + 1; // Находим последний непробельный символ в строке
    in = in.substr(pos, equal - pos); // Выделяем значение
    return in;
}

// Тест функции string_conversion
bool test_string_conversion()
{
    if (string_conversion("abc = def ") != "def")
        return 1;
    if (string_conversion("   \t\nNever = \t  \t    theless...") != "theless...")
        return 2;
    if (string_conversion("Adversaries clash in = \t \t      what’s called the “mirror dimension")
        == "   what’s called the “mirror dimension")
        return 3;
    return 0;
}

int main()
{
    cout << test_string_conversion();
    return 0;
}
