#ifndef FLOAT_INT_TABLE_H
#define FLOAT_INT_TABLE_H

#include <armadillo>

namespace util {

class FloatIntTable {

public:

    void addPair(double newFloat, int newInt);

    void sort();

    std::vector<int> findInts(double lowerFloat, double upperFloat);

private:

    std::vector<std::pair<double,int>> floatIntTable;

};

}

#endif // FLOAT_INT_TABLE_H
