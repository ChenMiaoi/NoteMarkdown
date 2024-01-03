#include <iostream>
#include <utility>

int main() {
    // in C++20 provides the three-way comparison operator
    // spaceship operator
    std::cout << "(3 < 5) " << ((3 <=> 5) < 0) << "\n"
                << "('a' = 'a') " << (('a' <=> 'a') == 0) << "\n"
                << "(7 > 5) " << ((7 <=> 5) > 0) << "\n";

    // in C++20 introduces a set of functions to safely compare int of different types
    unsigned a  = 4;
    int      b  = -3;
    bool     v1 = (a > b);      // false!!!
    bool     v2 = std::cmp_greater(a, b); // true
    std::cout << "v1 = " << v1 << "\n"
            << "v2 = " << v2 << "\n";
    return 0;
}