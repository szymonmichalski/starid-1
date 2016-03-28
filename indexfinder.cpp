#include "indexfinder.h"
#include <algorithm>

bool indexfinder::IndexFinder::sortDoubles(std::vector<std::pair<double,int>>& pairs) {
    pairs_ = pairs;
    std::sort(pairs_.begin(),pairs_.end());
    return true;
}

std::vector<int> indexfinder::IndexFinder::findIndexes(double low, double hi) {
    auto itlow = std::lower_bound(pairs_.begin(), pairs_.end(), std::make_pair(low, 0));
    auto ithi = std::upper_bound(pairs_.begin(), pairs_.end(), std::make_pair(hi, 0));
    std::vector<int> indexes;
    for (auto it = itlow; it <= ithi; ++it) {
        auto pair = *it;
        indexes.push_back(pair.second);
    }
    return indexes;
}
