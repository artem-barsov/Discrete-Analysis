#include "Data.hpp"

const std::string clear_text(const std::string& s) {
    std::string ret;
    for (char ch : s) {
        if ('A' <= ch&&ch <= 'Z')
            ch = ch + 'a' - 'A';
        if ('a' <= ch&&ch <= 'z')
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

const Dataset get_trainset(std::ifstream& fin) {
    Dataset ds;
    int n;
    while (fin >> n) {
        fin.get();
        fill_tags(fin, ds.tags);
        fill_text(fin, ds.text, n+1);
    }
    return ds;
}

const Dataset get_testset(std::ifstream& fin) {
    Dataset ds;
    int n;
    while (fin >> n) {
        fin.get();
        fill_title(fin, ds.title);
        fill_text(fin, ds.text, n);
    }
    return ds;
}

void save_stats(std::ofstream& fout, const Stats& stats) {
    fout << stats.docs_count       << ' '
         << stats.tags_info.size() << ' '
         << stats.dict_size        << '\n';
    for (const auto& [tag, info] : stats.tags_info) {
        fout << tag << ' ' << info.class_count << ' ' << info.words_total << '\n';
        for (const auto& [word, cnt] : info.word_count)
            fout << word << ' ' << cnt << ' ';
        fout << '\n';
    }
}

const Stats load_stats(std::ifstream& fin) {
    Stats ret;
    int tags_count;
    fin >> ret.docs_count >> tags_count >> ret.dict_size;
    while (tags_count--) {
        std::string tag;
        fin >> tag >> ret.tags_info[tag].class_count >> ret.tags_info[tag].words_total;
        int words_left = ret.tags_info[tag].words_total;
        while (words_left > 0) {
            std::string word; int cnt;
            fin >> word >> cnt;
            ret.tags_info[tag].word_count[word] = cnt;
            words_left -= cnt;
        }
    }
    return ret;
}

void save_feature(std::ofstream& fout, const Feature& feat) {
    for (const auto& row : feat) {
        if (!row.empty()) fout << row[0];
        for (int i = 1; i < row.size(); i++)
            fout << ", " << row[i];
        fout << '\n';
    }
}
