#ifndef __JTHREAD_H
#define __JTHREAD_H

#include <thread>
#include <utility>

class jthread {
    std::thread _t;
public:
    jthread() noexcept = default;
    template <typename Callable, typename ... Args>
    explicit jthread(Callable&& func, Args&& ... args)
        : _t(std::forward<Callable>(func), std::forward<Args>(args)...) {}
    explicit jthread(std::thread t) noexcept
        : _t(std::move(t)) {}
    jthread(jthread&& rhs) noexcept
        : _t(std::move(rhs._t)) {}
    
    jthread& operator= (jthread&& rhs) noexcept {
        if (joinable()) join();
        _t = std::move(rhs._t);
        return *this;
    }

    jthread& operator= (std::thread other) noexcept {
        if (joinable()) join();
        _t = std::move(other);
        return *this;
    }
    ~jthread() noexcept {
        if (joinable()) join();
    }
public:
    void swap(jthread& other) noexcept {
        _t.swap(other._t);
    }
    bool joinable() const noexcept {
        return _t.joinable();
    }
    void join() {
        _t.join();
    }
    void detach() {
        _t.detach();
    }
    std::thread& as_thread() noexcept {
        return _t;
    }
    const std::thread& as_thread() const noexcept {
        return _t;
    }
};

#endif //! __JTHREAD_H