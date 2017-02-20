#include "util/float_int_table.h"

void util::FloatIntTable::addPair(double newFloat, int newInt)
{
    std::pair<double,int> pair {newFloat, newInt};
    floatIntTable.push_back(pair);
}

void util::FloatIntTable::sort()
{
    std::sort(floatIntTable.begin(), floatIntTable.end());
}

std::vector<int> util::FloatIntTable::findInts(double lowerFloat, double upperFloat)
{
    std::vector<int> intsFromTable;
    auto itlow = std::lower_bound(floatIntTable.begin(), floatIntTable.end(),
                                  std::make_pair(lowerFloat, 0));
    auto ithi = std::upper_bound(floatIntTable.begin(), floatIntTable.end(),
                                 std::make_pair(upperFloat, 0));
    if (itlow == ithi) {
        return intsFromTable;
    }
    for (auto it = itlow; it <= ithi; ++it) {
        auto tableRow = *it;
        intsFromTable.push_back(tableRow.second);
    }
    std::sort(intsFromTable.begin(),intsFromTable.end());
    return intsFromTable;
}
