#include <functional>
#include <iostream>
#include <memory>
#include <stdio.h>
#include <string>
#include <thread>
#include <utility>

void f(int i, const std::string& s) {
    std::cout << "hello f" << std::endl;
}

void oops(int some_param) {
    char buffer[1024];
    sprintf(buffer, "%i", some_param);
    
    /**
     * ! 将本地变量的指针引用传入，如果线程detach，会导致buffer可能已经被销毁后才使用
     * ! 是一种UB
     */
    //  std::thread t(f, 3, buffer);
    /**
     * ! 出现这种情况的主要原因是，buffer会在缓冲区内转换为string，只要我们体验进行转换，
     * ! 并且使其变为右值即可
     */
     std::thread t(f, 3, std::string {buffer});
     t.detach();
}

using widget_id = int;
class widget_data {};

void update_data_for_widget(widget_id w, const widget_data& data) {
    std::cout << "hello " << __func__ << std::endl;
}
void display_status() {
    std::cout << "hello " << __func__ << std::endl;
}
void process_widget_data(widget_data w) {
    std::cout << "hello " << __func__ << std::endl;
}

void oops_again(widget_id w) {
    widget_data data;
    /**
     * ! 如果函数中是一个non-const的ref对象，那么编译就会报错
     * ! 因为在对线程函数传参时，参数会被默认处理为右值以便于后续转换和移动
     * ! 而non-const ref类型无法接受一个右值类型
     */
    // std::thread t(update_data_for_widget, w, data);
    /**
     * ! 因此我们需要进行一个包装: std::ref
     */
    std::thread t(update_data_for_widget, w, std::ref(data));
    display_status();
    t.join();
    process_widget_data(data);
}

/**
 * ! 如果十分熟悉std::bind的话，那么std::bind的机制和thread的构造机制几乎相同
 */
class X {
public:
    void do_lengthy_work() {}
};

void func() {
    X my_x;
    /**
     * ! 前两个参数是固定，后面第三个参数开始才是函数的第一个参数
     */
    std::thread t(&X::do_lengthy_work, &my_x);
}

class big_object {
    int _data;
public:
    void prepare_data(int data) {
        _data = data;
    }
};
void process_big_object(std::unique_ptr<big_object>) {}

void oops2() {
    /**
     * ! 除了上述的特殊传参外，还需要注意一种：
     * ! 只允许移动的传参，比如 unique_ptr
     * ! 对于这种特殊的传参，那么就需要手动的进行移动: std::move
     */
    std::unique_ptr<big_object> p (new big_object);
    p->prepare_data(42);
    std::thread t(process_big_object, std::move(p));
    /**
     * ! 对于thread来说，标准库实现规定了thread只准移动，禁止拷贝，因此每一个thread都会负责一个实例
     */
}

int main() {
    oops_again(1);
    func();
    oops2();
    return 0;
}