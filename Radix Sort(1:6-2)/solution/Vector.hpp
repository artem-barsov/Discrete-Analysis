#pragma once

#include <cstddef>
#include <cstdlib>

namespace NVector {
    template <typename T>
    class TVector {
    private:
        T* data = nullptr;
        size_t storedSize = 0;
        size_t containerSize = 0;
        template <typename TP>
        void inline Swap(TP& lhs, TP& rhs) {
            TP tmp = lhs;
            lhs = rhs;
            rhs = tmp;
        }
    public:
        TVector()
            : data(nullptr), storedSize(0), containerSize(0) { }
        TVector(const long long size, const T& defaultValue = T()) {
            if (size < 0) {
                return;
            }
            storedSize = size;
            containerSize = 1;
            while (containerSize < size) {
                containerSize <<= 1;
            }
            data = (T*)malloc(containerSize * sizeof(T));
            for (size_t i = 0; i < size; i++) {
                data[i] = defaultValue;
            }
        }
        ~TVector() {
            for (size_t i = containerSize-1; i != size_t(-1); --i) {
                data[i].~T();
            }
            free(data);
        }
        const size_t Size() const {
            return storedSize;
        }
        void PushBack(const T& value) {
            if (storedSize == containerSize) {
                if (!containerSize) {
                    containerSize = 1;
                }
                containerSize <<= 1;
                data = (T*)realloc(data, containerSize * sizeof(T));
            }
            data[storedSize++] = value;
        }
        void PushBack(const T&& value) {
            if (storedSize == containerSize) {
                if (!containerSize) {
                    containerSize = 1;
                }
                containerSize <<= 1;
                data = (T*)realloc(data, containerSize * sizeof(T));
            }
            data[storedSize++] = value;
        }
        void Swap(TVector<T>& other) {
            Swap(this->storedSize, other.storedSize);
            Swap(this->containerSize, other.containerSize);
            Swap(this->data, other.data);
        }
        T& operator [] (const size_t idx) {
            return data[idx];
        }
        const T& operator [] (const size_t idx) const {
            return data[idx];
        }
    };
} /* NVector */
