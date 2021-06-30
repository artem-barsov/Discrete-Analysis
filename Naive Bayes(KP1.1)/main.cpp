#include <iostream>
#include <fstream>
#include <functional>
#include <array>
#include "Data.hpp"
#include "NBC.hpp"

int main(int argc, char const *argv[]) {
    if (argc != 6 && argc != 8) {
        std::cout << "./NBC learn --input <input_file> --output <stats_file>" << '\n';
        std::cout << "или" << '\n';
        std::cout << "./NBC classify --stats <stats_file> --input <input_file> --output <stats_file>" << '\n';
        return 0;
    }
    if (std::string(argv[1]) == "learn") {
        std::ifstream fin(argv[3], std::ios::in);
        if (!fin.is_open()) {
            std::cerr << "Unable to open " << argv[3] << '\n';
            return 0;
        }
        const auto& [x1, x2, y] = get_dataset(fin);
        fin.close();
        std::vector X = {std::ref(x1), std::ref(x2)};
        NBC nbc;
        nbc.fit(X, y);
        std::ofstream fout(argv[5], std::ios::out);
        if (!fout.is_open()) {
            std::cerr << "Unable to open " << argv[3] << '\n';
            return 0;
        }
        auto model_stats = nbc.get_stats();
        save_stats(fout, model_stats);
        fout.close();
    }
    else if (std::string(argv[1]) == "classify") {
        std::ifstream fin(argv[3], std::ios::in);
        if (!fin.is_open()) {
            std::cerr << "Unable to open " << argv[3] << '\n';
            return 0;
        }
        auto model_stats = load_stats(fin);
    }
}
