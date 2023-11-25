#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <thread>
#include <vector>

void do_work(int id) {
    std::cout << "thread id: " << id << std::endl;
}

void f() {
    std::vector<std::thread> threads;
    for (int i = 0; i < 20; i++) {
        threads.emplace_back(do_work, i);
    }
    for (auto& entry : threads) 
        entry.join();
}

int main() {
    
    return 0;
}