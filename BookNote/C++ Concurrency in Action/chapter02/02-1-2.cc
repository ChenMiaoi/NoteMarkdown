#include <exception>
#include <iostream>
#include <stdio.h>
#include <thread>

struct func {
    int _i;
    func(int i): _i(i) {}

    void operator() () {
        for (int j = 0; j < 100000; j++) {
            printf("start: %d -> %d\n", j, _i);
        }
    }
};

void do_something_in_current_thread() {
    printf("do_something_in_current_thread: doing nothing\n");
}

void f() {
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread my_thread(my_func);
    try {
        do_something_in_current_thread();
    } catch (std::exception ex) {
        /**
         * ! 为了防止异常抛出时后续代码不会被执行的状况，因此要在所有可能执行且不冲突的情况下避免无法join的情况
         */
        my_thread.join();
        throw ;
    }
    my_thread.join();
}

int main() {
    f();
    return 0;
}