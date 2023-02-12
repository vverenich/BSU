#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <map>
#include <algorithm>

class Dictionary {
  public:
    Dictionary();

    std::map<std::string, int64_t>::iterator begin();
    std::map<std::string, int64_t>::iterator end();
    void addWord(const std::string& word, int number = 1);
    void removeWord(const std::string& str);
    int64_t getWordFrequency(const std::string& str) const;
    void setWordFrequency(const std::string& str, int64_t freq);
    size_t getDictionarySize() const;
    size_t getTotalNumberOfWordsInDictionary();
    bool isWordInTheDictionary(const std::string& str) const;
    void clearDictionary();

  private:
    std::map<std::string, int64_t> m_map{};
};

#endif // DICTIONARY_H
