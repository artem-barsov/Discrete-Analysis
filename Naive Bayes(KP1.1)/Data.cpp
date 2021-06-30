#include "Data.hpp"

Dataset get_dataset(std::ifstream& fin) {
    Dataset ds;
    int n;
    while (fin >> n) {
        fin.get();
        std::string line, word;
        std::getline(fin, line);
        std::stringstream ss(line);
        ds.tags.push_back(std::vector<std::string>());
        while (std::getline(ss, word, ','))
            ds.tags.back().push_back(word);
        std::getline(fin, line);
        ss = std::stringstream(line);
        ds.title.emplace_back(
            std::istream_iterator<std::string>(ss),
            std::istream_iterator<std::string>()
        );
        ss = std::stringstream();
        for (int i = 0; i < n; i++) {
            std::getline(fin, line);
            ss << line << ' ';
        }
        ds.text.emplace_back(
            std::istream_iterator<std::string>(ss),
            std::istream_iterator<std::string>()
        );
    }
    return std::move(ds);
}

void save_stats(std::ofstream& fout, Stats& stats) {
    fout << stats.docs_count       << ' ';
    fout << stats.freq.size()      << ' ';
    fout << stats.dict_size.size() << ' ';
    for (int i = 0; i < stats.dict_size.size(); i++)
        fout << stats.dict_size[i] << ' ';
    fout << '\n';
    for (auto& [tag, info] : stats.freq) {
        fout << tag << ' ' << info.classes << '\n';
        for (size_t i = 0; i < stats.dict_size.size(); i++) {
            fout << info.wordsum[i] << ' ';
            for (auto& [word, cnt] : info.word[i])
                fout << word << ' ' << cnt << ' ';
            fout << '\n';
        }
    }
}

Stats& load_stats(std::ifstream& fin) {
    Stats ret;
    int X_size, freq_size;
    fin >> ret.docs_count >> X_size >> freq_size;
}
