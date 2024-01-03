#include <iostream>
#include <typeinfo>

// in C++11/14 auto can be used to define function type with decltype
auto f1(int x) -> decltype(x) {
    return x;
}

// in C++14 auto can be used to define function type without decltype
auto f2(int x) {
    return x;
}

// in C++20 auto can be used to define function input
void f(auto x) {
    std::cout << "the type: " << typeid(x).name() << "\n"
            << "the value: " << x << "\n";
}

int main() {
    f(2);
    f("hello");
    using namespace std::string_literals;
    f("hello"s);
    return 0;
}