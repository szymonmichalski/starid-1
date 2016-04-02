#ifndef INDEXFINDER_H
#define INDEXFINDER_H

#include <vector>
#include <string>

namespace indexfinder {

// doubles are physical values to be sorted then searched
// ints are indexes refering back to the original symbol table
class IndexFinder {
public:
    bool sortDoubles(std::vector<std::pair<double,int>>& pairs);
    std::vector<int> findIndexes(double low, double hi);

private:
    std::vector<std::pair<double,int>> pairs_;
};

}
#endif

