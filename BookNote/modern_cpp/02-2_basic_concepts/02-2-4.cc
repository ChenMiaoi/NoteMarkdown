#include <iostream>

// Overflow / Underflow

//! Detecting wraparound for uz types is not trivial

auto is_add_overflow(unsigned a, unsigned b) -> decltype(auto) {
    return (a + b) < a || (a + b) < b;
}

auto is_mul_overflow(unsigned a, unsigned b) -> decltype(auto) {
    unsigned x = a * b;
    return a != 0 && (x / a) != b;
}

int main() {

    return 0;
}