#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>

namespace util {

class Stopwatch {

public:

    std::chrono::steady_clock::time_point t1;
    std::chrono::steady_clock::time_point t2;

    Stopwatch() {
        t1 = std::chrono::steady_clock::now();
    }

    int end() {
        t2= std::chrono::steady_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    }

    void reset() {
        t1 = std::chrono::steady_clock::now();
    }
};

}

#endif // STOPWATCH_H
