#include "NBC.hpp"
// HASH ?????

NBC::NBC(Stats&& model_stats) : stats(model_stats) { }

Stats& NBC::get_stats() { return stats; }

void NBC::fit(std::vector<std::reference_wrapper<const Feature>>& X, const Feature& y) {
    for (int row = 0; row < y.size(); row++) { // row
        for (auto& tag : y[row]) { // tag
            if (!stats.tags_info.contains(tag)) {
                stats.tags_info[tag].words_total.resize(X.size());
                stats.tags_info[tag].word_count.resize(X.size());
            }
            ++stats.tags_info[tag].class_count;
            for (int feat = 0; feat < X.size(); feat++) { // фича
                stats.tags_info[tag].words_total[feat] += X[feat].get()[row].size();
                for (auto& word : X[feat].get()[row]) { // word
                    ++stats.tags_info[tag].word_count[feat][word];
                }
            }
        }
    }
    stats.dict_size.resize(X.size());
    for (int feat = 0; feat < X.size(); feat++) { // фича
        std::unordered_map<std::string, int> dict;
        for (auto& [_,info] : stats.tags_info) { // tag
            dict.insert(info.word_count[feat].begin(), info.word_count[feat].end());
        }
        stats.dict_size[feat] = dict.size();
    }
    stats.docs_count = y.size();
}

// Multinomial predict
Feature NBC::predict(std::vector<std::reference_wrapper<const Feature>>& X) {
    Feature y(X[0].get().size());
    for (int doc = 0; doc < X[0].get().size(); doc++) {
        for (int feat = 0; feat < X.size(); feat++) {
            double max_prob = -std::numeric_limits<double>::infinity();
            std::string best_tag;
            for (auto& [tag, info] : stats.tags_info) {
                double log_prob = log(info.class_count) - log(stats.docs_count);
                for (auto& word : X[feat].get()[doc]) {
                    log_prob += log(info.word_count[feat][word] + Laplace_smoothing)
                        - log(Laplace_smoothing * stats.dict_size[feat] + info.words_total[feat]);
                }
                if (max_prob < log_prob) {
                    max_prob = log_prob;
                    best_tag = tag;
                }
            }
            bool has = false;
            for (auto& predicted_tag : y[doc])
                has |= (predicted_tag == best_tag);
            if (!has) y[doc].push_back(best_tag);
        }
    }
    return std::move(y);
}
