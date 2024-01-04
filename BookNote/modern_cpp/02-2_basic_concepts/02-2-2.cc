#include <cstddef>
#include <iostream>
#include <vector>

//! Mixing Signed / Unsigned Error
auto f(int a, unsigned b, int* array) {
    if (a > b) 
        return array[a - b];    // segment fault for a < 0
    return 0;
}

int main() {
    int array[1024];
    unsigned a = 10;
    int      b = -1;
    array[10ull + a * b] = 0;   // segment fault, because unsigned cannot be nagative

    std::vector<int> v(100);
    for (size_t i = 0; i < v.size() - 1; i++) 
        array[i] = 3;           // segment fault for v.size() == 0
                                // v.size() return unsigned

    
    unsigned x3 = 32;
    x3          += 2u - 4;      // 2u - 4 = 2 + (2^32 - 4)
                                //        = 2^32 - 2
                                // (32 + (2^32 - 2)) % 2^32
    std::cout << x3 << "\n";
    return 0;
}