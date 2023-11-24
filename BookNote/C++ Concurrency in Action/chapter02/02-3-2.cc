#include <algorithm>
#include <iostream>
#include <thread>

void some_function() {
    std::cout << "hello " << __FUNCTION__ << std::endl;
}
void some_other_function() {
    std::cout << "hello " << __FUNCTION__ << std::endl;
}

std::thread f() {
    return std::thread(some_function);
}
std::thread g() {
    std::thread t(some_other_function);
    return t;
}

void f1(std::thread t) {
    std::cout << t.get_id() << std::endl;
}

void oops() {
    auto t = f();
    std::cout << t.get_id() << std::endl;
    t.detach();
    t = g();
    std::cout << t.get_id() << std::endl;
    t.detach();

    f1(std::thread(some_function));
    std::thread g(some_function);
    f1(std::move(g));
}

int main() {
    oops();
    return 0;
}