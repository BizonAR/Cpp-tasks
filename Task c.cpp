#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

size_t const NPOS = string::npos;

struct Text_position
{
	 size_t line = NPOS, column = NPOS;
};

inline bool operator==(Text_position const& a, Text_position const& b)
{
	 return a.line == b.line && a.column == b.column;
}

inline bool operator!=(Text_position const& a, Text_position const& b)
{
	 return !(a == b);
}

Text_position find_the_largest_number(vector<string> const& text, size_t test_line)
{
	 size_t r_line = -1, r_column;
	 string max = "0";
	 size_t count = 0, max_count;
	 size_t begin = 0, end = 0;
	 auto sz = text.size();
	 for (size_t line = test_line; line < sz; ++line)
	 {
		  begin = 0;
		  for (size_t column = 0; column < text[line].size(); ++column)
		  {
				begin = text[line].find_first_of("123456789", column);
				if (begin != -1)
				{
					 end = text[line].find_first_not_of("0123456789", begin);
					 size_t count = end - begin;
					 string const* p_text = &text[line];
					 string const* p_max = &max;
					 max_count = max.size();
					 if (count > max_count)
					 {
						  r_line = line - test_line;
						  r_column = begin;
						  max.resize(count);
						  for (size_t max_number = 0, column1 = begin; max_number < count; ++max_number, ++column1)
								max[max_number] = text[line][column1];
					 }
					 else if (count == max_count)
					 {
						  for (size_t max_number = 0, column1 = begin; max_number < count; ++max_number, ++column1)
						  {
								if (text[line][column1] < max[max_number])
									 break;
								else if (text[line][column1] > max[max_number])
								{
									 max[max_number] = text[line][column1];
									 r_line = line - test_line;
									 r_column = begin;
								}
						  }
					 }
				}
		  }
	 }
	 if (r_line != -1)
		  return { r_line, r_column };
	 return {};
}

int test_find_the_largest_number()
{
	 vector<string> const text
	 {
		 " 000000000 ",
		 " 100000bb ",
		 "A l5ne",
		 "An1ot978her line",
		 "!@#$^!%",
		 "       ",
	 };

	 if (find_the_largest_number(text, 0) != Text_position{ 1, 1 })
		  return 1;
	 if (find_the_largest_number(text, 1) != Text_position{ 0, 1 })
		  return 2;
	 if (find_the_largest_number(text, 2) != Text_position{ 1, 5 })
		  return 3;
	 if (find_the_largest_number(text, 4) != Text_position{})
		  return 4;

	 return 0;
}

int main()
{
	 cout << "test find_the_largest_number (should write 0): ";
	 cout << test_find_the_largest_number();
	 return 0;
}
