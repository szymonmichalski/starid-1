#ifndef INDEXFINDER_H
#define INDEXFINDER_H

#include <vector>

class IndexFinder
{
public:

    // doubles are the physical values to be sorted and searched
    // indexes refer back to the original symbol table
    IndexFinder(std::vector<std::pair<double,int>>& doubles_with_indexes);

};
#endif

