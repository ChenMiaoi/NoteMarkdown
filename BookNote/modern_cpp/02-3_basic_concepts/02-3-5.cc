#include <iostream>

// Avoid Unused Variable Warning [[maybe_unused]]

template <typename T>
int f([[maybe_unused]] T value) {
    if constexpr (sizeof(value) >= 4)
        return 1;
    else 
        return 2;
}

template <typename T>
int g([[maybe_unused]] T value) {
    using R = decltype(value);
    return R{};
}

int main() {

    return 0;
}