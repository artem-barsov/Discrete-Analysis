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
struct Stats {
private:
    struct _Freq {
        int classes; // D_c
        std::vector<int> wordsum; // L_c
        std::vector<std::unordered_map<std::string, int>> word; // W_ic
    };
public:
    std::unordered_map<std::string, _Freq> freq; // c_
    std::vector<int> dict_size; // |V|
    int docs_count; // D
};

Dataset get_dataset(std::ifstream&);
void save_stats(std::ofstream&, Stats&);
Stats& load_stats(std::ifstream&);
