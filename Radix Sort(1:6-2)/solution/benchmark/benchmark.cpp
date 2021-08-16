#include <iostream>
#include <chrono>

#include "../Sort.hpp"
#include "../Vector.hpp"
#include <vector>
#include <string.h>
#include <algorithm>
#include <fstream>

using namespace NRecord;
using namespace NVector;

const char* DURATION_SUFFIX = "us";

int main(int argc, char const *argv[]) {
    NVector::TVector<TRecord> input;
    // std::vector<TRecord> input;
    std::vector<TRecord> inputStl;

    char* key = new char[KEY_LEN+1];
    char* number = new char[KEY_LEN];
    char* val = new char[VAL_LEN];
    while (scanf("%s\t%[^\n]\n", number, val) != EOF) {
        int i = 0, j = strlen(number)-1;
        for (; number[j] != '-'; ++i, --j) {
            key[i] = number[j];
        }
        for (; i < NUMBER_LEN; ++i) {
            key[i] = '0';
        }
        for (--j; number[j] != '-'; ++i, --j) {
            key[i] = number[j];
        }
        for (; i < NUMBER_LEN + CITY_LEN; ++i) {
            key[i] = '0';
        }
        for (--j; number[j] != '+'; ++i, --j) {
            key[i] = number[j];
        }
        for (; i < NUMBER_LEN + CITY_LEN + COUNTRY_LEN; ++i) {
            key[i] = '0';
        }
        key[KEY_LEN] = '\0';
        input.PushBack(TRecord(key, number, val));
        inputStl.push_back(TRecord(key, number, val));
        key = new char[KEY_LEN+1];
        number = new char[KEY_LEN];
        val = new char[VAL_LEN];
    }
    delete[] key;
    delete[] number;
    delete[] val;
    std::cout << "Count of lines is " << input.Size() << std::endl;

    // Измеряем время работы stl сортировки.
    std::chrono::time_point<std::chrono::system_clock> stlStartTs = std::chrono::system_clock::now();
    std::stable_sort(std::begin(inputStl), std::end(inputStl),
        [](const TRecord&lhs, const TRecord&rhs) {
            for (int i = KEY_LEN; i >= 0; --i) {
                if (lhs.key[i] != rhs.key[i])
                    return lhs.key[i] < rhs.key[i];
            }
            return true;
        }
    );
    auto stlEndTs = std::chrono::system_clock::now();
    uint64_t stlSortTs = std::chrono::duration_cast<std::chrono::microseconds>(stlEndTs - stlStartTs).count();

    // Измеряем время работы сортировки подсчётом.
    std::chrono::time_point<std::chrono::system_clock> radixStartTs = std::chrono::system_clock::now();
    NRadixSort::RadixSort(input);
    auto radixEndTs = std::chrono::system_clock::now();
    uint64_t radixSortTs = std::chrono::duration_cast<std::chrono::microseconds>(radixEndTs - radixStartTs).count();

    // Вывод
    std::ofstream stl_fout("stl_out.txt", std::ios::out);
    if (stl_fout.is_open()) {
        for (size_t i = 0; i < inputStl.size(); i++) {
            stl_fout << inputStl[i].number << '\t' << inputStl[i].val << '\n';
        }
        stl_fout.close();
    }
    std::ofstream radix_fout("radix_out.txt", std::ios::out);
    if (radix_fout.is_open()) {
        for (size_t i = 0; i < input.Size(); i++) {
            radix_fout << input[i].number << '\t' << input[i].val << '\n';
            delete[] input[i].key;
            delete[] input[i].number;
            delete[] input[i].val;
        }
        radix_fout.close();
    }

    std::cout << "Radix sort time: " << radixSortTs << DURATION_SUFFIX << std::endl;
    std::cout << "STL stable sort time: " << stlSortTs << DURATION_SUFFIX << std::endl;
}
