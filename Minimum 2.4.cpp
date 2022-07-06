#include <cstddef>  // size_t 
#include <cstring>  // strrchr 
#include <iostream> 
#include <cctype>

using namespace std;

// Особое значение координаты -- "не позиция". 

size_t const NPOS = size_t(-1);

// Решение задачи: поиск наибольшего числа в тексте. 
size_t find_the_largest_number(char const* const* text)
{
    size_t numberstring = -1, quantity = -1, quantitymax = 0;
    // Идём с начала текста. 
    char max[1024] = "0", number[1024] = "0";
    for (size_t line = 0; text[line]; line++)
    {
        for (size_t column = 0; text[line][column]; column++)
            if (isdigit(text[line][column]))
            {
                if ((quantity != -1) || (text[line][column] != '0'))
                {
                    quantity++;
                    number[quantity] = text[line][column];
                    if (quantity > quantitymax)
                    {
                        for (size_t i = 0; i <= quantity; ++i)
                            max[i] = number[i];
                        numberstring = line;
                        quantitymax = quantity;
                    }
                    else if (quantity == quantitymax)
                        for (size_t i = 0; i <= quantity; ++i)
                            if (number[i] > max[i])
                            {
                                for (size_t j = i; j <= quantity; j++)
                                    max[j] = number[j];
                                numberstring = line;
                                quantitymax = quantity;
                            }
                            else if (max[i] > number[i])
                                break;
                }
            }
            else quantity = -1;
    }
    if (numberstring != -1)
        return numberstring;
    return NPOS; // -- символ не найден. 
}


int test_find_the_largest_number()
{
    char const* const text[]
    {
      " 000000000 ",
      " 100000bb ",
      "A l5ne",
      "An1ot978her line",
      "!@#$^!%",
      "       ",
      nullptr
    };

    if (find_the_largest_number(text) != 1)
        return 1;
    if (find_the_largest_number(text + 1) != 0)
        return 2;
    if (find_the_largest_number(text + 2) != 1)
        return 3;
    if (find_the_largest_number(text + 4) != NPOS)
        return 4;

    return 0;
}

int main()

{
    cout << "test find_the_largest_number (should write 0): ";
    cout << test_find_the_largest_number();
    return 0;
}