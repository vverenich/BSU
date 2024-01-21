#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <string>
#include <sstream>

/*
Алгоритм Рябко-Элайеса
Пример. Предположим, что все фразы имеют длину k = 2 исходных символов, а исходная нумерация фраз соответствует возрастанию их
значений: [00] → 1, [01] → 2, [10] → 3, [11] → 4. Тогда последовательность
10, 10, 01, 11, 11, ...
кодируется следующим образом. Вместо первой фразы 10 передается ее
номер 3 (равный BElias(3) = 0101), а список фраз переупорядочивается:
10 → 1, 00 → 2, 01 → 3, 11 → 4. Вместо второй фразы 10 передается ее новый номер 1 (равный BElias(1) = 1), а список фраз остается
без изменений. С приходом фразы 01 передается ее номер 3 (равный
BElias(3) = 0101), а список фраз снова переупорядочивается: 01 → 1,
10 → 2, 00 → 3, 11 → 4. Фразе 11 соответствует номер 4 (равный
BElias(4) = 01100) и новый список: 11 → 1, 01 → 2, 10 → 3, 00 → 4.
Следующей фразе 11 соответствует уже номер 1 (равный BElias(1) = 1),
а список остается без изменений. Таким образом, код, построенный по
алгоритму Рябко – Элайеса, имеет следующий вид:
0101, 1, 0101, 01100, 1, ...,
где разделяющие запятые могут быть, конечно, опущены, так как код
BElias(n) является префиксным.

P.S. Для завершения ввода текста нужно нажать Ctrl+Z
*/

/*

int
binary_length(unsigned long long n)
{
    int length = 1;
    while ((1ULL << length) <= n)
        ++length;
    return length;
}

std::string
binary_code(unsigned int n, const int len)
{
    if (0 == len)
        return std::string();

    return binary_code(n / 2, len - 1) + std::to_string(n % 2);
}

std::string
prefix_code(unsigned int n)
{
    int l = binary_length(n);
    return binary_code(0, l - 1) + binary_code(n, l);
}

std::string
elias_code(unsigned int n)
{
    int l = binary_length(n);
    return prefix_code(l) + binary_code(n, l - 1);
}

std::string&
read_aligned_binary_block(std::string& str, std::string& block, int phrase_length)
{
    char next_char;
    size_t i{};
    for (i = 0 ; i < str.size(); ++i) {
        next_char = str.at(i);
        block += binary_code(next_char, sizeof(char));
        if (0 == block.length() % phrase_length)
            break;
    }

    while (0 != block.length() % phrase_length) {
        block += binary_code(0, sizeof(char));
    }

    str.erase(0, i);

    return str;
}

std::string slurp(std::ifstream& in) {
    std::ostringstream sstr;
    sstr << in.rdbuf();
    return sstr.str();
}

double getAverageLengthOfCodeWord(const std::string& fileName, const size_t phrase_length)
{
    std::list<std::string> phrase_deck;
    int phrase_number = 1 << phrase_length;
    for (int i = 0; i < phrase_number; ++i)
        phrase_deck.push_back(binary_code(i, phrase_length));

    std::string block, phrase;
    int total_code_length = 0, total_code_number = 0;
    std::ifstream fin{fileName};
    std::string text = slurp(fin);
    read_aligned_binary_block(text, block, phrase_length);
    //while (read_aligned_binary_block(text, block, phrase_length).size) {
        for (size_t i = 0; i < block.length(); i += phrase_length) {
            int pos_num = 0;
            for (auto pos = phrase_deck.begin(); pos != phrase_deck.end(); ++pos) {
                ++pos_num;
                if (0 == block.compare(i, phrase_length, *pos)) {
                    phrase = std::move(*pos);
                    phrase_deck.erase(pos);
                    phrase_deck.push_front(std::move(phrase));
                    ++total_code_number;
                    total_code_length += elias_code(pos_num).length();
                    break;
                }
            }
          }
        block.clear();
    //}

    std::cout << "The average length of the code word is " <<
        (double)(total_code_length) / total_code_number << '\n';

    return (double)(total_code_length) / total_code_number;

}

void doLab5()
{
    for (size_t phrase_length{2}; phrase_length <= 15; ++phrase_length) {
        std::cout << "k = " << phrase_length << "\n";
        getAverageLengthOfCodeWord("text.txt", phrase_length);
    }
}

int
main()
{
    doLab5();
}

*/

#include <iostream>
#include <string>
#include <cmath>

/*
* Лемпель-Зива
Суть алгоритма Лемпеля – Зива заключается в том, что исходная последовательность u = {u1, u2,...,un} разделяется на фразы,
которые до сих пор не встречались. Например, если дана последовательность
1011010100010 ...,
то после разделения мы получим
1   2   3   4   5       6   7
1,  0,  11, 01, 010,    00, 10, ...,
где каждая новая фраза имеет свой однозначный порядковый номер.
Такое разделение является уникальным и называется разделением Лемпеля – Зива.
В соответствии с этой конструкцией каждая последующая фраза состоит из некоторой (уже встречавшейся) предыдущей фразы как префикса и
еще одного отличительного конечного бита. Поэтому закодировать фразы можно, указывая номер префикса
и конечный бит, а восстановить — добавляя конечный бит к известному префиксу.
1       0       11      01      010     00      10 ... фразы после разделения
↓       ↓       ↓       ↓       ↓       ↓       ↓
(0,1)   (0,0)   (1,1)   (2,1)   (4,0)   (2,0)   (1,0) ... кодовые слова
↓       ↓       ↓       ↓       ↓       ↓       ↓
1       0       11      01      010     00      10 ... фразы после реконструкции

P.S. Для завершения ввода текста нужно нажать Ctrl+Z
*/


int
binary_length(unsigned long long n)
{
    int length = 1;
    while ((1ULL << length) <= n)
        ++length;
    return length;
}

std::string
binary_code(unsigned int n, const int len)
{
    if (0 == len)
        return std::string();

    return binary_code(n / 2, len - 1) + std::to_string(n % 2);
}

std::string
prefix_code(unsigned int n)
{
    int l = binary_length(n);
    return binary_code(0, l - 1) + binary_code(n, l);
}

std::string
elias_code(unsigned int n)
{
    int l = binary_length(n);
    return prefix_code(l) + binary_code(n, l - 1);
}

struct trie_node
{
    int number;
    trie_node* children[2];
    trie_node() : number(0), children{ nullptr, nullptr } {}
};

void
trie_insert_child(trie_node* node, int bit, int number)
{
    node->children[bit] = new trie_node();
    node->children[bit]->number = number;
}

void
trie_destroy(trie_node* root_node)
{
    if (!root_node)
        return;
    trie_destroy(root_node->children[0]);
    trie_destroy(root_node->children[1]);
    delete root_node;
}

struct lz_state {
    int curr_word;
    int total_bits;
    trie_node* root_node, * curr_node;
    int lz_length;
    lz_state() : curr_word(0), total_bits(0), root_node(new trie_node()),
        curr_node(root_node), lz_length(0) {}
    ~lz_state() { trie_destroy(root_node); }
};

void
lz_state_change_bit(lz_state& state, int bit)
{
    ++state.total_bits;
    trie_node* child = state.curr_node->children[bit];
    if (child) {
        state.curr_node = child;
        return;
    }

    state.lz_length += elias_code(state.curr_node->number).length() + 1;
    ++state.curr_word;
    trie_insert_child(state.curr_node, bit, state.curr_word);
    state.curr_node = state.root_node;
}

void
lz_state_change(lz_state& state, int c)
{
    for (int i = 8 * sizeof(char) - 1; i >= 0; --i)
        lz_state_change_bit(state, ((1 << i) & c) >> i);
}

void
lz_finish(lz_state& state)
{
    while (state.root_node != state.curr_node)
        lz_state_change_bit(state, 0);
}

double
lz_upper_bound(int n)
{
    return n / std::log2(n);
}

int
main()
{
    char c;
    lz_state state;
    std::ifstream fin("text.txt");
    while (fin.get(c)) {
        lz_state_change(state, c);
    }
    lz_finish(state);

    std::cout << "The number of source bits is " << state.total_bits << '\n';
    std::cout << "The number of bits after LZ encoding is " <<
        state.lz_length << '\n';
    std::cout << "The number of unique words in the text is " <<
        state.curr_word << '\n';
    std::cout << "The upper bound in the LZ inequality is " <<
        lz_upper_bound(state.total_bits) << '\n';
}


