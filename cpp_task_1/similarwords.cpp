#include "similarwords.h"

void SimilarWordsDictionary::Create(const std::string &word1, const std::string &word2)
{
    std::unordered_set<std::string> synonyms;
    
    if (synonymDictionary.find(word1) != synonymDictionary.end())
        synonymDictionary[word1].insert(word2);
    else
    {
        synonyms.insert(word2);
        synonymDictionary.insert(std::pair <std::string, 
            std::unordered_set<std::string>>(word1, synonyms));
    }

    synonyms.clear();
    
    if (synonymDictionary.find(word2) != synonymDictionary.end())
        synonymDictionary[word2].insert(word1);
    else
    {
        synonyms.insert(word1);
        synonymDictionary.insert(std::pair <std::string, 
            std::unordered_set<std::string>>(word2, synonyms));
    }
}

size_t SimilarWordsDictionary::Quantity(const std::string &word) const
{
    auto it = synonymDictionary.find(word);
    if (it == synonymDictionary.end())
        return 0;
    return it->second.size();
}

std::string SimilarWordsDictionary::CheckSimilar(const std::string &word1, 
    const std::string &word2) const
{
    if (synonymDictionary.find(word1) == synonymDictionary.end() 
        || synonymDictionary.find(word2) == synonymDictionary.end())
        return "NO";
    auto it = synonymDictionary.find(word1);
    if (it->second.find(word2) != it->second.end())
        return "YES";
    return "NO";
}
