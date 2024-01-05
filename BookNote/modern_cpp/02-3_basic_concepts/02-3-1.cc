#include <iostream>

// Entities can be declared multiple times, all declarations are the same
// but, each entity, only a single definition is allowed 

void f(int a, char* b);     // function declaration
void f(int a, char* b) {    // function definition
}
void f(int a, char* b);     // multiple declarations is valid

struct A;       // declaration 1
struct A;       // declaration 2 [ok]

struct B {
    int b;
    // A   x;   // compile error incomplete type
    A*  y;      // ok, pointer to incomplete type
};

int main() {

    return 0;
}