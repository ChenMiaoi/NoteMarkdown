#include <iostream>
#include <string>
#include <thread>

void print(const std::string& str) {
    std::cout << "start: " << str << "\n";
}

void do_some_work() { print(__func__); }
void do_something(int n) { print(__func__); }
void do_something_else() { print(__func__); }

class background_task {
public:
    void operator() () const {
        do_something(0);
        do_something_else();
    }
};

struct func {
    int _i;
    func(int& i): _i(i) {}

    void operator() () {
        for (unsigned int j = 0; j < 1000000; ++j) {
            do_something(_i);
        }
    }
};

void oops() {
    /**
     * ! 当线程传入参数为引用或指针，但没有等待其结束时
     * ! 可能`some_local_state`已经被摧毁，而线程才刚刚获取
     */
    int some_local_state = 0;
    func my_func (some_local_state);
    std::thread my_thread (my_func);
    my_thread.detach();
}

int main() {
    background_task bt;
    std::thread t(bt);
    /**
     * ! 这里会导致C++静态分析出现二义性
     * ! 可能会被识别为定义一个t1的参数为background_task，返回值为thread的函数
     * @code {.cc}
     * std::thread t1(background_task());
     * @endcode
     * ? 使用初始化列表 `{}`能够避免二义性的发生
     * ? 或者使用((background_task()))避免
     */
    std::thread t1 {background_task()};
    std::thread t2 ((background_task()));

    /**
     * ! 一般来说，thread中最常使用的是lambda表达式
     */
    std::thread t3 ([]() {
        do_something(0);
        do_something_else();
    });

    oops();
    return 0;
}