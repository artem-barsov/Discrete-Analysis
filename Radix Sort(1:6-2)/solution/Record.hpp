#pragma once

namespace NRecord {
    const int COUNTRY_LEN = 6; // длина кода страны
    const int CITY_LEN = 7; // длина кода города
    const int NUMBER_LEN = 11; // длина телефонного номера
    const int VAL_LEN = 2060; // длина строки-значения
    const int KEY_LEN = COUNTRY_LEN + CITY_LEN + NUMBER_LEN; // длина ключа

    class TRecord {
    public:
        char* key = nullptr;
        char* number = nullptr;
        char* val = nullptr;
        TRecord();
        TRecord(char* key, char* number, char* val);
    };
} /* NRecord */
