#include <algorithm>
#include <iostream>
#include <cmath>
#include <limits>

// Floating-point compare

//! Don't use absolute error margins
auto are_float_nearly_equal(float a, float b) -> decltype(auto) {
    if (std::abs(a - b) < 10e-7)
        return true;    //! epsilon is fixed by user [warn!]
    return false;
}

//! A not well solution
auto are_float_nearly_equal1(float a, float b) -> decltype(auto) {
    if (std::abs(a - b) / b < 10e-7)
        return true;    //! epsilon is fixed by user [warn!]
    return false;
}

//! A possible solution
auto are_float_nearly_equal2(float a, float b) -> decltype(auto) {
    constexpr float normal_min = std::numeric_limits<float>::min();
    constexpr float relative_err = 10e-7;

    if (!std::isfinite(a) || !std::isfinite(b))
        return false;
    
    float diff = std::abs(a - b);
    if (diff <= normal_min)
        return true;

    float abs_a = std::abs(a);
    float abs_b = std::abs(b);
    return (diff / std::max(abs_a, abs_b)) <= relative_err;
}

int main() {
    std::cout << (0.11f + 0.11f < 0.22f) << std::endl;  // print true
    std::cout << (0.1f + 0.1f > 0.2f) << std::endl;     // print true
    return 0;
}