#include <iostream>

// C++ dosen't allow anonymous struct
// struct {
//     int x;
// };

// Bitfield
struct S1 {
    int b1: 10;     // range [0, 1023]
    int b2: 10;     // range [0, 1023]
    int b3: 8;      // range [0, 255]
};  // sizeof S1: 4B

struct S2 {
    int b1: 10;
    int   : 0;      // reset: force the next field to start at bit 32
    int b2: 10;
};  // sizeof S2: 8B

union A {
    int  x;
    char y;
};

int main() {
    A a;
    // litle-endian
    a.x = 1023;     // 00..000'001'111'111'111
    a.y = 0;        // 00..000'001'100'000'000

    std::cout << a.x << std::endl;

    // C++17 introduces std::variant to represent a type-safe union
    return 0;
}