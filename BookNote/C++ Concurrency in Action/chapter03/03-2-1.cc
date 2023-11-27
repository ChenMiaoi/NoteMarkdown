#include <algorithm>
#include <iostream>
#include <list>
#include <mutex>

std::list<int> some_list;
std::mutex some_mtx;

void add_to_list(int value) {
    std::lock_guard<std::mutex> guard(some_mtx);
    some_list.push_back(value);
}

bool list_contain(int value_to_find) {
    std::lock_guard<std::mutex> guard(some_mtx);
    return std::find(some_list.begin(), some_list.end(), value_to_find) != some_list.end();
}

int main() {
    return 0;
}