#include "Data.hpp"
#include <unordered_map>
#include <map>
#include <cmath>
#include <array>
#include <queue>
#include <functional>

class NBC {
private:
    Stats stats;
    const double Laplace_smoothing = 1;
public:
    NBC() = default;
    NBC(Stats&&);
    Stats& get_stats();
    void fit(std::vector<std::reference_wrapper<const Feature>>& X, const Feature& y);
    Feature predict(std::vector<std::reference_wrapper<const Feature>>& X);
};
