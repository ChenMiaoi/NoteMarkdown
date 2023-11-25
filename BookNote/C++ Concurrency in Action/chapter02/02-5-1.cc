#include <iostream>
#include <thread>

int main() {
    std::thread::id master;
    auto tid = std::this_thread::get_id();

    std::cout << "master = " << master << "\n"
            << "tid = " << tid << "\n"
            << "master eq tid: " << (master == tid);
    return 0;
}