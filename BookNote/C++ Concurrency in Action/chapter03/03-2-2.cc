#include <iostream>
#include <mutex>
#include <string>

class some_data {
    int _a;
    std::string _b;

public:
    void do_something() {
        std::cout << "a = " << _a << ", b = " << _b << std::endl;
    }
};

class data_wrapper {
    some_data _data;
    std::mutex _mtx;

public:
    template <typename Function>
    void process_data(Function&& func) {
        std::lock_guard<std::mutex> l(_mtx);
        /**
         * ! 我们的本意是通过互斥锁来守卫数据
         * ! 我们此处传递的是一个函数，将我们内部的数据用于函数
         * ! 但是，此处的参数传递是一个指针/引用
         */
        func(_data);
    }
};

some_data* unprotected;

void malicious_function(some_data& protected_data) {
    // ! 这导致了，我们可以通过这样的操作，非法的获取到我们保护的私有数据
    unprotected = &protected_data;
}

data_wrapper x = {};

void foo() {
    x.process_data(malicious_function);
    // 并且能够成功获取并使用
    unprotected->do_something();
}

int main() {
    foo();
    return 0;
}