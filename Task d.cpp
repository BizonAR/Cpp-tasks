#include <string>
#include <iostream>
#include <vector>

using namespace std;

size_t getwordcount(string const& text)
{
    size_t words = 0, begin = 0, end = 0, previous_end = 0;
    while (end < text.size())
    {
        begin = text.find_first_not_of(' ', end);
        end = text.find_first_of(' ', begin);
        if (begin != -1)
            words++;
    }
    return words;
}


string adding_spaces_to_string(string& text, size_t width)
{
    size_t begin = 0, end = 0;
    if (!text.empty())
        while (text[text.size() - 1] == ' ')
            text.pop_back();
    while (text.size() != width)
    {
        begin = text.find_first_not_of(' ', end);
        end = text.find_first_of(' ', begin);
        if (end < text.size())
            text.insert(end, " ");
        else begin = 0, end = 0;
    }
    return text;
}

vector <string> justify_text(vector<string>& text, size_t width)
{
    size_t sz = size(text);
    for (size_t line = 0; line != sz; ++line)
    {
        size_t word_counter = 0, words = 0, number_of_letters = text[line].size();
        if (!text[line].empty())
            while (text[line][text[line].size() - 1] == ' ')
                text[line].pop_back();
        words = getwordcount(text[line]);
        if (words > 1)
        {
            if (number_of_letters < width)
                text[line] = adding_spaces_to_string(text[line], width);
            if (number_of_letters > width)
            {
                size_t begin = 0, end = 0, previous_end = 0;
                while (end < text[line].size())
                {
                    begin = text[line].find_first_not_of(' ', end);
                    end = text[line].find_first_of(' ', begin);
                    if (begin != string::npos)
                    {
                        word_counter++;
                        if (word_counter != 1)
                        {
                            if (begin > width)
                            {
                                begin = previous_end;
                                if (line + 1 >= sz)
                                {
                                    text.resize(sz + 1);
                                    sz = text.size();
                                    text[line + 1] = " ";
                                }
                                size_t count = text[line].size() - begin;
                                text[line + 1].insert(0, text[line], begin, count);
                                text[line + 1].insert(count, " ");
                                text[line].erase(begin, count);
                                text[line] = adding_spaces_to_string(text[line], width);
                            }
                            else
                                if (end > width)
                                {
                                    if (line + 1 >= sz)
                                    {
                                        text.resize(sz + 1);
                                        sz = text.size();
                                        text[line + 1] = " ";
                                    }
                                    size_t count = text[line].size() - begin;
                                    text[line + 1].insert(0, text[line], begin, count);
                                    text[line + 1].insert(count, " ");
                                    text[line].erase(begin, count);
                                    text[line] = adding_spaces_to_string(text[line], width);
                                }
                        }
                        previous_end = end;
                    }
                }
            }
        }
    }
    return text;
}

int test_justify_text()
{
    vector<string> text
    {
        "    Преимуществами способа 2 являются: удобство",
        "кодирования и в среднем большее быстродействие",
        "операций, выполняемых над массивом целиком, а",
        "также минимизация операций выделения и",
        "освобождения памяти, минимизация затрат памяти",
        "(нет вспомогательного массива)."
    };

    vector<string> const text1
    {
        "    Преимуществами  способа  2  являются: удобство",
        "кодирования  и  в  среднем  большее быстродействие",
        "операций,  выполняемых  над  массивом  целиком,  а",
        "также    минимизация    операций    выделения    и",
        "освобождения  памяти,  минимизация  затрат  памяти",
        "(нет           вспомогательного          массива)."
    };

    vector <string> const text2
    {
        "    Преимуществами  способа  2",
        "являются: удобство кодирования",
        " и     в    среднем    большее",
        "быстродействие       операций,",
        "выполняемых    над    массивом",
        "целиком,  а  также минимизация",
        "операций      выделения      и",
        "освобождения           памяти,",
        "минимизация затрат памяти (нет",
        " вспомогательного    массива)."
    };

    vector<string> text3
    {
        "    Преимуществами способа 2 являются: удобство",
        "кодирования и в среднем большее быстродействие",
        "операций, выполняемых над массивом целиком, а",
        "также минимизация операций выделения и",
        "освобождения памяти, минимизация затрат памяти",
        "(нет вспомогательного массива)."
    };

    if (justify_text(text, 50) != text1)
        return 1;
    if (justify_text(text3, 30) != text2)
        return 2;
    return 0;
}


int main()
{
    cout << "test justify text (should write 0): ";
    cout << test_justify_text();
    return 0;
}