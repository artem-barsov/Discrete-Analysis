#include "NBC.hpp"
// HASH ?????

void NBC::fit(std::vector<std::reference_wrapper<const Feature>>& X, const Feature& y) {
    for (int j = 0; j < y.size(); j++) { // row
        for (auto& tag : y[j]) { // tag
            if (!stats.freq.contains(tag)) {
                stats.freq[tag].wordsum.resize(X.size());
                stats.freq[tag].word.resize(X.size());
            }
            ++stats.freq[tag].classes;
            for (int i = 0; i < X.size(); i++) { // фича
                stats.freq[tag].wordsum[i] += X[i].get()[j].size();
                for (auto& word : X[i].get()[j]) { // word
                    ++stats.freq[tag].word[i][word];
                }
            }
        }
    }
    stats.dict_size.resize(X.size());
    for (int i = 0; i < X.size(); i++) { // фича
        std::unordered_map<std::string, int> dict;
        for (auto& [_,info] : stats.freq) {
            dict.insert(info.word[i].begin(), info.word[i].end());
        }
        stats.dict_size[i] = dict.size();
    }

    stats.docs_count = y.size();
}

Stats& NBC::get_stats() {
    return stats;
}
