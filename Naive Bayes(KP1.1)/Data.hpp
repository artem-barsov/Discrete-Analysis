#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <unordered_map>

using Feature = std::vector<std::vector<std::string>>;
struct Dataset {
    Feature title, text, tags;
};
template <typename T> using Param_per_feat = std::vector<T>;
struct Stats {
private:
    struct _Info {
        // D_c, количество документов в обучающей выборке принадлежащих классу `c`:
        int class_count;
        // L_c, суммарное количество слов в документах класса `c` в обучающей выборке:
        Param_per_feat<int> words_total;
        // W_ic, сколько раз `i`-ое слово встречалось в документах класса `c` в обучающей выборке:
        Param_per_feat<std::unordered_map<std::string, int>> word_count;
    };
public:
    // c_, информация о каждом классе:
    std::unordered_map<std::string, _Info> tags_info;
    // |V|, количество уникальных слов во всех документах обучающей выборки:
    Param_per_feat<int> dict_size;
    // D, общее количество документов в обучающей выборке:
    int docs_count;
};

Dataset get_trainset(std::ifstream&);
Dataset get_testset(std::ifstream&);
void save_stats(std::ofstream&, Stats&);
Stats load_stats(std::ifstream&);
void save_feature(std::ofstream&, Feature&);
