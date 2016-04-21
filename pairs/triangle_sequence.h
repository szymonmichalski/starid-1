#ifndef TRIANGLE_SEQUENCE_H
#define TRIANGLE_SEQUENCE_H

#include "../base/sensor.h"

namespace pairs {

class TriangleSequence
{
public:
    TriangleSequence();
    TriangleSequence(base::Obs& obs);
    std::vector<int> ndxs;
};

}

#endif // TRIANGLE_SEQUENCE_H
