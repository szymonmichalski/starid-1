#ifndef FLOAT_INT_TABLE_H
#define FLOAT_INT_TABLE_H

#include <armadillo>
#include <cereal/access.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/tuple.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/unordered_map.hpp>

namespace util {

class FloatIntTable {

public:

    void addPair(double newFloat, int newInt);

    void sort();

    std::vector<int> findInts(double lowerFloat, double upperFloat);

private:

    std::vector<std::pair<double,int>> floatIntTable;

    friend class cereal::access;
    template <class Archive> void serialize(Archive& ar) {
        ar(floatIntTable);
    }

};

}

#endif // FLOAT_INT_TABLE_H
