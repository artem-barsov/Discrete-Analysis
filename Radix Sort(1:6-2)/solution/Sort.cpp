#include "Sort.hpp"

using namespace NRecord;

namespace NRadixSort {
    void RadixSort(NVector::TVector<NRecord::TRecord>& a) {
        for (int d = 0; d < KEY_LEN; d++) {
            size_t c[K+1] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            for (size_t i = 0; i < a.Size(); i++) {
                ++c[a[i].key[d]-'0'];
            }
            for (int i = 1; i <= K; i++) {
                c[i] += c[i-1];
            }
            NVector::TVector<TRecord> b(a.Size());
            for (long long i = a.Size()-1; i >= 0; --i) {
                b[c[a[i].key[d]-'0']-1] = a[i];
                --c[a[i].key[d]-'0'];
            }
            a.Swap(b);
        }
    }
} /* NRadixSort */
