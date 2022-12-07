# 1. The Basics

## 1.1 Introduction

#introdution [[#^quote1]]

- 这本书不在于过多的讲解C++的语法，而是去讲C++为什么要这样，稍微深层理解C++背后的含义

>  C++’s model of memory and computation, and the basic mechanisms for organizing code into a program ^quote1

## 1.2 Programs

#Programs/std[[#^quote2]]

- C++的标准库是由C++语言所实现的，而不是通过其他复杂操作

> The standard-library components are perfectly ordinary C++ code provided by every C++ implementation. ^quote2

#Programs/trans1[[#^quote3]]

- 因此，C++标准库能够被C++自身实现，而对于机器语言或者线程上下文切换之类的事情使用的比较少

> That is, the C++ standard library can be implemented in C++ itself and is (with very minor uses of machine code for things such as **thread** context switching). ^quote3

#Programs/trans2[[#^quote4]]

- 这意味着，C++就算面对要求极其苛刻的系统编程任务也能保证充足的表现力和效率性

>  This implies that C++ is sufficiently expressive and efficient for the most demanding systems programming tasks. ^quote4

#Programs/trans3[[#^quote5]]

- 因此，每一种实例的类型(例如，对象、值、变量名和表达式)的使用范围和作用都必须被编译器所知道

>  That is, the type of every entity (e.g., object, value, name, and expression) must be known to the compiler at its point of use ^quote5

#Programs/trans4[[#^quote6]]

- 对象的类型决定了一系列对其适用的操作以及它在内存中的布局

> The type of an object determines the set of operations applicable to it and its layout in memory. ^quote6

### 1.2.1 Hello World

#HelloWorld/trans1[[#^quote7]]

- main()函数返回的整数值，如果有的话，就是该程序对“system”的返回值
	- main()函数返回的非零值，意味着运行失败

> The **int** integer value returned by **main()**, if any, is the program’s return value to “the system.”
>>  A nonzero value from **main()** indicates failure. ^quote7

## 1.3 Function

#Function/declaration[[#^quote8]]

- 一个函数的声明可能包含参数名，这对于编码者/阅读者是有帮助的，但是如果该函数只是一个**声明/定义**而非**实现**，**那么对于编译器来说，它所看见的将不会有参数名**

> A function declaration may contain argument names. This can be a help to the reader of a program, but unless the declaration is also a function definition, the compiler simply ignores such names. ^quote8

```c++
// if we just delclarate a function:  
double sqrt(double var);
// the compiler will ignore such names, just like:  
double sqrt(double var); -> double sqrt(double);

// but if you declarate and implement a funtion:  
double sqrt(double var) {} -> double sqrt(double var) {} // the compiler saw
```

#Function/function_type[[#^quote9]]

- 不仅仅对于值来说有类型，函数一样也是有类型的，在编译器看来，函数的类型就是函数的返回值类型 + 参数列表的各参数的类型

> The type of a function consists of its return type followed by the sequence of its argument types in parentheses. ^quote9

```c++
// for exmaple, there is a function
double get(std::vector<double>& vec, int index);
// -> the type: double(std::vector<double>, int)
```

#Function/member_function_type[[#^quote10]]

- 对于类中的成员函数来说，其类型不仅仅只有返回值类型和列表类型，还需要带上类作用域来指定具体类型

>  For such a _member function_, the name of its class is also part of the function type ^quote10

```c++
// if we code a String class with a operator[]
char& String::operator[] (int index);
// -> the type: char& String::(int)
```

#Function/trans2[[#^quote11]]

- 代码的可维护性第一步在于代码的可读性。**实现可读性的第一步就是将计算任务分成各种有意义的小堆(将其以函数或者类的形式表示)并将其命名**

> We want our code to be comprehensible because that is the first step on the way to maintainability.
> **The first step to comprehensibility is to break computational tasks into meaningful chunks (represented as functions and classes) and name those**. ^quote11

#Function/trans3[[#^quote12]]

- 代码中的错误量与代码量和代码复杂程度有着强相关
	- 代码数量越多，就意味着代码后期维护工作量的增长，而复杂程度就不可避免的压低了代码的可读性

> The number of errors in code correlates strongly with the amount of code and the complexity of the code. ^quote12

#Function/trans4[[#^quote13]]

- 使用函数来做一些特殊化的任务(准确来说应该是特定的模块)通常能够让我们避免在其他代码中杂糅
	- 最简单的例子就是，模块化，每一个函数对应一个单一的功能

>  Using a function to do a specific task often saves us from writing a specific piece of code in the middle of other code; ^quote13

#Function/trans5[[#^quote14]]

- 如果我们无法对一个函数进行合适的命名，这很有可能意味着我们对该函数模块的设计有问题
	- 显然的，如果无法对一个函数的具体作用摸棱两可，那么该函数在后续的作用也会是杂乱无章的

>  If we cannot find a suitable name, there is a high probability that we have a design problem. ^quote14

#Function/trans6[[#^quote15]]

- 当一个函数被重载时，对于每一个基于该函数的重载函数都应该实现相同的语义
	- 也就是说，**建议重载函数都是对相同功能的一个扩展，尽量不要使用重载函数去完成与原函数相悖的功能**

> When a function is overloaded, each function of the same name should implement the same semantics. ^quote15

```c++
// source function
void print(int) {}
// in this case, the 'print' function just want to print the value of type
void print(double) { //... }
// but if you code a 'print' function but use it to output the sum of all var of double type -> when someone use it, it will find that the function is ambiguous.
```

## 1.4 Types Variables and Arithmetic

#Types/type[[#^quote16]]

- 每一个变量名和表达式都有一个类型，而该类型决定了其可能被执行的操作
	- 或者说，类型决定了该类型一系列可用的操作

> Every name and every expression has a type that determines the operations that may be performed on it. ^quote16

#Types/declaration[[#^quote17]]

- **声明是将一个实体引入进程序和指定其类型的语句**

> A _declaration_ is a statement that introduces an entity into the program and specifies its type ^quote17

#Types/value[[#^quote18]]

- 对象是包含(保存)某种类型值的内存空间
	- 其实通俗点说就是**实例化(对象)是一堆值的集合**
- value是根据类型对一系列二进制集合的解释
	- **也就是说，信息不仅仅只有表示，还有解释**
	- **带解释的信息被称为值 -> value， 而类型其实就是一种表示**

> An _object_ is some memory that holds a value of some type.
> A _value_ is a set of bits interpreted according to a type. ^quote18

#Variables/type[[#^quote19]]

- **类型的大小是由实现定义的**。
	- 因此，不同机器上对其的实现不同，其表现的类型大小也不尽相同

> The size of a type is implementation-defined (i.e., it can vary among different machines)^quote19

#Variables/tip[[#^quote20]]

- 为了使长字节文字更利于阅读，我们可以使用单引号(')左右一个数字分隔符
	- 同时，0x的前缀表示十六进制数，0前缀表示八进制数，0b前缀表示二进制数

> To make long literals more readable for humans, we can use a single quote (**’**) as a digit separator. ^quote20

```c++
double x = 3.1415'9265'4646;  
double x1 = 0x7546'ddde'45;  
double x2 = 04657'123;  
double x3 = 0b0101'1100'1101;
```

### 1.4.1 Arithmetic

#Arithmetic/trans1[[#^quote21]]

- 因为历史优化的原因，其他表达式(例如$f(x)+g(y)$)和函数参数(例如$h(f(x), g(y))$)的运算顺序很不幸地是未定义的
	- ~~这也就说明了，为什么谭教授的小红书害人不浅~~

> For historical reasons realated to optimization, the order of evaluation of other expressions (e.g., **f(x)+g(y)**) and of function arguments (e.g.,**h(f(x),g(y))**) is unfortunately unspecified. ^quote21

```c++
// for exmaple, if we write a code
i = 5;
printf("%d%d%d", i++, ++i, i++);

// the code's output is unsoecified, maybe it was 8 8 8, or 5 5 8...
// in fact, it depends on the platform such as gcc, msvc or clang...
```

### 1.4.2 Initialization

#Initialization/initializer_lists[[#^quote22]]

- =赋值操作符是传统的且来源于C的，但是如果你对值的类型不确定，使用常规的{}初始化列表可以避免这个问题，除此之外，**它还能帮你避免隐式转换所导致的信息丢失**
	- 初始化列表规定了必须显示的初始化一个变量(对象) -> 保证了数据的一致性，且减少了隐式类型转换的发生

> The **=** form is traditional and dates back to C, but if in doubt, use the general **{}**-list form. If nothing else, it saves you from conversions that lose information ^quote22

```c++
int i = 7.54;  // in this statement, the i of value is 7, loss the float-point
int i {7.54};  // in this statement, it was error, can't pass the compile
```

#Initialization/constant[[#^quote23]]

- 常量不能是未初始化的，且一个变量只有在极少数条件下才不会被初始化
	- 对变量(甚至是常量)初始化是一个好习惯，尽管你可能当时没有使用

> A constant cannot be left uninitialized and a variable should only be left uninitialized in extremely rare circumstances. ^quote23

#Initialization/type[[#^quote24]]

- 对于内置类型(例如string、vector...)能够在定义的时候隐式的初始化
	- 实际上就是在实例化时，C++默认调用了其默认构造函数

>  User-defined types (such as **string**, **vector**, **Matrix**, **Motor_controller**, and **Orc_warrior**) can be defined to be implicitly initialized ^quote24

#Initialization/auto [[#^quote25]]

- 我们会在不需要在特殊情况下清晰的指明类型的时候使用auto，比如：
	- 定义的类型范围很大，我们需要让阅读代码的人清晰的理解该类型
	- 初始化类型不明确的时候
	- 我们需要明确说明变量的范围或者精度的时候(例如，double 而非 float)

> [!question] why when we need explicited variable to use auto rather that specific type?

> We use **auto** where we don’t have a specific reason to mention the type explicitly. “Specific reasons” include:
>> The definition is in a large scope where we want to make the type clearly visible to readers of our code.
>> The type of the initializer isn’t obvious.
>> We want to be explicit about a variable’s range or precision (e.g., **double** rather than **float**). ^quote25

