#include <iostream>

int f() {
    return 0;
}

int main() {
    char x = 'a';
    switch (x) {
    case 'a': x++;
        // in C++17: avoid warning
        [[fallthrough]];
    case 'b': return 0;
    default: return -1;
    }

    // C++17 introduce if statement with initializer
    int x1 = 5, y = 4;
    if (int ret = x1 + y; ret < 10)  
        std::cout << ret << std::endl;

    // C++17 introduce switch statement with initializer
    switch (auto i = f(); x) {
        case 1: return i + x;
    }

    // C++20 introduce range-for statement with initializer
    for (int i = 0; auto x : {'A', 'B', 'C'})
        std::cout << i++ << ":" << x << std::endl;
    return 0;
}