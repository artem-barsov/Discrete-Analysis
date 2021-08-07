#pragma once
#include <unordered_map>
#include <iterator>
#include <fstream>
#include <sstream>
#include <vector>

using Feature = std::vector<std::vector<std::string>>;
struct Dataset { Feature title, text, tags; };
struct Stats {
    struct _Info {
        // D_c, количество документов в обучающей выборке принадлежащих классу `c`:
        int class_count;
        // L_c, суммарное количество слов в документах класса `c` в обучающей выборке:
        int words_total;
        // W_ic, сколько раз `i`-ое слово встречалось в документах класса `c` в обучающей выборке:
        std::unordered_map<std::string, int> word_count;
    };
private:
public:
    // c_, информация о каждом классе:
    std::unordered_map<std::string, _Info> tags_info;
    // |V|, количество уникальных слов во всех документах обучающей выборки:
    int dict_size;
    // D, общее количество документов в обучающей выборке:
    int docs_count;
};

const Dataset get_trainset(std::ifstream&);
const Dataset get_testset(std::ifstream&);
void save_stats(std::ofstream&, const Stats&);
const Stats load_stats(std::ifstream&);
void save_feature(std::ofstream&, const Feature&);
