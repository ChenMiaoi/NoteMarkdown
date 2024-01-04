#include <fenv.h>
#include <iostream>
#include <cfenv>

// in C++11 allows determining if a floating-point exceptional condition has occurred
// by using floating-point exception in <cfenv>

/**
 *! MACRO
 * FE_DIVBYZERO  --> division by zero
 * FE_INEXACT    --> rounding error
 * FE_INVALID    --> invalid operation, i.e. NaN
 * FE_OVERFLOW   --> overflow (reach saturation value +inf)
 * FE_UNDERFLOW  --> underflow (reach saturation value -inf)
 * FE_ALL_EXCEPT --> all exceptions
 */

#pragma STDC FENV_ACCESS ON

int main() {
    std::feclearexcept(FE_ALL_EXCEPT);
    auto x = 1.0 / 0.0;
    std::cout << (bool)std::fetestexcept(FE_DIVBYZERO) << std::endl;

    std::feclearexcept(FE_ALL_EXCEPT);
    auto x2 = 0.0 / 0.0;
    std::cout << (bool)std::fetestexcept(FE_INVALID) << std::endl;

    std::feclearexcept(FE_ALL_EXCEPT);
    auto x3 = 1e38f * 10;
    std::cout << (bool)std::fetestexcept(FE_OVERFLOW) << std::endl;
    return 0;
}