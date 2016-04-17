#include "indexfinder.h"
#include <algorithm>

bool base::IndexFinder::SetTable(std::vector<std::pair<double,int>>& tablein) {
    table = tablein;
    std::sort(table.begin(), table.end());
    return true;
}

std::vector<int> base::IndexFinder::FindIndexes(double low, double hi) {
    auto itlow = std::lower_bound(table.begin(), table.end(), std::make_pair(low, 0));
    auto ithi = std::upper_bound(table.begin(), table.end(), std::make_pair(hi, 0));
    std::vector<int> ndxs;
    for (auto it = itlow; it <= ithi; ++it) {
        auto tablerow = *it;
        ndxs.push_back(tablerow.second);
    }
    return ndxs;
}
