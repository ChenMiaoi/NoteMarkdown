#include <iostream>
#include <numeric>
#include <vector>
#include <thread>
#include <algorithm>

template <typename Iterator, typename T>
struct accumulate_block {
    void operator() (Iterator first, Iterator last, T& result) {
        result = std::accumulate(first, last, result);
    }
};

/**
 * 值得注意的点
 * 1. 这个并行累加器，对浮点类型的支持程度不够
 * 2. 迭代器的要求至少为forward iterators
 * 3. T类型必须支持默认构造
 * 4. 不能从thread中直接的传递一个值，而是要通过ref包装
 */

template <typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init) {
    unsigned long const length = std::distance(first, last);
    // 如果容器的长度为0，那么就返回初始值
    if (!length) return init;
    unsigned long const min_per_thread = 25;    // 为了防止创建大量线程
    unsigned long const max_threads = (length + min_per_thread - 1) / min_per_thread;
    unsigned long const hardware_threads = std::thread::hardware_concurrency();
    // 选择一个合适的线程数
    unsigned long const num_threads = std::min(
        hardware_threads != 0 ? hardware_threads : 2, 
        max_threads);
    // 计算出每一个线程负责的块大小
    unsigned long const block_size = length / num_threads;
    // 对每一个线程计算结果统计的容器
    std::vector<T> results (num_threads);
    // 创建出对应数量的进程
    std::vector<std::thread> threads (num_threads - 1);
    Iterator block_start = first;
    for (unsigned long i = 0; i < num_threads - 1; i++) {
        Iterator block_end = block_start;
        // 计算一个线程的任务开始和结束迭代器位置
        std::advance(block_end, block_size);
        threads[i] = std::thread(
            // 转交给内部的accumulate函数计算出结果
            accumulate_block<Iterator, T>(),
            block_start, block_end, std::ref(results[i])
        );
        // 更新下一个线程任务起始地址
        block_start = block_end;
    }
    // 计算出最后一个线程任务结果
    accumulate_block<Iterator, T>() (block_start, last, results[num_threads - 1]);
    for (auto& entry : threads) entry.join();

    // 计算每一个任务结果累加
    return std::accumulate(results.begin(), results.end(), init);
}

int main() {
    std::vector<int> numbers(100);
    for (int i = 0; i < numbers.size(); i++)
        numbers.push_back(i);
    auto ret = parallel_accumulate(numbers.begin(), numbers.end(), 0);
    std::cout << ret << std::endl;
    return 0;
}