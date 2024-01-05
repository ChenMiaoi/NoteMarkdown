#include <cstdint>
#include <iostream>

// in C++11 'enum class' data type is a type safe enumerator that is not
// implicitly convertible to int

// allow to set the underlying type
enum class Color: int8_t {
    BLACK, BLUE = -1, GREEN
};

// C++17 support attributes
enum class Fruit {
    APPLE, CHERRY
};

enum Device {
    PC
};

int main() {
    Color color = Color::BLUE;
    Fruit fruit = Fruit::CHERRY;

    // bool b = (color == fruit);
    // compile error, they are different things entirely

    // int a1 = Color::BLACK;   compile error

    int a2 = (int)Color::BLACK; // ok, provide explicit conversion

    std::cout << (Color::BLACK < Color::BLUE) << std::endl;
    // automatically enumerated in increasing order
    std::cout << (Color::BLACK == Color::GREEN) << std::endl;

    // C++17 supports direct-list-initialization
    Color a {-1};    // ok, equal to Color::BLUE
    std::cout << (Color::BLUE == a) << std::endl;

    // C++20 allows to introduce the enumerator identifiers into the local scope
    // to decrease the verbosity
    switch (color) {
        using enum Color;
        case BLACK: break;
        case BLUE: break;
    }

    // C++17 constexpr expression don't allow out-of-range values for (only)enum
    // without explicit underlying type
    constexpr Device d = (Device) - 1;  // but C++20 ok?
    return 0;
}