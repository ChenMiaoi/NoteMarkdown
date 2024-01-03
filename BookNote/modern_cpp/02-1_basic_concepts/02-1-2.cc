#include <iostream>

void f(int i, int j) {
    std::cout << "i = " << i << "\n"
            << "j = " << j << "\n";
}

int main() {
    int a[10] = {0};
    int i = 0;
    i = ++i + 2;    // until C++11: ub
                    // since C++11: i = 3
    std::cout << "i = " << i << "\n";

    i = 0;
    i = i++ + 2;    // until C++17: ub
                    // since C++17: i = 3
    std::cout << "i = " << i << "\n";

    f(i = 2, i = 1);    // until C++17: ub
                             // since C++17: i = 2
    std::cout << "i = " << i << "\n";

    i = 0;
    a[i] = i++;     // until C++17: ub
                    // since C++17: a[1] = 1
    std::cout << "a[1] = " << a[1] << "\n";

    f(++i, ++i);    // ub
    i = ++i + i++;       // ub
    return 0;
}