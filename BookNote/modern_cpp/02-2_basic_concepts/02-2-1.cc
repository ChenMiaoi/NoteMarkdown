#include <cstdint>
#include <iostream>

int main() {
    // we should use fixed width integer types more, not native
    int8_t i8 = 1;

    // WARN IO stream interprets uint8_t and int8_t as char, not as integer
    int8_t var;
    std::cin >> var;            // read '2'
    std::cout << var << " ";    // write '2'
    int a = var * 2;            
    std::cout << a;             // write '100'

    // size_t / ptrdiff_t are 4B on 32-bit, and 8B on 64-bit
    // in C++23 adds us / UZ literals for size_t, and z / Z for ptrdiff_t

    //! Promotion to a larger type keeps sign
    int16_t x = -1;
    int     y = x;          // keep sign
    std::cout << y << "\n"; // y = -1

    //! Truncation to a smaller type modulo the number of bits of the smaller type
    int     x1 = 65537;         // 2^16 + 1
    int16_t y1 = x1;            // x % 2^16
    std::cout << y1 << "\n";    // y1 = 1

    int     x2 = 32769;         // 2^15 + 1
    int16_t y2 = x2;            // x % 2^16
    std::cout << y2 << "\n";    // y2 = -32767

    return 0;
}