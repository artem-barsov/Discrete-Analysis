#include "Data.hpp"
#include <unordered_map>
#include <functional>
#include <cmath>
#include <set>

class NBC {
private:
    Stats stats;
    // сглаживание Лапласа для слов, отсутствующих в обучающей выборке
    const int Laplace_smoothing = 1;
    // количество подобранных классов для каждой фичи
    const int maxClasses_per_feat = 2;
public:
    NBC() = default;
    NBC(const Stats&&);
    const Stats& get_stats() const;
    void fit(const Feature&, const Feature&);
    template <size_t SZ>
    const Feature predict(const std::array<std::reference_wrapper<const Feature>, SZ>&) const;
};
