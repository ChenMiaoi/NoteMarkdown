#include <iostream>
#include <stdexcept>
#include <thread>

class scoped_thread {
    std::thread _t;
public:
    explicit scoped_thread(std::thread t): _t(std::move(t)) {
        std::cout << __func__ << std::endl;
        if (!_t.joinable())
            throw std::logic_error("No thread");
    }
    ~scoped_thread() {
        _t.join();
        std::cout << __func__ << std::endl;
    }

    scoped_thread(const scoped_thread&) = delete;
    scoped_thread& operator= (const scoped_thread&) = delete;
};

struct func {
    int _i;
    func(int& i): _i(i) {}

    void operator() () {
        for (unsigned int j = 0; j < 10; ++j) {
            std::cout << "start: " << j << " -> " << _i << "\n";
        }
    }
};

void f() {
    int some_local_state;
    scoped_thread t { std::thread(func(some_local_state)) };
}

int main() {
    f();
    return 0;
}