#include <iostream>
#include <thread>

int main(int, char**){
    std::thread t([]() {
        std::cout << "Hello Concurrency World\n";
    });
    t.join();
    return 0;
}
