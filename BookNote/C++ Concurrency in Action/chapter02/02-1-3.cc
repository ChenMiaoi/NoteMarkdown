#include <exception>
#include <iostream>
#include <stdio.h>
#include <thread>

class thread_guard {
    std::thread& _t;
public:
    explicit thread_guard(std::thread& t): _t(t) {}
    ~thread_guard() {
        if (_t.joinable()) {
            _t.join();
        }
    }
    thread_guard(const thread_guard&) = delete;
    thread_guard(thread_guard&&)      = delete;
    thread_guard& operator= (const thread_guard&) = delete;
    thread_guard& operator= (thread_guard&&)      = delete;
};

struct func {
    int _i;
    func(int i): _i(i) {}

    void operator() () {
        for (int j = 0; j < 1000; j++) {
            printf("start: %d -> %d\n", j, _i);
        }
    }
};

void do_something_in_current_thread() {
    printf("do_something_in_current_thread: doing nothing\n");
}

/**
 * ! 通过RAII的方式使得在局部变量销毁前进行join
 */
void f() {
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread my_thread(my_func);
    thread_guard tg(my_thread);
    do_something_in_current_thread();
}

int main() {
    f();
    return 0;
}