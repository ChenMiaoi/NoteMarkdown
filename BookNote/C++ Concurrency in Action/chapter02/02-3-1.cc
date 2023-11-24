#include <iostream>
#include <thread>
#include <utility>

void some_function() {
    std::cout << "hello " << __FUNCTION__ << std::endl;
}
void some_other_function() {
    std::cout << "hello " << __FUNCTION__ << std::endl;
}

void oops() {
    /**
     * ! 这里就展示了，thread只能移动，并且一次只会管理一个实例
     */
    std::thread t1(some_function);
    std::thread t2 = std::move(t1);
    t1 = std::thread(some_other_function);
    std::thread t3;
    t3 = std::move(t2);
    t1 = std::move(t3); /* terminal */
}

int main() {
    oops();
    return 0;
}