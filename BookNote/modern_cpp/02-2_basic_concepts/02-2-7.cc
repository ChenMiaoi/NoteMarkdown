#include <iostream>
#include <iomanip>
#include <cmath>

int main() {
    // Integer type is more accurate than floating type for large numbers
    std::cout << 16'777'217          << std::endl;   // print 16'777'217
    std::cout << (int)16'777'217.0f  << std::endl;   // print 16'777'216
    std::cout << (int)16'777'217.0   << std::endl;   // print 16'777'217 [ok]

    // float numbers are diff from double numbers
    std::cout << (1.1 != 1.1f)       << std::endl;   // print true

    // floating-point precision is finite
    std::cout << std::setprecision(20);
    std::cout << 3.33'333'333f;     // print 3.33'333'254
    std::cout << 3.33'333'333;      // print 3.33'333'333

    // floating-point arithmetic is not associative
    std::cout << ((0.1 + (0.2 + 0.3)) == ((0.1 + 0.2) + 0.3)) << std::endl; // print false

    float x = 0.0f;
    for (int i = 0; i < 20'000'000; i++)
        x += 1.0f;
    std::cout << x << std::endl;    // print 16'777'216 !!!

    //! Ceiling division
    float x1 = std::ceil((float)20'000'001 / 2.0f);
    std::cout << x1 << std::endl;   // print 10'000'000
    return 0;
}