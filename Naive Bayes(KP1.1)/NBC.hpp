#include "Data.hpp"
#include <unordered_map>
#include <map>
#include <cmath>
#include <array>
#include <set>
#include <functional>

class NBC {
private:
    Stats stats;
    const int Laplace_smoothing = 1;
    const int maxClasses_per_feat = 2;
public:
    NBC() = default;
    NBC(Stats&&);
    Stats& get_stats();
    void fit(std::vector<std::reference_wrapper<const Feature>>& X, const Feature& y);
    Feature predict(std::vector<std::reference_wrapper<const Feature>>& X);
};
