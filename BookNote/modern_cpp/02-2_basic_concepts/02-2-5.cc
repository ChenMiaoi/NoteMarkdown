#include <iostream>
#include <limits>

int main() {
    std::cout <<    0 / 0   << std::endl;    // UB
    std::cout <<  0.0 / 0.0 << std::endl;    // "nan"
    std::cout <<  5.0 / 0.0 << std::endl;    // "inf"
    std::cout << -5.0 / 0.0 << std::endl;    // "-inf"

    auto inf = std::numeric_limits<float>::infinity();
    std::cout << (-0.0 == 0.0)   << std::endl;                          // true, 0 == 0
    std::cout << ((5.0f / inf) == (-5.0f / inf)) << std::endl;          // true, 0 == 0
    std::cout << ((10e40f) == (10e40f + 9'999'999.0f)) << std::endl;    // true, inf == inf
    std::cout << ((10e40)  == (10e40f + 9'999'999.0f)) << std::endl;    // false, 10e40 != inf
    return 0;
}