# Thread

--- 

## 多线程

> 一般情况：子线程没有执行完毕，而主线程执行完毕，**子线程应该被强行终止**

### thread

#### Construct

```cpp
template <class Fn, class... Args>
explicit thread (Fn&& fn, Args&&... args);
```

- Fn
	- 是一个可调用的函数，包括**函数指针，仿函数，funtion以及lambda表达式**

##### 指针函数

```cpp
void func1(){
	std::cout << "func1 start" << std::endl;
}

int main(){
	std::thread t1(func1);
	return 0;
}
```

##### 仿函数

```cpp
struct Func2{
	void operator()() {
		std::cout << Func2 start" << std::endl;
	}
}

int main(){
	Func2 func2;
	std::thread t2(func2);
	return 0;
}
```

##### function

```cpp
class Func3{
public:
	static void func3(){
		std::cout << "func3 start" << std::endl;
	}

	void func4() {
		std::cout << "func4 start" << std::endl;
	}
};

int main(){
	std::function<void()> func3 = Func3::func3;
	std::thread t3(func3);

	std::function<void()> func4 = std::bind(&Func3::func4, Func3());
	std::thread t3(func4);
	return 0;
}
```

- 注意
	- **如果function一个类函数，那么必须是类的静态成员函数**
		- 个人见解：如果不是静态成员，**普通成员函数就算被function包装之后，依旧是指向成员函数的指针，而thread需要的是一个指向函数的指针**
		- **其实归根结底，就是因为function包装之后也需要传入this指针，如果用bind讲this指针绑定就可以解决**

##### lambda

```cpp
auto func5 = []{
	std::cout << "func4 start" << std::endl;
};

int main(){
	std::thread t4(func5);
	return 0;
}
```

#### join

> 阻塞主线程，让主线程等待子线程执行完毕，子线程和主线程合并

```cpp
thread().join();
```

- 注意：
	- 如果主程序没有阻塞等待，程序会出现错误

#### detach

> 传统的多线程程序的主进程必须要等待子线程执行完毕，然后再退出。
> detach：分离，主线程不和子线程回合，主线程自行执行。**并不影响子线程的执行**

- **但是，如果不等待子线程，有可能导致子线程没有办法被监视，从而引发故障**

```cpp
thread().detach();
```

- 注意：
	- 一旦detach之后，该thread对象就会失去与主线程的关联，**此时这个子线程驻留在后台运行**
	- 相当于被C++接管，当子线程运行完成，由负责清理该线程相关的资源(守护线程)清理
	- **一旦使用detach后，不能再次使用join**

- 优化：
	- 如果在线程创建开始的时候，传入的参数是内置类型，那么建议直接值传递，**值传递之后，thread会构建出另外一个变量，如果用引用传递，则会导致变量地址一致**，从而有可能因为主进程结束导致资源被清空引发错误
	- 如果传递的是类(或自定义类)，需要避免隐式类型转换。因此在创建线程的时候，传入类的临时对象且调用函数中使用引用(**避免浪费**)来接受避免错误

#### joinable

> 判断是否可以成功使用join或detach

```cpp
if (thread().joinable()){
	//...
}
```

#### get_pid

> 获取线程的pid

```cpp
thread().get_pid();
```

#### this_thread

> 指向自身线程的类

```
std::this_thread
```

### 创建多个线程

```cpp
void myPrint(const int& i){  
    std::cout << "thread -> " << i << " -> create success" << std::endl;  
}  
  
int main(){  
    std::vector<std::thread> mythread;  
    for (int i = 0; i < 10; i++){  
        mythread.emplace_back(thread(myPrint, i));  
    }  
    for (auto it = mythread.begin(); it != mythread.end(); it++){  
        if (it->joinable()){  
            it->join();  
        }  
    }  
    return 0;  
}
```

### 数据共享

#### 只读数据

> 只读数据是安全稳定的，不需要特别的处理手段

#### 可读可写

> 大概率会导致程序崩溃，因此需要特殊的处理

#### 其他

> 数据争抢问题，需要特殊处理

## 互斥量

> 保护共享数据，操作时，某个线程用代码把共享数据锁住、操作数据、解锁。**其他想操作共享数据的线程必须等待解锁、锁住、操作、解锁**

