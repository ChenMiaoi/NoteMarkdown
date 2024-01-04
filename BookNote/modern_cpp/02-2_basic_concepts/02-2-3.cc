#include <cstdint>
#include <iostream>
#include <limits>
#include <numeric>

// Undefined Behavior

void f(int* ptr, int pos) {
    pos++;
    if (pos < 0) return;    // --> here compiler will assume that signed overflow never happen
    ptr[pos] = 0;           // compiled with optimization leads to segment fault 
}

void f1(int size) {
    for (int i = 1; i < size; i += 2);
    //! when size == INT32_MAX?
    // size will overflow
    // if u want to have a safety solution:
    // i < size && i + step > i
}

int main() {
    //! 1. more negative values than positive 
    int x = std::numeric_limits<int>::max() * -1;   // (2^31 - 1) * -1
    std::cout << x << "\n";                         // -2^31 + 1 [ok]

    int y = std::numeric_limits<int>::min() * -1;   // -2^31 * -1
    std::cout << y << "\n";                         // 2^31 [overflow]

    // A pratical example
    int tmp[10];
    f(tmp, INT32_MAX); 

    //! 2. Initialize an integer with a value larger
    int z = 3'000'000'000;

    //! 3. Bitwise operation on signed integer types
    int y1 = 1 << 12;

    //! 4. Shift larger than bits of the data type (include unsigned)
    unsigned y2 = 1u << 32u;

    //! 5. UB in implicit conversion
    uint16_t a = 65535;
    uint16_t b = 65535;
    std::cout << (a * b) << '\n';   // expected 4'294'836'255
                                    // but overflow
    
    for (int i = 0; i < 4; i++) {
        std::cout << i * 1'000'000'000 << std::endl;
    }
    // output what?
    // with optimization, it is an infinite loop
    // --> 1'000'000'000 * i > INT32_MAX
    // ub
    //! so, the compiler translates the multiplication constant into an addition
    // in gcc 12.3.0 x86 AT&T O2:
    // movq    %rbx, %rdi
    // addl    $1000000000, %r12d

    f1(INT32_MAX);
    return 0;
}