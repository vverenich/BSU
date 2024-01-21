#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <queue>
#include <iomanip>
#include <cmath>

struct MessageNode
{
    explicit MessageNode(const size_t num) :
        m_Num{num}
    {}

    size_t      m_Num;
    std::string m_Word{};
};

struct HuffmanNode
{
    explicit HuffmanNode(const double probability) :
        m_Probability{probability}
    {}

    double                 m_Probability;
    std::list<MessageNode> m_ListMessages{};
};

struct HuffmanNodeCmp {
    bool operator() (const HuffmanNode& a, const HuffmanNode& b)
    {
        return a.m_Probability >= b.m_Probability;
    }
};

HuffmanNode mergeHuffmanNodes(HuffmanNode &a, HuffmanNode &b)
{
    HuffmanNode result { a.m_Probability + b.m_Probability };
    for (auto &msg : a.m_ListMessages)
        msg.m_Word = '0' + msg.m_Word;
    for (auto &msg : b.m_ListMessages)
        msg.m_Word = '1' + msg.m_Word;
    result.m_ListMessages = move(a.m_ListMessages);
    result.m_ListMessages.splice(result.m_ListMessages.begin(), b.m_ListMessages);

    for (const auto& msg : result.m_ListMessages) {
        std::cout << msg.m_Word << " " << msg.m_Num << "\n";
    }

    return result;
}

std::vector<std::string> huffman(const std::vector<double> &probabilities)
{
    std::priority_queue<HuffmanNode, std::vector<HuffmanNode>,
         HuffmanNodeCmp> nodeQueue;
    for (size_t i = 0; i < probabilities.size(); ++i) {
        MessageNode message {i};
        HuffmanNode leaf { probabilities[i] };
        leaf.m_ListMessages.push_back(std::move(message));
        nodeQueue.push(std::move(leaf));
    }

    while (nodeQueue.size() > 1) {
        HuffmanNode first = nodeQueue.top();
        nodeQueue.pop();
        HuffmanNode second = nodeQueue.top();
        nodeQueue.pop();
        std::cout << first.m_Probability << " " << second.m_Probability;
        std::cout << "\n";
        nodeQueue.push(mergeHuffmanNodes(first, second));
        std::cout << "\n";
        std::cout << "\n";
        std::cout << "\n";
    }

    HuffmanNode root = nodeQueue.top();
    std::vector<std::string> result(probabilities.size());
    for (auto &msg : root.m_ListMessages)
        result[msg.m_Num] = move(msg.m_Word);

    return result;
}

int getNumberOfDigits(int num)
{
    int result = 0;
    do {
        ++result;
        num /= 10;
    } while (num > 0);

    return result;
}

double getAverageWordLength(const std::vector<std::string> &huffmanWords,
                            const std::vector<double>      &probabilities)
{
    double result = 0;
    for (size_t i = 0; i < huffmanWords.size(); ++i)
        result += huffmanWords[i].length() * probabilities[i];

    return result;
}

double getSourceEntropy(const std::vector<double> &probabilities)
{
    double result = 0;
    for (size_t i = 0; i < probabilities.size(); ++i)
        result += -probabilities[i] * std::log2(probabilities[i]);

    return result;
}

int main()
{
    std::vector<double> probabilities{};
    double              currentProbability{};
    double              sumOfProbabilities{};

    std::cout << "Enter probabilities (sum must be 1.0, enter ctrl+D+Enter to end) :\n";
    while (std::cin >> currentProbability) {
        probabilities.push_back(currentProbability);
        sumOfProbabilities += currentProbability;
        if (sumOfProbabilities > 1.0) {
            std::cerr << "sum of entered probabilities is " << sumOfProbabilities << " > 1\n";
            return 1;
        }
    }

    if (1.0 != sumOfProbabilities) {
        std::cerr << "the probabilities don't sum up to 1\n";
        return 1;
    }

    auto words = huffman(probabilities);

    std::cout << "The Huffman codes for the messages are as follows:\n";
    int places = getNumberOfDigits(probabilities.size());
    for (size_t i = 0; i < words.size(); ++i)
        std::cout << std::setw(places) << i << " | " << words[i] << '\n';

    std::cout << "The average length of the code is "
        << getAverageWordLength(words, probabilities) << '\n';
    std::cout << "The entropy of the source is "
        << getSourceEntropy(probabilities) << '\n';
}
