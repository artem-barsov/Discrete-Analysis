#include "NBC.hpp"

NBC::NBC(const Stats&& model_stats) : stats(model_stats) { }

const Stats& NBC::get_stats() const { return stats; }

void NBC::fit(const Feature& X, const Feature& y) {
    for (int row = 0; row < y.size(); row++) {
        for (const auto& tag : y[row]) {
            ++stats.tags_info[tag].class_count;
            stats.tags_info[tag].words_total += X[row].size();
            for (const auto& word : X[row])
                ++stats.tags_info[tag].word_count[word];
        }
    }
    std::unordered_map<std::string, int> dict;
    for (const auto& [_,info] : stats.tags_info)
        dict.insert(info.word_count.begin(), info.word_count.end());
    stats.dict_size = dict.size();
    stats.docs_count = y.size();
}

template <size_t SZ>
const Feature NBC::predict(const std::array<std::reference_wrapper<const Feature>, SZ>& X) const {
    Feature y(X[0].get().size());
    for (const Feature& feat : X) {
        for (int doc = 0; doc < feat.size(); doc++) {
            std::set<std::pair<double, std::string>, std::greater<std::pair<double, std::string> > > bests;
            for (const auto& [tag, info] : stats.tags_info) {
                double log_prob = log(info.class_count) - log(stats.docs_count);
                for (const auto& word : feat[doc]) {
                    auto it = info.word_count.find(word);
                    int Wic = (it != info.word_count.end() ? it->second : 0);
                    log_prob += log(Wic + Laplace_smoothing) - log(Laplace_smoothing * stats.dict_size + info.words_total);
                }
                bests.insert({log_prob, tag});
                if (bests.size() > maxClasses_per_feat)
                    bests.erase(std::prev(bests.end()));
            }
            for (const auto& [_,best_tag] : bests) {
                bool has = false;
                for (const auto& predicted_tag : y[doc])
                    has |= (predicted_tag == best_tag);
                if (!has) y[doc].push_back(best_tag);
            }
        }
    }
    return std::move(y);
}

template const Feature NBC::predict<2>(const std::array<std::reference_wrapper<const Feature>, 2>& X) const;
