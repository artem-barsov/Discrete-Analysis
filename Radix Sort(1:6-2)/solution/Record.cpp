#include "Record.hpp"

namespace NRecord {
    TRecord::TRecord()
        : key(nullptr), number(nullptr), val(nullptr) { }
    TRecord::TRecord(char* key, char* number, char* val)
        : key(key), number(number), val(val) { }
} /* NRecord */
