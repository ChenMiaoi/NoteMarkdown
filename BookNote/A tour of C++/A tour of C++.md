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
> <center> because compiler is well to use that </center>

> We use **auto** where we don’t have a specific reason to mention the type explicitly. “Specific reasons” include:
>> The definition is in a large scope where we want to make the type clearly visible to readers of our code.
>> The type of the initializer isn’t obvious.
>> We want to be explicit about a variable’s range or precision (e.g., **double** rather than **float**). ^quote25

#Initialization/auto_use[[#^quote26]]

- 这在范型编程中尤为重要，因为程序员很难知道一个对象的确切类型，而且这个对象的类型名可能很长

> This is especially important in generic programming where the exact type of an object can be hard for the programmer to know and the type names can be quite long ^quote26

## 1.5 Scope and Lifetime

#Scope/local[[#^quote27]]

- 函数形参也可以视作是局部变量
	- 因此，就出现了一个问题 -> **函数中的局部变量作为返回值被返回**，因此C++中，局部变量的返回不允许被引用。**除非是右值引用**

> Function argument names are considered local names. ^quote27

#Scope/class[[#^quote28]]

- 也就是说，只要在类中定义的成员变量(**且不是在类中的函数、lambda甚至enum中定义的**)，其作用范围就是在类中全局的

>  if it is defined in a class, outside any function , lambda , or **enum class** . Its scope extends from the opening **{** of its enclosing declaration to the matching **}**. ^quote28

#Scope/global[[#^quote29]]

- 如果一个变量定义在任何函数、lambda甚至结构体之内，那么就称其为全局变量，其作用范围也是全局的 -> 全局的命名空间

> A name not declared inside any other construct is called a _global name_ and is said to be in the _global namespace_. ^quote29

## 1.6 Constants

#Constants/const[[#^quote30]]

- const: 其被主要用于指定接口，以便于可以使用指针或者引用来传值而不必担心数据会被修改 -> **尤其是引用**

> **const**: This is used primarily to specify interfaces so that data can be passed to functions using pointers and references without fear of it being modified. ^quote30

```c++
void function(int* a, int& b) {  
    // if we not use const to limit pointer and reference, the data may be modified  
    *a = 5;  
    b = 6;  
}  
  
void function(const int* a, const int& b) {  
    // if we use const, when we may modify it careless, const will talk to the compiler, we don't want it modified  
    *a = 6; // wrong  
    b = 7; // wrong  
}  
  
void Contants() {  
    // if we use const, we can do pass data without fear of it being modified  
    int a = 2, b = 3;  
    function(&a, b);  
}
```

#Constants/constexpr[[#^quote31]]

- constexpr：大致的意思就是“在编译期计算”。其主要用于指定常量，允许数据放置在只读内存中(不可能损坏) **-> 也就是说，允许其在内存中就进行计算**，为了更高效。

> **constexpr**: meaning roughly “to be evaluated at compile time.” This is used primarily to specify constants, to allow placement of data in read-only memory (where it is unlikely to be corrupted), and for performance. The value of a **constexpr** must be calculated by the compiler. ^quote31

```c++
constexpr long fibonacii(long num) {  
    return num <= 2 ? 1 : fibonacii(num - 1) + fibonacii(num - 2);  
}  
  
long fibonacii(long num, int) {  
    return num <= 2 ? 1 : fibonacii(num - 1) + fibonacii(num - 2);  
}  
  
void Constants(int) {  
    std::chrono::time_point start = std::chrono::system_clock::now();  
    std::cout << fibonacii(45) << "\n";  
    std::chrono::time_point end = std::chrono::system_clock::now();  
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count() << " milliseconds -> constexpr\n";  
  
    start = std::chrono::system_clock::now();  
    std::cout << fibonacii(45, 0) << "\n";  
    end = std::chrono::system_clock::now();  
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count() << " milliseconds -> none\n";  
}
```

> [!question] why the constexpr not work?
> <center> because the constexpr allow function to be called with non-constant </center>

#Constants/constexpr_other[[#^quote32]]

- 被constexpr修饰的函数能够被非常量参数调用，但是如果这样调用之后**运行的结果则是一个非常量表达式**。我们允许一个被contexpr修饰的函数在不需要常量表达式的上下文中使用非常量参数调用 -> **也就解释了，为什么上文中的contexpr失效的原因，因为其递归后的函数的结果就已经是non-constant了**

> A **constexpr** function can be used for non-constant arguments, but when that is done the result is not a constant expression. We allow a **constexpr** function to be called with non-constant-expression arguments in contexts that do not require constant expressions. ^quote32

#Constants/consteval[[#^quote33]]

- 当我们只想使用编译期计算时，我们通常使用**consteval**而不是**constexpr**

> When we want a function to be used only for evaluation at compile time, we declare it **consteval** rather than **constexpr**.  ^quote33

```c++
consteval long fibonacii(long num) {  
    return num <= 2 ? 1 : fibonacii(num - 1) + fibonacii(num - 2);  
}

// when we declarated it by consteval, it'll be wrong. because the 'fibonacii' function is non-constant after iertation
```

#Constants/pure_function[[#^quote34]]

- 声明**contexpr**或者**consteval**的函数是C++对纯函数概念的版本
- **他们不会产生副作用，且只允许使用传过去的信息作为参数。特别是，他们不能修改非局部变量，但他们可以循环且使用自己的局部变量**

> Functions declared **constexpr** or **consteval** are C++’s version of the notion of _pure functions_.
> They cannot have side effects and can only use information passed to them as arguments. In particular, they cannot modify non-local variables, but they can have loops and use their own local variables. ^quote34

```c++
constexpr double nth(double x, int n) { // assume 0 <= n
	double res = 1;
	int i = 0;
	while (i<n) { // while-loop: do while the condition is true 
		res *= x;
		++i;
	}
	return res;
}
```

#Constants[[#^quote35]]

- 在一些地方，语法规则需要常量表达式 -> (例如：数组边界、case标签、模板参数和使用**constexpr**声明的常量)
- 在其他方面，**编译期计算对性能提升非常有用**
- 同时，哪怕不考虑性能，不可变性(具有不可更改状态的对象)也是一个重要的设计理念

> In a few places, constant expressions are required by language rules (e.g., array bounds, case labels, template value arguments, and constants declared using **constexpr**). 
> In other cases, compile-time evaluation is important for performance. 
> Independent of performance issues, the notion of immutability (an object with an unchangeable state) is an important design concern. ^quote35

## 1.7 Pointers, Arrays and References

#Arrays[[#^quote36]]

- **最基本的数据集合就是连续分配的相同类型的数据序列**，被成为数组。其基本上是被硬件所提供的
	- 实际上就是内存，数组是在内存中连续开辟的一段有序空间

> The most fundamental collection of data is a contiguously allocated sequence of elements of the same type, called an _array_. This is basically what the hardware offers. ^quote36

#Arrays/size[[#^quote37]]

```c++
char v[6];
```

- 所有的数组的下限都是0,所以v中有六个元素，v\[0]到v\[5]。**数组的大小必须是常量表达式**
	- 实际上，目前数组也有很多特殊的形式，比如变长数组、柔性数组甚至更多的

> All arrays have **0** as their lower bound, so **v** has six elements, **v[0]** to **v[5]**. The size of an array must be a constant expression. ^quote37

#Pointer[[#^quote38]]

- 在表达式中
	- 前缀"\*"表示"什么什么的内容" -> 或者说包含
	- 前缀"&"表示"什么什么的地址"

> In an expression, prefix unary * means “contents of” and prefix unary **&** means “address of.” ^quote38

```c++
char v[6];
char* p = &v[3];
char x = *p; // *p is the object that p points to
```

![[A tour of C++ Point Graph.png]]

#Arrays/range-for[[#^quote39]]

- 注意：当我们使用初始化列表匿名数组的时候，**不必指定数组绑定** 
	- -> 也就是说，不需要将其给定到一个确切的变量中

> Note that we don’t have to specify an array bound when we initialize it with a list. ^quote39

```c++
for (auto x : {1, 2, 3, 4, 5})
	std::cout << x << " ";
```

#Reference[[#^quote40]]

```c++
void increment() {
	int v[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	for (auto& x : v) // add 1 to each x in v
		++x;
}
```

- 如果你不想**将v中的值复制到变量x中，而只是让x引用一个元素** -> auto& x
- 在上述声明中，这个一元后缀"&"的意思是引用。引用类似于指针，不同之处在于引用不需要使用"\*"来进行解引用去访问指向的值

> If we didn’t want to copy the values from **v** into the variable **x**, but rather just have **x** refer to an element
> In a declaration, the unary suffix **&** means “reference to.” A reference is similar to a pointer, except that you don’t need to use a prefix * to access the value referred to by the reference. ^quote40

#Reference/function[[#^quote41]]

- 引用在指定函数参数上特别有用
	- 引用可以简单的就将指针复杂的功能简化，而达到类似与指针一样的效果 -> 简化内存，修改值...

> References are particularly useful for specifying function arguments. ^quote41

#Reference/const[[#^quote42]]

- 当我们不想修改一个参数的值但是又不想其在传参的过程中产生太大的代价，我们可以使用一个 const reference，也就是说，对常量的引用
	- 事实上，const reference是极为有用的，并且在代码中很常见

> When we don’t want to modify an argument but still don’t want the cost of copying, we use a **const** reference; that is, a reference to a **const**. ^quote42

```c++
double sum(const std::vector<double>&);
```

### 1.7.1 The Null Pointer

#nullptr[[#^quote43]]

- 习惯性的检查一个指针是否指向实际的值是很明智的
	- 由于C/C++的指针可以指向空的原因，做这种检查是很有必要的

> It is often wise to check that a pointer argument actually points to something ^quote43

```c++
int count_x(const char* p, char x) {
	// count the number of occurrences of x in p[]
	// p is assumed to point to a zero-terminated array of char (or to nothing)
	if (p == nullptr)
		return 0;
	int count = 0;
	for (; *p != 0; ++p)
		if (*p == x)
			++count;
	return count;
}
```

#nullptr/Null[[#^quote44]]

- 在老标准的代码中，通常使用0或者NULL而不是nullptr。**但是，nullptr的善用可以消除整形(如0和NULL)和指针(nullptr)之间的潜在混淆**
	- 因为在老标准中，NULL的定义为：

```c++
#define NULL (void*)0 // -> 其极有可能出现二义性，但是又可以有妙用

if (pointer != NULL) // -> 这里可以是判断，但是其实可以通过直接pointer来判断
if (pointer) // -> 如果pointer == NULL时，那么实际上这里就是 if (0)
```

> In older code, **0** or **NULL** is typically used instead of **nullptr**. However, using **nullptr** eliminates potential confusion between integers (such as **0** or **NULL**) and pointers (such as **nullptr**). ^quote44

#nullptr/null-reference[[#^quote45]]

- 这里没有空引用 -> 也就是说**不允许没有初始化引用的存在**
- 引用必须引用有效对象(假定它引用有效对象) -> 但是一些晦涩而又smart的操作可以绕过这一约定 -> 蠢吧

> There is no “null reference.” A reference must refer to a valid object (and implementations assume that it does). There are obscure and clever ways to violate that rule; don’t do that. ^quote45

## 1.8 Tests

## 1.9 Mapping to Hardware

#Map-Hardware[[#^quote46]]

- C++提供了到硬件的直接映射。当你使用一种基本操作时，**其实现是由硬件提供的**，且通常是单独的机器指令。例如，两个整数相加，$x + y$执行一个整数相加的机器指令
- C++实现将计算机的内存视为一系列内存位置，它可以在其中放置(类型化)对象并使用指针寻址

> C++ offers a direct mapping to hardware. When you use one of the fundamental operations, the implementation is what the hardware offers, typically a single machine operation. For example, adding two **int**s, **x+y** executes an integer add machine instruction.
> A C++ implementation sees a machine’s memory as a sequence of memory locations into which it can place (typed) objects and address them using pointers ^quote46

![[Mapping to Hardware.png]]

#Map-Hardware/pointer[[#^quote47]]

- **指针在内存中表示为计算机地址**，因此上图中p的数值为103.
	- 实际上这样看上去很想数组，**因为数组在C++是对"内存中连续的对象序列"的基本抽象**

> A pointer is represented in memory as a machine address, so the numeric value of **p**in this figure would be **103**. ^quote47

#Map-Hardware/construct[[#^quote48]]

- **基本语言结构到硬件的简单映射对于基本的底层性能至关重要**，而C/C++几十年来一直以这种性能而闻名。C/C++的基本机器模型基于计算机硬件而不是某种形式上的数学
	- 也就是说，C/C++能够沟通底层，这也就是为什么C/C++经久不衰的一个原因

> The simple mapping of fundamental language constructs to hardware is crucial for the raw low-level performance for which C and C++ have been famous for decades. The basic machine model of C and C++ is based on computer hardware, rather than some form of mathematics. ^quote48

### 1.9.1 Assignment

#Assignment[[#^quote49]]

- 内置类型的分配是简单的计算机拷贝操作

> An assignment of a built-in type is a simple machine copy operation. ^quote49

```c++
int x = 2;
int y = 3;
x = y;
```

![[Assignment.png]]

> [!tip] The two objects are independent. We can change the value of one without affecting another.**Unlike Java, C# and others, but like C, that is true for all types**

- If we want different objects to refer to the same value, we can do:

```c++
int x = 2;
int y = 3;
int *p = &x;
int *q = &y;
p = q;
```

![[AssignmentPointer.png]]

#Assignment/reference[[#^quote50]]

- 指针和引用都可以指向/引用对象，并且都可以在内存中表示为计算机地址。但是他们相互之间所使用的语言规则不同。**对引用的赋值不会更改引用所引用的内容**

> A reference and a pointer both refer/point to an object and both are represented in memory as a machine address. However, the language rules for using them differ. Assignment to a reference does not change what the reference refers to but assigns to the referenced object ^quote50

```c++
int x = 2;
int y = 3;
int& r = x;
int& r2 = y;
r = r2;  // -> if we do that, just let x become the value of y
```

![[AssignmentReference.png]]

### 1.9.2 Initialization

#Map-Hardware/Initialization[[#^quote51]]

- **初始化不同于赋值**，一般来说，为了使赋值正常工作，分配的对象必须有一个值。
- 另一方面，**初始化的作用在于将未初始化的内存片段变为有效对象**
- 在C/C++中，对于所有类型，读取或者写入未初始化变量的结果都是未定义的

> Initialization differs from assignment. In general, for an assignment to work correctly, the assigned-to object must have a value. On the other hand, the task of initialization is to make an uninitialized piece of memory into a valid object. For almost all types, the effect of reading from or writing to an uninitialized variable is undefined. ^quote51

# 2. User-Defined Types

## 2.1 Introduction

#User-Defined/Introduction[[#^quote52]]

- 然而，C++没有提供一套高级的接口设施去给程序员方便地编写高级应用。相反，C++用了一系列复杂的抽象机制来增强内置类型和操作符，程序员可以从中构建此类高级设施

> However, they don’t provide the programmer with high-level facilities to conveniently write advanced applications. Instead, C++ augments the built-in types and operations with a sophisticated set of _abstraction mechanisms_ out of which programmers can build such high-level facilities. ^quote52

#User-Defined/type[[#^quote53]]

- 使用C++抽象机制从其他类构建的类型称为用户自定义类型
	- 自定义类型通常优于内置类型，因为它们**更易于使用、不易出错，并且通常与直接使用内置类型一样高效，甚至更为高效**

> Types built out of other types using C++’s abstraction mechanisms are called _user-defined types_. ^quote53

## 2.2 Structures

#User-Defined/Structure[[#^quote54]]

- 构建一个新类型的第一步通常是将其所需的元素组织到数据结构中
	- 组织 -> 描述

> The first step in building a new type is often to organize the elements it needs into a data structure ^quote54

```c++
struct Vector {
	double* elem;
	int sz;
};

void vector_list(Vector& v, int s) { // initialize a Vector
	v.elem = new double[s];
	v.sz = s;
}
```

#User-Defined/Structure/new[[#^quote55]]

- new运算符从被成为空闲存储(也被叫做动态内存区和堆)的区域分配内存。**在空闲存储区上被分配的对象与其创建的范围无关，一直"存活"到使用delete操作符将其摧毁**

> The **new** operator allocates memory from an area called the _free store_ (also known as _dynamic memory_ and _heap_). Objects allocated on the free store are independent of the scope from which they are created and “live” until they are destroyed using the **delete** operator ^quote55

```c++
// a simple use Vector
double read_and_sum(int s) {
	Vector v;
	vector_init(v, s);

	for (int i = 0; i !=s; ++i)
		std::cin >> v.elem[i];

	double sum = 0;
	for (int i = 0; i != s; ++i)
		sum += v.elem[i];
	return sum;
}
```

#User-Defined/Structure/to[[#^quote56]]

- 我们使用"."(点)来获取变量(或者甚至引用)结构体成员
- 使用"->"来获取指针结构体成员

> We use **.** (dot) to access **struct** members through a name (and through a reference) and **->** to access **struct** members through a pointer. ^quote56

```c++
void f(Vector& v, Vector& rv, Vector* pv) {  
    int i1 = v.sz;  
    int i2 = rv.sz;  
    int i3 = pv->sz;  
}
```

## 2.3 Classes

#User-Defined/Classes[[#^quote57]]

- 将数据与数据上的操作分开指定具有很多优势，例如能够任意方式使用数据。但是，**用户定义类型需要在表示和操作之间建立更紧密的连接，以具有“真实类型”所期望的所有属性**

> Having data specified separately from the operations on it has advantages, such as the ability to use the data in arbitrary ways. 
> However, a tighter connection between the representation and the operations is needed for a user-defined type to have all the properties expected of a “real type.” ^quote57

#User-Defined/Classes/want[[#^quote58]]

- 特别是，我们经常想要保证用户无法访问表示(**自定义类型中的成员**)，以简化使用且保证数据的一致性(**防止用户对内部数据直接进行更改**)，并允许用户之后通过接口改进表示(**允许用户在定义之后，通过我们设计的接口去规范化的修改内部结构**)。
- 要做到这一点，我们必须区分一个类型的接口(供所有人使用)和它的实现(可以访问其他情况下无法访问的数据)
	- 事实上，这就是OOP中的封装性，**而这种语言机制，就被称为类**

> In particular, we often want to keep the representation inaccessible to users so as to simplify use, guarantee consistent use of the data, and allow us to later improve the representation. To do that, we have to distinguish between the interface to a type (to be used by all) and its implementation (which has access to the otherwise inaccessible data). ^quote58

-   The interface of a class is defined by its **public** members, and its **private**members are accessible only through that interface. The **public** and **private** parts of a class declaration can appear in any order

```c++
class Vector {  
public:  
    Vector(int s): elem{new double[s]}, sz{s} {}  
    double& operator[] (int i) { return elem[i]; }  
    int size() { return sz; }  
private:  
    double* elem;  
    int sz;  
};
```

#User-Defined/Classes/size[[#^quote59]]

> The number of elements (6 in the example) can vary from **Vector** object to **Vector** object, and a **Vector** object can have a different number of elements at different times. **However, the Vector object itself is always the same size.**

```c++
Vector v1(6);
Vector v2(12);

// we can see the sz in v1 is 6 but v2 is 12
sizeof(v1)
sizeof(v2)

// -> the the size of two are both the same value 16
```

- 这是C++中处理不同数量信息的基本技术：一个固定大小的“句柄”，指的是“其他地方”(例如，在new分配的空闲存储区上)
	- **至于为什么sizeof(v1)的值为16,涉及到内存对齐的概念**

![[User-Class-size.png]]

> This is the basic technique for handling varying amounts of information in C++: a fixed-size handle referring to a variable amount of data “elsewhere” (e.g., on the free store allocated by **new**; ^quote59

#User-Defined/Classes/initialize[[#^quote60]]

- 与普通函数不同，构造函数保证了类的对象的初始化。因此，定义构造函数消除了类未初始化变量的问题。

> Unlike an ordinary function, a constructor is guaranteed to be used to initialize objects of its class. Thus, defining a constructor eliminates the problem of uninitialized variables for a class. ^quote60

#User-Defined/Classes/struct[[#^quote61]]

- struct和class之间没有本质上的区别。**默认情况下，struct只是一个成员公开的类**
	- 相对的，class就是成员私有的

> There is no fundamental difference between a **struct** and a **class**; a **struct** is simply a **class** with members **public** by default. ^quote61

## 2.4 Enumerations

#User-Defined/Enumerations/enum_class[[#^quote62]]

- 除了类，C++还支持一种用户自定义类型的可以列出每一项值的简单形式，这就是枚举
- 注意枚举变量在其枚举器的范围内，因为他们可以在不同的枚举中重复使用而不会混淆

> In addition to classes, C++ supports a simple form of user-defined type for which we can enumerate the values
> Note that enumerators are in the scope of their **enum class**, so that they can be used repeatedly in different **enum class**es without confusion. ^quote62

```c++
enum class Color {
	red,
	blue,
	green
};

enum Color {}; // -> the not same as enum class Color
```

> [!fail] In fact, the **class** after the **enum** just to specifie that an enumeration is strongly typed and that ist enumerations are scoped. **You can't ignore the class just use the enum to declaration**

- **Similarly, we cannot implicitly mix Color and integer values**

```c++
int i = Color::red; // -> error: Color::red is not an int
Color c = 2; // -> error: 2 is not a Color
```

#User-Defined/Enumerations/initialize[[#^quote63]]

- 捕获尝试的转换为枚举(**通过隐式转换为枚举**)是防止错误的良好措施。但我们通常希望使用内置类型的值(默认情况是int)初始化枚举 -> 因此显示的转换是允许的 -> **通过列表初始化**

> Catching attempted conversions to an **enum** is a good defense against errors, but often we want to initialize an **enum** with a value from its underlying type (by default, that’s **int**), so that’s allowed, as is explicit conversion from the underlying type ^quote63

```c++
Color x = Color {5};
color y {6};
```

- **Similarly, we can explicitly convert an enum value to its underlying type**

```c++
int x = int(Color::red);
```

#User-Defined/Enumerations/operation[[#^quote64]]

- 默认情况下，枚举只定义了赋值、初始化和比较(例如，\=\= 和 <;)。但是，枚举也是一个用户自定义类型，因此我们可以为其重载运算符

> By default, an **enum class** has assignment, initialization, and comparisons (e.g., \=\=and <; ) defined, annd only those. However, an enumeration is a user-defined type, so we can define operators for it ^quote64

```c++
Traffic_light& operator++ (Traffic_light& t) { // prefix increment: ++Color  
    switch (t) {  
        case Traffic_light::green: return t = Traffic_light::yellow;  
        case Traffic_light::yellow: return t = Traffic_light::red;  
        case Traffic_light::red: return t = Traffic_light::green;  
    }  
}

auto signal = Traffic_light::red;  
Traffic_light next = ++signal;
```

- 这里，有一个值得注意的操作，就是在内部通过switch选择之后，然后再通过赋值到下一个枚举值
	- 因为我们知道，**枚举是按顺序的，且枚举值是一个常量**，这种操作极大的简化了代码，超级优雅

- **If the repetition of the enumeration name, Traffic_light, becomes too tedious, we can abbreviate it in a scope**
	- 我们可以使用using来简化枚举类型的长度

```c++
Traffic_light& operator++ (Traffic_light& t) { // prefix increment: ++Color  
    using enum Traffic_light;  
    switch (t) {        
	    case green: return t = yellow;        
	    case yellow: return t = red;        
	    case red: return t = green;    
    }
}
```

#User-Defined/Enumerations/enum[[#^quote65]]

- **如果你不想显示限定枚举，并且希望枚举值可以为整数(无需显示转换)**，则可以从**enum class**中删除**class**以获取"普通"枚举。而“普通”枚举与enum class无异，但是**可以被隐式转换**

> If you don’t ever want to explicitly qualify enumerator names and want enumerator values to be **int**s (without the need for an explicit conversion), you can remove the **class** from **enum class** to get a “plain” **enum**. The enumerators from a “plain” **enum**are entered into the same scope as the name of their **enum** and implicitly convert to their integer values. ^quote65

```c++
enum Color {
	red,
	green,
	blue
};

int col = Color::green; // -> OK
Color c = 1;
```

- The value of col is 1. **By default, the integer values of enumerators start with 0 and increase by one for each additional enumerator.**

## 2.5 Unions

#User-Defined/Unions[[#^quote66]]

- union是一种结构体，**其中所有成员都分配在同一地址，以至于union占据的空间与其最大的成员一样多**。因此，**union只能为一个成员在同一时间保存一个值**

> A **union** is a **struct** in which all members are allocated at the same address so that the **union** occupies only as much space as its largest member. Naturally, a **union** can hold a value for only one member at a time. ^quote66

```c++
enum class Type { // a Type can hold values ptr and num  
    ptr,  
    num  
};  
  
struct Entry {  
    std::string name;  
    Type t;  
    Node* p; // use p if t == Type::ptr  
    int i;  // use i if t == Type::num  
};  
  
void f(Entry* pe) {  
    if (pe->t == Type::num)  
        std::cout << pe->i;  
    else if (pe->t == Type::ptr)  
        std::cout << pe->p;  
}
```

- The members p and i are never used at the same time, so soace is wasted. Use union can easily recovere.

```c++
union Value {
	Node* p;
	int num;
}
```

- 这种空间优化对于占据大量内存的应用程序或许很重要，因此这样紧凑的内存表示是至关重要的

```c++
struct Entry {  
    std::string name;  
    Type t;  
    Value v;  
};  
  
void f(Entry* pe) {  
    if (pe->t == Type::ptr)  
        std::cout << pe->v.p;  
    else  
        std::cout << pe->v.i;  
}
```

> [!todo] Here is a question: The **"variant"** in $15.4.1

# 3. Modularity

> 模块性

## 3.1 Introduction

#Modularity/Introduction[[#^quote67]]

- C++程序由许多独立开发的部分组成，例如函数、用户自定义类型、类层级结构和模板。**管理如此众多部件的关键是在于明确定义这些部件之间的交互**

> A C++ program consists of many separately developed parts, such as functions , user-defined types, class hierarchies, and templates. The key to managing such a multitude of parts is to clearly define the interactions among those parts. ^quote67

- 第一步，也是最重要的一部是区分部件的接口和实现。**在语言层面，C++通过声明表示接口。声明指明使用函数或类型所需的所有内容**

```c++
double sqrt(double); // the square root function takes a double and returns a double  
  
class Vector { // what is needed to use a Vector  
public:  
    Vector(int s);  
    double& operator[] (int i);  
    int size();  
private:  
    double* elem;  
    int sz;  
};
```

- **The key point here is that the function bodies, the function definitions, can be "elsewhere"**

```c++
double sqrt(double d) { // definition of sqrt()  
    // ...    return 0;  
}  
  
Vector::Vector(int s): elem {new double[s]}, sz {s} { // definition of the constructor  
    // initialize members}  
  
double& Vector::operator[](int i) { // definition of subscription  
    return elem[i];  
}  
  
int Vector::size() { // definition of size()  
    return sz;  
}
```

## 3.2 Separate Compilation

#Modularity/SeparateCompilation[[#^quote68]]

- C++支持分离编译的概念，**用户代码只能看见所使用的类型和函数的声明**

> C++ supports a notion of separate compilation where user code sees only declarations of the types and functions used. ^quote68

- 我们可以通过两种方式实现分离编译：
	- Header files：将声明放置在一个单独的文件，这被称为头文件，然后并以文本的方式\#include需要其声明的头文件
	- Modules：定义模块文件，单独的编译该文件，然后在需要时导入。**导入模块的代码只能看到显式导出的声明**

#Modularity/SeparateCompilation/work[[#^quote69]]

- 上述两者都可用于将程序组织成一组半独立的代码片段。**这种分离可用于最小化编译时间，并强制将程序逻辑上不同的部分分离(从而最大限度地减少错误的可能)**。库通常是独立编译的代码片段(例如，函数)的集合。

> Either can be used to organize a program into a set of semi-independent code fragments. Such separation can be used to minimize compilation times and to enforce separation of logically distinct parts of a program (thus minimizing the chance of errors). A library is often a collection of separately compiled code fragments (e.g., functions). ^quote69

> [!tip] 用于组织代码的头文件技术可以追溯到C语言的早期，**到目前位置仍然是最常见的**。模块的使用在C++20中新增的，其在代码整洁和编译时间方面提供了巨大的优势

### 3.2.1 Header Files

#Modularity/HeaderFile[[#^quote70]]

- 传统上，我们将指定代码接口的声明放在文件中，我们就认为这是一个模块，其名称表明了它的预期用途

> Traditionally, we place declarations that specify the interface to a piece of code we consider a module in a file with a name indicating its intended use. ^quote70

```c++
// Vector.h
class Vector {
public:
	Vector(int s);
	double& operator[] (int i);
	int size();
private:
	double* elem;
	int sz;
}
```

- User can use \#include that file, called a header file, to access that interface

```c++
// user.cc
#include "Vector.h"
#include <cmath>

double sqrt_sum(const Vector& v) {
	double sum = 0;
	for (int i = 0; i != v.size(); ++i)
		sum += std::sqrt(v[i]);
	return sum;
}
```

> [!tip] 为了帮助编译器确保一致性。提供Vector实现的.cc文件还将包括提供其接口的.h文件

```c++
// Vector.cc
#include "Vector.h"  // get Vector's interface

Vector::Vector(int s): elem {new double[s]}, sz {s} {  
  
}  
  
double &Vector::operator[](int i) {  
    return elem[i];  
}  
  
int Vector::size() {  
    return sz;  
}
```

> [!tip] 自行编译的.cpp文件(包括\#includes的h文件)称为翻译单元

![[SeparateVector.png]]

#Modularity/HeaderFile/weakness[[#^quote71]]

- 使用头文件和\#include是一种非常古老的模拟模块化的方式，具有明显的缺点

> The use of header files and **#include** is a very old way of simulating modularity with significant disadvantages ^quote71

- 从编译时间上来看：
	- 如果你#include的头文件中有101个翻译单元，那么该header.h的文本将会被编译器执行101次 -> 很显然，这极大的使得程序臃肿且耗时巨大
- 从顺序依赖关系上来看：
	- 如果我们在header2.h之前#include header1.h，那么header1.h中的声明和宏可能会影响header2.h中代码的含义。相反的如果在header1.h前面#include header2.h，那么header2.h中的声明和宏可能会影响header1.h中的代码
- 从二义性(不一致性)上来看：
	- 在一个文件中定义了一个实体(如类型或者函数)，然后在另一个文件定义它(但是略有不同)，这可能导致崩溃或者细微错误。如果我们(无意或有意)在两个源文件中分别声明一个实体，而不是放置在头文件中，或者通过不同头文件之间的顺序依赖关系，都有可能发生这种情况
- 可传递性：
	- 在头文件中表达声明所需的所有代码都必须出现在该头文件中，这导致了大量代码膨胀，因为头文件#include其他头文件，并且导致了头文件的使用者(无意或有意地)变得依赖于这样的实现细节

> [!todo] We can use a skill to explain the Transivity

```c++
#include <iostream>

int main() {
	std::cout << "hello world" << std::endl;
	return 0;
}
```

- We can see the file just a print statment with iostream header file

```linux
$ g++ -E test.cc -o test.i
$ cat -10 test.i
1 # 1 "test.cc"                                                             
2 # 1 "<built-in>"
3 # 1 "<command-line>"
4 # 1 "/usr/include/stdc-predef.h" 1 3 4
5 # 1 "<command-line>" 2
6 # 1 "test.cc"
7 # 1 "/usr/include/c++/9/iostream" 1 3
8 # 36 "/usr/include/c++/9/iostream" 3
9 
10 # 37 "/usr/include/c++/9/iostream" 3
11 
12 # 1 "/usr/include/x86_64-linux-gnu/c++/9/bits/c++config.h" 1 3
13 # 256 "/usr/include/x86_64-linux-gnu/c++/9/bits/c++config.h" 3
14 
15 # 256 "/usr/include/x86_64-linux-gnu/c++/9/bits/c++config.h" 3
16 namespace std
// ...
28636 # 2 "test.cc" 2
28637 
28638 
28639 # 3 "test.cc"
28640 int main() {
28641     std::cout << "hello world" std::endl;
28642     return 0;
28643 } 
```

> [!warning] now, you should know clearly why the transitivity is a disadvantage

### 3.2.2 Modules

#Modularity/Modules[[#^quote72]]

```c++
// For C++20, use model to take place the header file
// in Vector.cppm
export module Vector; // defining the module called "Vector"  
  
export class Vector {  
public:  
    Vector(int s);  
    double& operator[] (int i) const;  
    int size() const;  
private:  
    double* elem;  
    int sz;  
};  
  
Vector::Vector(int s): elem {new double[s]}, sz {s} {}  
  
double &Vector::operator[](int i) const {  
    return elem[i];  
}  
  
int Vector::size() const {  
    return sz;  
}  
  
export bool operator== (const Vector& v1, const Vector& v2) {  
    if (v1.size() != v2.size())  
        return false;  
    for (int i = 0; i < v1.size(); i++)  
        if (v1[i] != v2[i])  
            return false;  
    return true;  
}
```

> [!example] The Model Defining Order ^quote72
> 1. 必须将文件命名为 .cppm
> 2. 使用**export**关键字，使得model能够被外部可见，其中**export model**是声明模块
> 3. 里面的每一个函数、类都必须用**export**关键字声明

- This defines a **module** called **Vector**, which exports the class **Vector**, all its member functions, and the non-member function defining operator **\=\=**.

```c++
// The way we use this model we defined
// in Vector.cc
import Vector;  
#include <cmath>  
  
double sqrt_sum(const Vector& v) {  
    double sum = 0;  
    for (int i = 0; i != v.size(); i++)  
        sum += std::sqrt(v[i]);  
    return sum;  
}  
  
int main() {  
    Vector v(5);  
    sqrt_sum(v);  
    return 0;  
}
```

> [!example] The Model Use Order
> 1. import必须在#include的前面
> 2. 通过**import**关键字来引出model

#Modularity/Modules/work[[#^quote73]]

- 头文件与模块的差异不仅仅是在语法上的
	- 模块只会被编译一次(而不是在每一个使用它的翻译单元中编译) -> 解决了重复编译以及臃肿的问题
	- 模块之间能够任意顺序导入，这不会使得先导入的模块影响后导入的模块
	- 如果将某些内容导入或#include进模块中，则使用模块的用户不会隐式地访问(也就是说不会受以下问题的困扰)：**import是不可传递的，也就是说，当你import一个model，不会像include一样一股脑的全部代入，而是你使用什么，引入什么**

> The differences between headers and modules are not just syntactic.
>> A module is compiled once only (rather than in each translation unit in which it is used).
>> Two modules can be **import**ed in either order without changing their meaning.
>> If you **import** or **#include** something into a module, users of your module do not implicitly gain access to (and are not bothered by) that: **import** is not transitive. ^quote73

- **import model**在可维护性和编译时间上的成效是十分显著的，比如：
	- 如果我执行一个程序"Hello World！"，使用**import std**比使用**include \<iostream>** 的编译时间快了十倍不止

> [!bug] Unfortunately, **module std** is not part of C++20.

![[Module model.png]]

> 编译器将模块的接口(由**export**关键字指定)与其实现的详细信息分隔开。因此Vector接口通常由编译器生成，不再由用户显示命名

```c++
#include <iostream>  
#include <vector>  
export module vector_printer;  
  
export template <typename T>  
void print(std::vector<T>& v) { // this is the (only) function seen by users  
    std::cout << "{\n";  
    for (const T& val : v) {  
        std::cout << " " << val << "\n";  
    }  
    std::cout << "}";  
}
```

## 3.3 Namespaces

#Modularity/Namespace[[#^quote74]]

- C++提供了命名空间作为表达某些声明属于一起并且他们的命名不会和其他命名发生冲突的机制

> C++ offers _namespaces_ as a mechanism for expressing that some declarations belong together and that their names shouldn’t clash with other names. ^quote74

```c++
namespace My_code {
	class complex {
		// ...
	};
	int main();
}

int main() {
	reurn My_code::main();
}
```

- 我们可以看见，在**namespace**中的main函数是属于**My_code::** 的，而在外部的main函数，属于**std::** ，因此，他们不会发生冲突。

#Modularity/Namespace/using[[#^quote75]]

- 如果重复限定名称变得乏味或者分散注意力，我们可以使用**using**关键字去声明将该名称纳入范围

> If repeatedly qualifying a name becomes tedious or distracting, we can bring the name into a scope with a _using-declaration_ ^quote75

```c++
void my_code(vector<int>& x, vector<int>& y) {
	using std::swap; // make the standard-library swap available locally
	// ...
	swap(x, y); // std::swap
	ohther::swap(x, y); // some other swap
}
```

- using声明使命名空间中的名称可用，就像在其声明的范围中声明一样

#Modularity/Namespace/namespace[[#^quote76]]

 - 为了访问标准库命名空间中的所有名称，我们可以使用using指明：**using namespace std**

> To gain access to all names in the standard-library namespace, we can use a _using-directive：**using namespace std** ^quote76

```c++
#include <iostream>

using namespace std;

int main() {
	cout << "hello world" << std::endl;
	return 0;
}
```

> [!warning] 重要的是，命名空间声明的使用**不会影响模块的用户(内部)**， 因此using作为了模块本地的实现细节来处理 -> **因此不会使得代码膨胀**

#Modularity/Namespace/weakness[[#^quote77]] 

- 但是，使用**using指明空间**，我们将失去有选择地使用该命名空间中名称的能力，因此需要谨慎使用

> By using a **using**-directive, we lose the ability to selectively use names from that namespace, so this facility should be used carefully ^quote77

## 3.4 Function Arguments and Return Values

#Modularity/Function[[#^quote78]] 

- **将信息从程序中的一个部分传递到另一个部分的主要和推荐的方式是通过函数调用**。执行任务所需要的信息作为参数传递给函数，生成的结果作为返回值传回

> The primary and recommended way of passing information from one part of a program to another is through a function call. Information needed to perform a task is passed as arguments to a function and the results produced are passed back as return values. ^quote78

```c++
int sum(const vector<int>& v) {
	int s = 0;
	for (const int i : v) 
		s += i;
	return s;
}

vector fib = {1, 2, 3, 5, 8, 13, 21};
int x = sum(fib); // x becomes 53
```

- 还有其他途径可以在函数之间传递信息，比如**全局变量和类对象中的共享状态(这将会在第五章讲到)**。**标准中，尽量不要将全局变量作为已知的错误来源，并且状态通常应该仅在联合实现定义良好的抽象的函数之间共享** -> 比如，类的成员函数

#Modularity/Function/type[[#^quote79]]

- 鉴于在函数之间传递信息的重要性，有多种方法可以做到这一点就不足为奇了：
	- 该对象是复制的，还是共享的？
		- -> 复制和共享，分别对应的**传值**和**传地址/引用**
	- 如果该对象是共享的，那么它可变吗？
		- -> **传地址/引用可以通过改变形参的值来对原对象产生影响**
	- 该对象是可移动的，那么移动之后留下来的空对象怎么办？
		- -> 这里涉及到一个知识点：**右值引用和移动的概念**，其将在第六章讲解

> Given the importance of passing information to and from functions, it is not surprising that there are a variety of ways of doing it. 
>> 1. Is an object copied or shared? 
>> 2. If an object is shared, is it mutable?
>> 3. Is an object moved, leaving an “empty object” behind? ^quote79

> [!tip] **参数的传递和值的返回默认行为都是”copide“**，但是很多情况下，”copied“能够隐式优化为**move(移动)**

> [!warning] **如果函数不需要修改参数值，且你使用了引用/指针作为参数，那么请加上const，以const-reference的形式传递**

### 3.4.1 Argument Passing

#Modularity/Argument[[#^quote80]]

- **当我们考虑性能的时候，我们经常在传递比较小的值时使用pass-by-value(值传递)，传递较大的值时使用pass-by-reference(传引用)**

> When we care about performance, we usually pass small values by-value and larger ones by-reference. ^quote80

> [!tip] 这里的"small"，指的是”**复制起来开销很小的东西**“。**"small"的具体含义取决与机器架构**


#Modularity/Argument/default[[#^quote81]]

- 函数参数具有默认值的情况并不少见; 也就是说，被视为首选值或许只是其是最常见的值。

> It is not uncommon for a function argument to have a default value; that is, a value that is considered preferred or just the most common. ^quote81

```c++
void print(int value, int base = 10); // print value in base "base"

print(x, 16); // hexadecimal
print(x, 60); // sexagesimal(Sumerian)
print(x); // use the default: decimal
```

> [!warning] **默认参数只能从右至左， 且中间不能间隔**

```c++
void print(int a, int b, int c = 10); // Ok
void print(int a = 1, int b, int c = 0); // error
void print(int a = 1, int b, int c); // error
```

### 3.4.2 Value Return 

#Modularity/Value[[#^quote82]]

- 只有当我们想要授予调用者访问本地函数内容的权限时，我们才会返回"by reference"

> We return “by reference” only when we want to grant a caller access to something that is not local to the function ^quote82

```c++
double Vector::operator[] (int i) {
	return elem[i];
}
```

> [!bug] 注意：如果你想要用"by reference"的方式返回一个函数内的局部变量，这是不应该的，或者使用”**移动**"来解决这一问题

```c++
int& bad() {
	int x;
	// ...
	return x; // bad: return a reference to the local variable x
}
```

- 但是如果你很想返回一个本地的变量，那么可以使用返回一个指针来解决这件事。**但是，就目前来说，移动构造是最为高效且便捷的方式** -> 而且，返回一个指针需要承担的代价不仅仅如此，为什么C/C++被深恶痛绝，归根结底就是指针的复杂程度，一旦大量使用指针，我们很难发现指针的错误

### 3.4.3 Return Type Deduction

#Modularity/ReurnType[[#^quote83]]

- 一个函数的返回值类型能够从函数的返回值中推导出来

> The return type of a function can be deduced from its return value. ^quote83

```c++
auto nul(int i, double d) { // here, "auto" means "deduce the type"
	return i * d; 
}
```

- 这在很多时候很便利，特别是对于**范型函数(第7章)** 和 **lambda表达式**。 但是也应该谨慎的使用，**因为推导的类型不能提供一个稳定的接口：也就是说，改变函数(或者lambda)的实现可以改变其类型**

### 3.4.4 Suffix Return Type

#Modularity/SuffixType[[#^quote84]]

- 然而，有时我们需要查看参数来确定结果的类型。返回类型推导就是一个例子(但也不是唯一的例子)。
- 我们允许将返回类型添加到参数列表之后，**即我们虚妄显示声明返回值类型的位置**，这也使得"auto"意味着"**返回值类型将在后面提到或者被推导出来**" 

> However, sometimes we need to look at the arguments to determine the type of the result. Return type deduction is one example of that, but not the only one. Consequently, we allow adding the return type after the argument list where we want to be explicit about the return type. That makes **auto** mean “the return type will be mentioned later or be deduced.” ^quote84

```c++
auto mul(int i, double d) -> double {
	return i * d;
}
```

> [!tip] 事实上，现代高级语言(如：Rust，Golang等)都是后置返回类型，由于C++的历史包袱，因此才一直采用了基于C、Fortran等语言的前置声明

### 3.4.5 Structured Binding(C++ 17)

#Modularity/Structured[[#^quote85]]

- 我们都知道，**一个函数只能返回一个值**，但是这个值可以是带有很多成员变量的类对象。这就允许了我们优雅地返回多个值

> A function can return only a single value, but that value can be a class object with many members. This allows us to elegantly return many values. ^quote85

```c++
struct Entry {  
    std::string name;  
    int value;  
};  
  
auto read_entry(std::istream& is) -> Entry {  
    std::string str;  
    int i;  
    is >> str >> i;  
    return {str, i};  
}  
  
auto e = read_entry(std::cin);
```

- 我们可以看到，通过结构体能够实现多个值的返回，e通过索引：**e.name or e.value**就能够获取到返回的值

> [!tip] 但是，C++ 17中，给我们提供了一种类似“解包”的概念 -> (事实上，包括Python、Rust等语言早已支持)

```c++
auto [str, v] = read_entry(std::cin);
```

- **auto [str, v]声明了两个局部变量str，v，他们的类型是从read_entry()中的返回类型推导出来的。这种为类对象成员变量提供了局部变量的机制叫做 -> Structured Binding(结构化绑定)**

```c++
auto incr(std::map<std::string, int>& m) {  
    for (auto& [key, value] : m) {  
        ++value;  
    }  
}
```

#Modularity/Structured/work[[#^quote86]]

- 当结构化绑定用于没有私有数据的类时，很容易看出绑定是如何完成的：**为绑定定义的变量的数量必须和类对象中的成员变量数量相同，且绑定中引入的每个变量都为相应的成员命名** -> 也就是说，通过数量相同的局部变量来接受，其类型由编译器自动推导

> When structured binding is used for a class with no private data, it is easy to see how the binding is done: there must be the same number of names defined for the binding as there are data members in the class object, and each name introduced in the binding names the corresponding member. ^quote86

> [!tip] 特别的，结构化绑定和显式的使用复合对象(m.member)相比，**代码的效率和质量上是没有任何差距的**。特别是，使用结构化绑定不意味着“copy”了结构体。反而，**简单结构提的返回很少涉及到“copy”，因为简单返回类型可以直接在需要他们的位置构造。**

- 在A tour of C++ 3rd中，有着：A **complex** has two data members, but its interface consists of access functions, such as **real()** and **imag()**. Mapping a **complex\<double\>** to two local variables, such as **re** and **im** is feasible and efficient, but the technique for doing so is beyond the scope of this book.

> **可能是我理解有误，我无法通过上述所说：“使用类中的成员函数访问器 real()和imag()来实现对私有成员的绑定。查阅资料后，找到了另一种实现方法，但是比较复杂”**

```c++
template <typename T>  
class complex;  
  
template<>  
class std::tuple_size<complex<double>>  
    : public std::integral_constant<size_t, 2> {};  
  
template <>  
class std::tuple_element<0, complex<double>> {  
public:  
    using type = double;  
};  
  
template <>  
class std::tuple_element<1, complex<double>> {  
public:  
    using type = double;  
};  
  
template <typename T>  
struct complex {  
    complex(T _re, T _im): re {_re}, im {_im} {}  
    complex<T>& operator+ (T d) {  
        this->re += d;  
        return *this;  
    }  
public:  
    template<size_t Index>  
    std::tuple_element_t<Index, complex<double>> &get() &;  
private:  
    T re;  
    T im;  
};  
  
template<> template <>  
std::tuple_element_t<0, complex<double>> &complex<double>::get<0>() & {  
    return re;  
}  
  
template <> template <>  
std::tuple_element_t<1, complex<double>> &complex<double>::get<1>() & {  
    return im;  
}

complex<double> z = {1, 2};  
auto& [re, im] = z + 2; // use it, the re become 3, and im is still 2
std::cout << re << " " << im << "\n";
```

> [!todo] 想要实现上述代码逻辑，首先使用std::tuple -> 特化tuple_size和tuple_element，但由于现在还没学，无法进行讲解，只能看后续学到后，再返回来解决

# 4. Error Handling

## 4.1 Introduction

#ErrorHanding/Introduction[[#^quote87]]

-  **错误处理是一个庞大而复杂的主题，其关注点和影响都远远超出了语言设施本身，而涉及到编程技术和工具**。然而，C++提供了一些功能来帮助，其主要工具是类型系统本身。

> Error handling is a large and complex topic with concerns and ramifications that go far beyond language facilities into programming techniques and tools. However, C++ provides a few features to help. The major tool is the type system itself. ^quote87

- 我们不需要费力地再从内置类型和语句中构建应用程序，而是构建适合我们程序的类型(**例如STL库中都string、map和算法sort()、find_if()等**)。这样的高级构造简化了我们都变成，限制了我们出错的机会，并且增加了编译器捕获错误的机会。**大多数C++语言构造都致力于设计和实现优雅高效的抽象，而使用这一种抽象都效果是：可以检测到运行时错误都点和可以处理错误都点是分开都**

## 4.2 Exceptions

#ErrorHanding/Exceptions[[#^quote88]]

- 假定超出范围的访问是一种我们希望从中恢复的错误，其解决方案是让Vector实现者检测尝试超出范围的访问并且告知用户，然后用户可以采取适当的操作去解决这个问题。

> Assuming that out-of-range access is a kind of error that we want to recover from, the solution is for the **Vector** implementer to detect the attempted out-of-range access and tell the user about it. The user can then take appropriate action. ^quote88

```c++
double& Vector::operator[] (int i) {
	if (!(0 < i && i < size()))
		throw out_of_range {"Vector::operator[]"};
	return elem[i];
}
```

- **throw**将控制转移到某个直接或间接调用Vector::operator\[\]()的函数中的out_of_range类型异常的处理程序。**为此，实现将根据需要展开函数调用堆栈，以返回调用方的上下文。也就是说，异常处理机制将根据需要退出作用域和函数，以返回对处理此类异常表示兴趣的调用方，并根据需要调用析构函数**

```c++
#include "Vector/Vector.h"  
  
void f(Vector& v) {  
    try { // out_of_range exception thrown in this block are handle by the handle define below  
        // computer 1... might try to access beyond the end of v        
        double a = v[7]; // might try to access beyond the end of v  
        // computer 2... might try to access beyond the end of v    
    }catch (const std::out_of_range& exception) {  
        std::cerr << exception.what() << "\n";  
    }  
}  
  
int main() {  
    Vector v(5);  
    f(v);  
    return 0;  
}
```

- 我们将可能出现异常的代码放入”**try-block**“语句中，对compute1、compute2,以及中间的v\[7\]的调用表示了**那些不容易提前确定是否发生"cou_of_range"错误的代码。”catch“子句用于处理"out_of_range“类型的异常(但是事实上，catch可用于处理任何可捕获的异常)。**

> [!tip] 如果在f()中处理异常起来很麻烦，那我们就不要在f()中使用"**try-block**"，而是让异常隐式传递给f()的调用者

#ErrorHanding/Exceptions/define[[#^quote89]]

- **out_of_range**类型是在标准库中定义的(**\<stdecept\>**)，实际上被一些标准库容器访问函数使用
- 通过引用捕获异常以避免复制，并使用**what()** 函数在抛出点打印放入其中的错误信息

> The **out_of_range** type is defined in the standard library (in **\<stdexcept\>**) and is in fact used by some standard-library container access functions.
> I caught the exception by reference to avoid copying and used the **what()** function to print the error message put into it at the **throw**-point. ^quote89

- 使用异常处理机制可以使错误处理变得更简单、更系统、更可读。要做到这一点，**就不能过度使用try语句。** 在许多程序中，**抛出和可以处理抛出异常的函数往往有几十个函数的调用**。因此，大多数函数应只允许异常在调用堆栈中传播。

> [!tip] 在后面第五章中，解释了使用错误处理变得更简单和系统都主要技术(称为**Resource Acquisition Is Initialization(资源获取即初始化RAII)**)。RAII背后的基本思想是让构造函数获取类操作所需要的资源，并让析构函数释放所有资源，从而使资源释放得到保证和隐蔽

## 4.3 Invariants

#ErrorHanding/Invariants[[#^quote90]]

- 使用异常来表示超出范围的访问是一个函数检查其参数并拒绝执行都例子，因为基本假设(前提条件)不成立

> The use of exceptions to signal out-of-range access is an example of a function checking its argument and refusing to act because a basic assumption, a _precondition_, didn’t hold. ^quote90

- 每当我们定义一个函数时，我们都应该考虑它的前提条件是什么，并且考虑是否测试它们。对于大多数应用程序来说，测试简单的不变量是个好注意(参见第四章五小节)。
- 就比如上述的**Vector::operator[] ()**，对于该函数来说，我们应该明确的知道其下标访问的范围应该是**\[a, b)** ，也就是说，a在其范围内，而b不在

#ErrorHanding/Invariants/define[[#^quote91]]

- 特别是，我们确实说了"**elem指向类型为双精度浮点数组sz**"，但是我们只是在注释中(或者说，我们的脑海中)说了这一点。对于一个类，这种假定为**True**的表述称为类不变式，或者简单称为不变式。

> In particular, we did say “elem points to an array of sz doubles” but we only said that in a comment. Such a statement of what is assumed to be true for a class is called a class invariant, or simply an invariant. ^quote91

- **构造函数的工作是为其类建立不变量(以便成员函数可以依赖它)，并确保成员函数在退出时保持不变量。** 不幸的是，在上述的Vector构造函数中只完成了部分工作，其确切地初始化了Vector成员，但是没有检查传递给它的参数是否有意义。

```c++
Vector v(-27);

Vector::Vector(int s) {  
    if (s < 0)  
        throw std::length_error {"Vector constructor: negative size"};  
    if ((elem = new double[s]) == nullptr)  
        throw std::bad_alloc {};  
    sz = s;  
}

void test(int n) {  
    try {  
        Vector v(n);  
    }catch (const std::length_error& exception) {  
        std::cerr << exception.what();  
    }catch (const std::bad_alloc& exception) {  
        std::cerr << exception.what();  
    }  
}

test(-27); // throws length_error (-27 is too small)  
test(10'0000'0000); // may throw bad_alloc  
test(10); // likely OK
```

- 如果你请求的内存多于计算机提供的内存，或者程序已经消耗了绝大部分内存，然后你再次请求内存 -> 导致了消耗的内存超出了限制，则会发生内存耗尽。**但是注意，现代操作系统内存一次容纳的更多的空间，因此请求过多内存可能会导致在“bad_alloc”之前很久就严重变慢**

#ErrorHanding/Invariants/exception[[#^quote92]]

- 通常，一个函数在发生异常被抛出后无法继续执行其分配的任务。“**处理**”异常意味着执行一些最小的本地清理并重新抛出异常

> Often, a function has no way of completing its assigned task after an exception is thrown. Then, “handling” an exception means doing some minimal local cleanup and rethrowing the exception. ^quote92

- 在设计良好的代码中，“**try-block**”其实很少使用。通过系统地使用RAII技术来避免过度使用。而不变式的概念是类设计的核心，前提条件在函数设计中扮演着类似的角色：
	- 制定不变式有利于我们准确地理解我们想要什么
	- 不变式使我们具体化，这给了我们更好的机会使代码更好 -> **不变式要求我们，要对constructor考虑完善，这直接的使得代码变得严谨**

## 4.4 Error-Handing Alternatives

#ErrorHanding/Alternative[[#^quote93]]

- 错误处理是所有实际软件中的一个主要问题，因此，有很多方法来解决。如果检测到错误无法在函数内部处理，那么该函数就必须以某种方式将问题传递给某个调用方。**抛出异常是C++最通用的错误处理机制**

> Error handling is a major issue in all real-world software, so naturally there are a variety of approaches. If an error is detected and it cannot be handled locally in a function, the function must somehow communicate the problem to some caller. Throwing an exception is C++’s most general mechanism for that. ^quote93

- 异常被设计用于报告完成给定任务的失败。异常与构造函数和析构函数集成在一起，为错误处理和资源管理提供了一致的框架。

#ErrorHanding/Alternative/code[[#^quote94]]

- 编译器经过优化后，使得返回值比抛出相同都值作为异常的代价更小

> Compilers are optimized to make returning a value much cheaper than throwing the same value as an exception. ^quote94

- 抛出异常并不是报告无法在函数内部处理错误的唯一方法。函数也可以通过如下方式说明其无法完成分配的任务：
	- 抛出异常
	- 以某种方式返回一个表示失败的值
	- 终止程序(通过调用terminate()、exit()或者abort()等函数)
- 而我们在以下情况返回错误指示器(“**error code**”)：
	- 该失败是能够预见和正常的 -> 例如，请求打开一个文件，则失败是很正常的(无权限或无该文件)
	- 希望调用方合理且立即地处理预期中的错误 -> 例如：某个输入值有误，重新输入
	- 一组并行任务中的其中一个发生了错误，我们需要知道哪一个发生了错误 -> 例如，游戏的几个选项，第一个失败返回1,第二个失败返回2...
	- 系统的内存太少，以至于运行时对异常的支持会挤占基本功能
- 而我们会在以下情况抛出异常：
	- 这种错误不常见导致程序员很有可能会忘记检查 -> 例如，你经常检查printf()的返回值吗？
	- 直接调用方无法处理错误。相反，必须将调用链渗透到“最终调用方” -> 如果你用过模板或者python，甚至java的话。**反复检查错误代码将很乏味、昂贵且容易出错。错误测试和将错误代码作为返回值传递很容易掩盖函数的主要逻辑**
	- 错误代码没有可用的返回路径 -> 最常见的，构造函数没有返回值，想要处理就只能使用异常
	- 函数的返回需要同时传递值和错误知识符(例如，pair), 可能导致使用外参数、非本地错误状态指示器或者其他变通方法
	- ...
- 而我们会在以下情况直接终止程序：
	- 该错误是一种我们无法修复的错误 -> 例如，内存耗尽对于绝大部分系统都没有合理的方法解决
	- 该系统的错误处理基于每当检测到重大错误时就会重新启动线程、进程甚至计算机

#ErrorHanding/Exceptions/noexcept[[#^quote95]]

- 确保终止的一种方法是将**noexcept**添加到函数中，使得该函数实现中任何地方的抛出都会变为**terminate()**

> One way to ensure termination is to add **noexcept** (§[4.5.3](file:///OEBPS/ch04.xhtml#sec4_5_3)) to a function so that a **throw** from anywhere in the function’s implementation will turn into a **terminate()**. ^quote95

> [!warning] 注意：有些应用程序不接受无条件终止，因此必须使用一种代替方案。用于常规用途的库都不应无条件终止

- **不要认为所有的错误代码和异常都是坏的，他们都有着明确的用途。此外，也不要认为异常处理缓慢的传闻，它通常比正确处理复杂或罕见的错误条件以及重复测试错误代码更快**

## 4.5 Assertions

#ErrorHanding/Assertions[[#^quote96]]

- 目前还没有编写不变式、前提条件等可选运行时测试的通用标准方法。然而，对于许多大型程序，又需要支持那些希望在测试时依赖大量运行时检查，且使用最小检查部署代码的用户

> There is currently no general and standard way of writing optional run-time tests of invariants, preconditions, etc. However, for many large programs, there is a need to support users who want to rely on extensive run-time checks while testing, but then deploy code with minimal checks. ^quote96

- 因此，我们不得不依靠临时机制。有很多这样的机制，并且它们灵活而通用，在未启动时意味着没有成本。

```c++
enum class Error_action { // error-handing alternatives  
    ignore,  
    throwing,  
    terminating,  
    logging  
};  
  
// a default  
constexpr Error_action default_Error_action = Error_action::throwing;  
  
enum class Error_code {  
    range_error,  
    length_error  
};  
  
std::string error_code_name[] {"range error", "length error"};  
  
template <Error_action action = default_Error_action, class C>  
constexpr void except(C cond, Error_code x) { // take "action" if the expected condition "cond" doesn't hold  
    if constexpr (action == Error_action::logging)  
        if (!cond())  
            std::cerr << "expect() failure: " << int(x) << ' ' << error_code_name[int(x)] << "\n";  
  
    if constexpr (action == Error_action::throwing)  
        if (!cond())  
            throw x;  
  
    if constexpr (action == Error_action::terminating)  
        if (!cond())  
            std::terminate();  
}
```

- 乍一看，这似乎令人难以置信，因为使用的许多语言功能还为体现出来。然而，**它确实十分灵活又易于使用**

```c++
double &Vector::operator[](int i) {  
    except(
	    [i, this]() -> bool { return 0 <= i && i < size(); }, 
	    Error_code::range_error
	);  
    return elem[i];  
}
```

- 可以看见上面的代码，检查下标是否在合法范围内，如果不在则采取默认操作**default_Error_action**抛出异常。而期望保持的条件，作为lambda表达式传递给expect()。**if constexpr在编译期完成，因此每次调用expect()最多执行一次运行时测试**。若将action设置为**Error_action::ignore**，则不会采取任何操作。

> [!fail] **在许多系统中，断言机制(如expect())，提供对断言失败含义的单点控制非常重要。但是，在大型代码库中，搜索真正检查假设的if语句是不切实际的**

### 4.5.1 assert()

#ErrorHanding/Assertions/assert[[#^quote97]]

- 在标准库中提供了调试宏：assert()，用于断言一个条件必须在运行时保持

> The standard library offers the debug macro, **assert()**, to assert that a condition must hold at run time. ^quote97

```c++
void f(const char* p) {
	assert(p != nullptr); // p must not be nullptr
}
```

- 如果assert()的条件在“debug”下失败，程序会被中止。**但如果是在“release”下，却又不检查assert()**。**这是十分粗糙且暴力的，但是有总比没有好，不是吗**

### 4.5.2 Static Assertions

#ErrorHanding/Assertions/static_assert[[#^quote98]]

- **异常报告通常在运行时发现错误，如果该错误能在编译期就被发现，这显然会更好**。所以，这就是类型系统和用于指定用户定义类型接口的工具的主要用途。当然，我们也可以对编译时已知的大多数属性执行简单检查，并将失败信息报告给编译器，以满足我们我们的期望

> Exceptions report errors found at run time. If an error can be found at compile time, it is usually preferable to do so. That’s what much of the type system and the facilities for specifying the interfaces to user-defined types are for. However, we can also perform simple checks on most properties that are known at compile time and report failures to meet our expectations as compiler error messages. ^quote98

```c++
static_assert(4 <= sizeof(int), "integers are too small");
```

- 在此处，我们使用**static_assert(静态断言)**来断言**int**的大小。而**static_assert机制可用于任何用常量表达式表示的东西**

```c++
constexpr double C = 299792.458;

void f(double speed) {
	constexpr double local_max = 160.0 / (60 * 60); // 160 km/h == 160.0 / (60 * 60)
	static_assert(speed < C, "can't go that fast"); // error, the speed must be a constexpr
	static_assert(local_max < C, "can't go that fast"); // OK
}
```

> [!tip] 当然，你也可以不需要自定义消息，使用编译器默认提供的错误信息 -> 错误源位置 + 断言谓词的字符表示形式。**而static_assert的一个重要作用就是对泛型编程中用作参数的类型进行断言** -> 这会在第八章和第十六章提到

### 4.5.3 noexcept

#ErrorHanding/Assertions/noexcept[[#^quote99]]

- 一个函数如果不应该抛出异常就需要声明为**noexcept**

> A function that should never throw an exception can be declared **noexcept**. ^quote99

```c++
void user(int sz) noexcept {
	Vector v(sz);
	itoa(&a[0], &a[sz], 1); // fill v with 1, 2, 3, ..
}
```

- 如果我们为该代码设计的所有良好的意图和计划都失败了，user()仍然会抛出异常，那么就让其调用**std::terminate()**立即终止程序

#ErrorHanding/Assertions/danger[[#^quote100]]

** 如果你不假思索地在函数上添加了**noexcept**功能，这是相当危险的。如果**noexcept**函数调用了一个会抛出异常的函数，并且希望其能捕获并处理该异常，而由于**noexcept**的存在，会将其转化为一个致命错误从而迫使编译器通过某种形式的错误代码来处理错误，而这种错误可能是复杂的、容易出错的和开销巨大的。**noexcept应该清晰和谨慎地使用**

> Thoughtlessly sprinkling **noexcept** on functions is hazardous. If a **noexcept**function calls a function that throws an exception expecting it to be caught and handled, the **noexcept** turns that into a fatal error. Also, **noexcept** forces the writer to handle errors through some form of error codes that can be complex, error-prone, and expensive. Like other powerful language features, **noexcept** should be applied with understanding and caution. ^quote100

