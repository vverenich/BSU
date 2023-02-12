#include "dictionary.h"

Dictionary::Dictionary()
{

}

std::map<std::string, int64_t>::iterator Dictionary::begin()
{
    return m_map.begin();
}

std::map<std::string, int64_t>::iterator Dictionary::end()
{
    return m_map.end();
}

void Dictionary::addWord(const std::string &word, int number)
{
    std::string str = word;
    std::transform(str.begin(), str.end(), str.begin(),
        [](unsigned char c){ return std::tolower(c); });

    auto search = m_map.find(str);
    if (search == m_map.end()) {
        m_map.insert(std::pair<std::string, int64_t>(str, number));
        return;
    }

    m_map.at(str) += 1;
}

void Dictionary::removeWord(const std::string& str)
{
    m_map.erase(str);
}

int64_t Dictionary::getWordFrequency(const std::string& str) const
{
    auto search = m_map.find(str);
    if (search == m_map.end()) {
        return -1;
    }

    return m_map.at(str);
}

void Dictionary::setWordFrequency(const std::string &str, int64_t freq)
{
    m_map.at(str) = freq;
}

size_t Dictionary::getDictionarySize() const
{
    return m_map.size();
}

size_t Dictionary::getTotalNumberOfWordsInDictionary()
{
    size_t sum{0};
    for (const auto& i : m_map) {
        sum += i.second;
    }

    return sum;
}

bool Dictionary::isWordInTheDictionary(const std::string& str) const
{
    auto search = m_map.find(str);
    if (search == m_map.end()) {
        return false;
    }

    return true;
}

void Dictionary::clearDictionary()
{
    m_map.clear();
}
