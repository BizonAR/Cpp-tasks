#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>

using namespace std;

unordered_map<string, string> create_macro_dictionary(istream& macros, // Заполняем словарь макро-подстановок
	 unordered_map<string, string> macro_dictionary)
{
	 for (string macros_line; getline(macros, macros_line);) // Пройти по всему файлу с макроподстановками
	 {
		  auto pos = macros_line.find_first_of('='); // Находим позицию = в строке с макроподстановкой
		  macro_dictionary.emplace(macros_line.substr(0, pos - 1), macros_line.substr(pos + 2, macros_line.size()));
	 }
	 return macro_dictionary;
}

void macro_substitution(ifstream& in, ofstream& out,
	 unordered_map<string, string>& macro_dictionary)
{
	 for (string line; getline(in, line);) // Пройти по всему исходному файлу
	 {
		  auto pos = line.find_first_of('$'); // Находим первую позицию $ в строке исходного файла
		  auto end = line.find_first_of('$', pos + 1); // Находим следующую позицию $ в строке исходного файла
		  while (!(pos == string::npos || end == string::npos)) // Проверяем, что такие символы есть
		  {
				string word = line.substr(pos + 1, end - (pos + 1)); // Выделяем слово, которое заменяем
				auto it = macro_dictionary.find(word); // Находим этот макрос в словаре
				if (it != macro_dictionary.end())
					 line.replace(pos, end + 1 - pos, macro_dictionary.at(word)); // Если этот макрос есть в словаре делаем подстановку
				pos = line.find_first_of('$', end + 1); // Находим следующий символ $ в строке, если он есть после end
				end = line.find_first_of('$', pos + 1); // Находим следующий символ $ в строке, если он есть после pos
		  }
		  out << line << '\n'; // Записываем строку в новый файл
	 }
}

bool macro_substitution(char const* filename, unordered_map<string, string>& macro_dictionary)
{
	 ifstream in(filename); // Открыть исходный файл
	 if (!in.is_open()) // Если не открылся вернуть ошибку
		  return false;
	 string temp_file = string(filename) + ".temp"; // Создаём временный файл с таким же названием
	 ofstream out(temp_file); // Открываем временный файл
	 if (!out.is_open()) // Если не открылся вернуть ошибку
		  return false;
	 macro_substitution(in, out, macro_dictionary); // Создаём файл с макроподстановками
	 in.close(); // Закрываем исходный файл
	 out.close(); // Закрываем временный файл
	 remove(filename); // Удаляем исходный файл
	 return !rename(temp_file.c_str(), filename); // Переименовываем новый файл в исходный
}

int main(int argc, char* argv[])
{
	 setlocale(LC_ALL, "Russian");
	 ifstream macros("D:\\Users\\mikaa\\source\\repos\\ConsoleApplication6\\macros.txt"); // Открываем исходный файл с макроподстановками
	 if (!macros.is_open()) // Если не открылся файл с макроподстановками - ошибка
		  throw exception("Failed to open macros_file");
	 unordered_map<string, string> macro_dictionary; // Словарь макро-подстановок
	 macro_dictionary = create_macro_dictionary(macros, macro_dictionary);
	 int failed_files = 0; // С каким файлом возникла ошибка
	 for (int i = 1; i < argc; ++i)
		  if (!macro_substitution(argv[i], macro_dictionary))
		  {
				++failed_files;
		  }
	 macros.close(); // Закрываем файл с макроподстановками
	 return failed_files; // 0 == ни одной ошибки == успех
	 return 0;
}