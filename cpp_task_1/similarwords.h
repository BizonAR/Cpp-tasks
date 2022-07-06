#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>

/*!
 * \brief Словарь похожих слов
 */
class SimilarWordsDictionary
{
public:
    /*!
     * \brief Добавить в словарь пару похожих слов (word1, word2)
     * \param word1, word2 - похожие слова
     * \note Гарантируется, что word1 != word2
     */
    void Create(const std::string& word1, const std::string& word2);

    /*!
     * \brief Узнать количество похожих на word слов
     * \param word слово
     * \return Возвращает количество похожих на word слов
     */
    size_t Quantity(const std::string& word) const;

    /*!
     * \brief Проверить, являются ли слова word1 и word2 похожими.
     * \param word1, word2 - потенциальные похожие слова
     * Слова word1 и word2 считаются похожими, если среди запросов CREATE
     * был хотя бы один запрос 'CREATE word1 word2' или 'CREATE word2 word1'.
          * \return Возвращает строку "YES", если word1 и word2 являются похожими словами, и "NO" в противном случае.
     */
    std::string CheckSimilar(const std::string& word1, const std::string& word2) const;
    
    

private:
    // TODO организовать структуру данных, которая позволит эффективно взаимодействовать со словарем синонимов
    std::unordered_map <std::string, std::unordered_set<std::string>> synonymDictionary;
};
