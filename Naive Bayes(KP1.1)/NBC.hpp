#include "Data.hpp"
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <array>
#include <functional>

class NBC {
private:
    Stats stats;
public:
    void fit(std::vector<std::reference_wrapper<const Feature>>& X, const Feature& y);
    Stats& get_stats();
};
