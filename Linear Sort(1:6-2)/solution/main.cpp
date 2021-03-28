#include <iostream>
#include "Record.hpp"
#include "Vector.hpp"
#include "Sort.hpp"
#include <string.h>

using namespace NRecord;
using namespace NVector;

int main(int argc, char const *argv[]) {
    char* key = new char[KEY_LEN+1];
    char* number = new char[KEY_LEN];
    char* val = new char[VAL_LEN];
    NVector::TVector<TRecord> a;
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
        a.PushBack(TRecord(key, number, val));
        key = new char[KEY_LEN+1];
        number = new char[KEY_LEN];
        val = new char[VAL_LEN];
    }
    delete[] key;
    delete[] number;
    delete[] val;
    NRadixSort::RadixSort(a);
    for (size_t i = 0; i < a.Size(); i++) {
        printf("%s\t%s\n", a[i].number, a[i].val);
        delete[] a[i].key;
        delete[] a[i].number;
        delete[] a[i].val;
    }
}
