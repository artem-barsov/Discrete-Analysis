#include "Data.hpp"

std::string clear_text(std::string s) {
    std::string ret;
    for (char ch : s) {
        if ('A' <= ch && ch <= 'Z')
            ch = ch + 'a' - 'A';
        if ('a' <= ch && ch <= 'z')
            ret += ch;
        else if (ret.back() != ' ') {
            ret += ' ';
        }
    }
    while (ret.back() == ' ') ret.pop_back();
    return ret;
}

void fill_tags(std::ifstream& fin, Feature& ds_tags) {
    std::string s;
    std::getline(fin, s);
    std::stringstream ss(s);
    ds_tags.push_back(std::vector<std::string>());
    while (std::getline(ss, s, ','))
        ds_tags.back().push_back(clear_text(s));
}

void fill_title(std::ifstream& fin, Feature& ds_title) {
    std::string line;
    std::getline(fin, line);
    std::stringstream ss(clear_text(line));
    ds_title.emplace_back(
        std::istream_iterator<std::string>(ss),
        std::istream_iterator<std::string>()
    );
}

void fill_text(std::ifstream& fin, Feature& ds_text, int nLines) {
    std::string line;
    std::stringstream ss;
    for (int i = 0; i < nLines; i++) {
        std::getline(fin, line);
        ss << clear_text(line) << ' ';
    }
    ds_text.emplace_back(
        std::istream_iterator<std::string>(ss),
        std::istream_iterator<std::string>()
    );
}

Dataset get_trainset(std::ifstream& fin) {
    Dataset ds;
    int n;
    while (fin >> n) {
        fin.get();
        fill_tags(fin, ds.tags);
        fill_title(fin, ds.title);
        fill_text(fin, ds.text, n);
    }
    return ds;
}

Dataset get_testset(std::ifstream& fin) {
    Dataset ds;
    int n;
    while (fin >> n) {
        fin.get();
        fill_title(fin, ds.title);
        fill_text(fin, ds.text, n);
    }
    return ds;
}

void save_stats(std::ofstream& fout, Stats& stats) {
    fout << stats.docs_count       << ' '
         << stats.tags_info.size() << ' '
         << stats.dict_size.size() << ' ';
    for (int i = 0; i < stats.dict_size.size(); i++)
        fout << stats.dict_size[i] << ' ';
    fout << '\n';
    for (auto& [tag, info] : stats.tags_info) {
        fout << tag << ' ' << info.class_count << '\n';
        for (size_t i = 0; i < stats.dict_size.size(); i++) {
            fout << info.words_total[i] << ' ';
            for (auto& [word, cnt] : info.word_count[i])
                fout << word << ' ' << cnt << ' ';
            fout << '\n';
        }
    }
}

Stats load_stats(std::ifstream& fin) {
    Stats ret;
    int X_size, freq_size;
    fin >> ret.docs_count >> freq_size >> X_size;
    ret.dict_size.resize(X_size);
    for (size_t i = 0; i < X_size; i++)
        fin >> ret.dict_size[i];
    for (size_t i = 0; i < freq_size; i++) {
        std::string tag;
        fin >> tag >> ret.tags_info[tag].class_count;
        ret.tags_info[tag].words_total.resize(X_size);
        ret.tags_info[tag].word_count.resize(X_size);
        for (size_t j = 0; j < X_size; j++) {
            fin >> ret.tags_info[tag].words_total[j];
            int uniq_wordsum = ret.tags_info[tag].words_total[j];
            while (uniq_wordsum > 0) {
                std::string word; int cnt;
                fin >> word >> cnt;
                ret.tags_info[tag].word_count[j][word] = cnt;
                uniq_wordsum -= cnt;
            }
        }
    }
    return ret;
}

void save_feature(std::ofstream& fout, Feature& feat) {
    for (auto& row : feat) {
        if (!row.empty()) fout << row[0];
        for (int i = 1; i < row.size(); i++)
            fout << ", " << row[i];
        fout << '\n';
    }
}
