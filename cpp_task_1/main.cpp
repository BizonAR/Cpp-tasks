#include <iostream>
#include <string>
#include "similarwords.h"

using namespace std;

int main()
{
    SimilarWordsDictionary dictionary;

    size_t q;
    cin >> q;

    for (size_t i = 0; i < q; i++)
    {
        string operation;
        cin >> operation;

        if (operation == "CREATE")
        {
            string word1;
            cin >> word1;

            string word2;
            cin >> word2;
            dictionary.Create(word1, word2);
        }
        else if (operation == "QUANTITY")
        {
            string word;
            cin >> word;

            cout << dictionary.Quantity(word) << std::endl;
        }
        else if (operation == "CHECKSIMILAR")
        {
            string word1;
            cin >> word1;

            string word2;
            cin >> word2;

            cout << dictionary.CheckSimilar(word1, word2) << std::endl;
        }
    }
}
