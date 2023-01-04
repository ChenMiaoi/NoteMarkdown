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

> The size of a type is implementation-defined (i.e., it can vary among different machines) ^quote19

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

# 5. Classes

## 5.1 Introduction

- 略

### 5.1.1 Classes

#Class/Introduction/classes[[#^quote101]]

- C++的核心语言特征是**class**。**class**是用户自定义的类型，用于表示程序代码中的实体。

> The central language feature of C++ is the _class_. A class is a user-defined type provided to represent an entity in the code of a program. ^quote101

- 每当我们的程序设计有一个有用的想法、实体、数据集合等时，我们都会尝试将其表示为程序中的一个类，以便该想法在代码中体现，而不仅仅是在我们的头脑、设计文档甚至一些注释中。

> [!tip] **由一组精心挑选的类构建的程序比直接根据内置类型构建所有内容的程序更容易理解和正确**。特别是，类通常是库提供的。

## 5.2 Concrete Type

#Class/ConcreteType[[#^quote102]]

- 具体类的基本思想就是**它们的行为“就像内置类型一样”**

> The basic idea of _concrete classes_ is that they behave “just like built-in types.” ^quote102

- 例如：复数类型和无限精度整数很像内置类型的“int”， 当然，它们有着自己的语义和运算集。类似的，**vector**和**string**很想内置数组，只是他们更灵活，行为更好

#Class/ConcreteType/work[[#^quote103]]

- **具体类型的定义特征是其表示定义的一部分**。

> The defining characteristic of a concrete type is that its representation is part of its definition. ^quote103

- 在很多情况下，例如**vector**，**该表示只是存储在其他地方数据的一个或多个指针，但该表示存在于具体类的每个对象中。这允许实现在空间和时间上达到最佳效率**。
- 并且，其允许：
	- 将具体类型的对象放置在堆栈上、静态分配的内存中或者其他对象中
	- 直接引用对象(**而不仅仅是通过指针或者引用**)
	- 立即完整地初始化对象
	- 拷贝或者移动对象
- 且该表示可以是私有的，并且只能通过成员函数访问(**但其必须是存在的**)。因此，**如果表示形式有任何重大变化，用户必须重新编译。这是让具体类型的行为和内置类型完全相同所需要付出的代价**。对于不经常变化的类型，使用局部变量提供必须的清晰度和效率，这是可以接受的，并且通常是很理想的。**为了增加灵活性，具体类型可以将其表示的主要部分保存在自由存储区(动态内存、堆)上，并通过存储在类对象本身中的部分来访问它们**。这也是**vector**和**string**的实现方式。

### 5.2.1 An Arithmetic Type

```c++
class complex {  
public:  
    complex(double re, double im): _re {re}, _im {im} {}  
    complex(double re): _re {re}, _im {0} {}  
    complex(): _re {0}, _im {0} {}  
    complex(const complex& z): _re {z._re}, _im {z._im} {}  
public:  
    double real() const { return _re; }  
    double imag() const { return _im; }  
    void real(double re) { _re = re; }  
    void imag(double im) { _im = im; }  
public:  
    complex& operator+= (complex z) {  
        _re += z._re;  
        _im += z._im;  
        return *this;  
    }  
    complex& operator-= (complex z) {  
        _re -= z._re;  
        _im -= z._im;  
        return *this;  
    }  
    complex& operator*= (complex z);  
    complex& operator/= (complex z); 
    complex operator+ (complex z) {  
    complex temp = *this;  
	    return temp += z;  
	}  
	complex operator- (complex z) {  
	    complex temp = *this;  
	    return temp -= z;  
	}  
	complex operator* (complex z) {  
	    complex temp = *this;  
	    return temp *= z;  
	}  
	complex operator/ (complex z) {  
	    complex temp = *this;  
	    return temp /= z;  
	}  
	bool operator== (complex z) { return this->real() == z.real() && this->imag() == z.imag(); }  
	bool operator!= (complex z) { return !(*this == z); } 
private:  
    double _re;  
    double _im;  
};
```

#Class/ConcreteType/complex[[#^quote104]]

- 除了逻辑需求之外，**complex必须是有效的**，否则其将不会被使用。**这意味着简单操作必须“inline”。也就是说，生成的机器代码中，必须在没有函数调用的情况下实现简单操作(例如构造函数，+=和imag())。默认情况下，类中定义的函数是“inline”的。**
- 通过在函数声明前加关键字**“inline”**，可以显示请求内联。

> In addition to the logical demands, complex must be efficient or it will remain unused. This implies that simple operations must be inlined. That is, simple operations (such as constructors, +=, and imag()) must be implemented without function calls in the generated machine code. Functions defined in a class are inlined by default. It is possible to explicitly request inlining by preceding a function declaration with the keyword inline. An industrial-strength complex (like the standard-library one) is carefully implemented to do appropriate inlining. ^quote104

> [!tip] 我们知道，**C++允许类实现类似于内置类型的操作。但是这些操作一般都很简短且经常重复使用。** **而将这些函数定义为“inline”之后，以牺牲空间的方式来节省函数调用的开销** -> 也就是说，这样更接近于内置类型的普通操作

- **拷贝赋值和拷贝构造都是隐式定义的**
- **无需参数即可调用的构造函数被成为默认构造函数**。通过默认构造函数，能够使得类型未初始化的情况不再发生
- **const说明符表示这些函数不会修改其调用的对象。** 可以为const和非const对象调用const成员函数，**但是只能由非const对象调用非const成员函数**

```c++
complex z = {1, 0};
const complex cz {1, 3};
z = cz;    // OK: assigning to a non-const variable
cz = z;    //  error: assignment to a const
double x = z.real();  // OK: complex::real() is const
```

- **编译器将涉及到的运算转化为适当的函数调用**。例如：c != b表示c.operator!= (b)
- 用户定义的运算符(**"重载运算符"**)应该谨慎使用。**重载运算符语法由语言固定，因此不能定义“一元/”。此外，也无法更改内置类型运算符的含义。**

### 5.2.2 A Container

#Class/ConcreteType/container[[#^quote105]]

- 容器是保存元素集合的对象

> A _container_ is an object holding a collection of elements. ^quote105

#Class/ConcreteType/destructor[[#^quote106]]

- 在很多类中都有一个致命的缺陷：使用**new**分配元素，但从不释放它们(分配的空间)。这不是一个好注意，因为C++没有提供垃圾收集器来为新对象提供未使用的内存。在某些环境中，你不能使用收集器，并且处于逻辑或者性能的原因，你通常更喜欢更精确地控制销毁。因此，**我们需要一种机制来确保由构造函数分配的内存被释放，该机制是析构函数**

> However, it does have a fatal flaw: it allocates elements using **new** but never deallocates them. That’s not a good idea because C++ does not offer a garbage collector to make unused memory available for new objects. In some environments you can’t use a collector, and often you prefer more precise control of destruction for logical or performance reasons. We need a mechanism to ensure that the memory allocated by the constructor is deallocated; that mechanism is a _destructor ^quote106

```c++
class Vector {
public:
	Vector (int s): elem {new double[s]}, sz {s} {
		for (int i = 0; i != s; i++)
			elem[i] = 0;
	}
	~Vector () { delete[] elem; }
	double& operator[] (int i);
	int size() const;
private:
	double* elem;
	int sz;
}
```

> [!tip] 析构函数前面是**\~**，其名字和类名一致

```c++
Vector gv(10); // global variable; gv is destroyed at the end of program

Vector* gp = new Vector(100); // Vector on free store; never implicitly destroyed

void fct(int n) {
	Vector v(n);
	// ...use v
	{
		Vector v2(2 * n);
		// ...use v and v2
	} // v2 is destroyed here
	// ...use v
} // v is destroyed here 
```

- **类在命名、作用域、分配、生存期等方面遵循与内置类型同样的规则**。

#Class/ConcreteType/RAII[[#^quote107]]

- 在构造函数中获取资源并在析构函数中释放它们的技术称为资源获取即初始化(**Resource Acquisition Is Initialization(RAII)**)

> The technique of acquiring resources in a constructor and releasing them in a destructor, known as _Resource Acquisition Is Initialization_ or _RAII_. ^quote107

- RAII允许我们消除 **“单独的new操作”**，也就是说，避免在一般代码中进行分配，并将其隐藏在行为良好的抽象实现中。同样，应该避免 **“单独的delete操作”**。避免单独的new和delete使代码更不容易出错，更容易避免资源泄漏。

### 5.2.3 Initializing Containers

#Class/ConcreteType/initialize[[#^quote108]]

- 容器的存在是为了容纳元素，所以显然我们需要更方便的方法来将元素放入容器中
	- initializer-list consturctor：initialize with a list of elements
	- push_back()

> A container exists to hold elements, so obviously we need convenient ways of getting elements into a container. ^quote108

```c++
class Vector {
public:
	Vector(); // default
	Vector(std::initializer_list<double>); // initialize with a list
	// ...
	void push_back(double); // add element at end
}
```

- 对于**push_back**来说，在最后插入一个任意的数是很轻松的

```c++
Vector read(std::istream& is) {
	Vector v;
	for (double d; is >> d; )
		v.push_back(d);
	return v;
}

Vector v = read(std::cin);
```

- 对于上述案例来说，返回一个Vector的代价可能是非常巨大的，但是我们可以通过**move construtor**来解决，这需要在后面才会有所体现。
- 同时，用于**initializer-list constructor(初始化列表构造)**的 **std::initializer_list**是编译器已知的标准库类型：当我们使用**{}-list**时，编译器将创建一个**initializer_list**对象提供给程序

```c++
Vector v1 = {1, 2, 3, 4, 5}; 
Vector v2 = {1.23, 3.45, 6.7, 8};
```

- 而初始化构造函数可以像这样写：

```c++
Vector::Vector(std::initializer_list<double> lst)
	: elem {new double[lst.size()]}
	, sz {static_cast<int>(lst.size())} {
	std::copy(lst.begin(), lst.end(), elem);	
}
```

> [!tip] 不幸的是，标准库使用**“unsigned int”**作为大小和下标，因此我们需要使用**static_cast**将初始化设定项列表的大小显示转化为int。 -> 事实上，这样的操作很丑陋且迂腐，因为你手写列表中的元素大于最大整数的可能性相当低(16位整型是32767, 32位整型是2147483647)

- 但是，类型系统没有常识。他知道变量的可能值，而不是实际值，**所以它可能会在没有实际违反的地方报错**。这个的警告有时可以使程序员避免出现严重错误。

#Class/ConcreteType/cast[[#^quote109]]

- **static_cast**不检查它正在转换的值。程序员可以正确地使用，但是**这并不总是一个好的假设，所以如果对其有疑惑，就需要检查**。显示类型转换(通常称为类型转换，以提醒你使用他们支撑“损坏”的内容)。尝试仅对系统的最低级别使用未检查的强制转换。**他们很容易出错**

> A **static_cast** does not check the value it is converting; the programmer is trusted to use it correctly. This is not always a good assumption, so if in doubt, check the value. Explicit type conversions (often called _casts_ to remind you that they are used to prop up something broken) are best avoided. Try to use unchecked casts only for the lowest level of a system. They are error-prone. ^quote109

- 其他的类型强制转换包括**reinterpret_cast**和**bit_cast**，用于将对象简单地视为字节序列，以及**const_cast**用于“强制转换const”。明智的使用类型系统和设计良好的库允许我们在高级软件中消除未经检查的强制转换

- for **const_cast**
```c++
// we all konw C string is a const char*
string str = "hello";
char* const_str = str.c_str(); // error: str.c_str() is a const char*
char* non_const_str = const_cast<char*> (str.c_str()); // OK, const_cast<char*> conversion the char* to const
```

- for **static_cast**
```c++
int x = 0;
double x1 = static_cast<double> (x);
```

- for **reinterpret_cast**
```c++
int* x = new int(10);
double* x1 = reinterpret_cast<double*> (x);
```

- 注意：**reinterpret_cast**能够实现毫无关系的指针进行转换。

## 5.3 Abstract Types

#Class/AbstractType[[#^quote110]]

- 诸如**complex**和**Vector**之类的类型被称为具体类型，因为它们的表示是其定义的一部分。在这方面，它们类似于内置类型。相反，抽象类型是将用户与实现细节完全隔离的类型。为此，我们将接口与表示分离，并放弃真正的局部变量。由于我们对抽象类型的表示一无所知(甚至不知道其大小)，我们必须在自由存储区上分配对象，并通过引用或者指针访问它们。

> Types such as **complex** and **Vector** are called _concrete types_ because their representation is part of their definition. In that, they resemble built-in types. In contrast, an _abstract type_ is a type that completely insulates a user from implementation details. To do that, we decouple the interface from the representation and give up genuine local variables. Since we don’t know anything about the representation of an abstract type (not even its size), we must allocate objects on the free store and access them through references or pointers ^quote110

```c++
class Container {  
public:  
    virtual double& operator[] (int) = 0; // pure virtual function  
    virtual auto size() -> int const = 0; // const member function  
    virtual ~Container() {} // destructor  
};
```

- 该类是稍后定义的特定容器的纯接口。**“virtual”** 关键字的意义是 **“以后可以在此类派生的类中重新定义”**。当然的，声明为**virtual**的函数称为**虚函数**。从**Container**派生的类提供了**Container**接口的实现。而 **=0**的语法表示该函数是纯虚的，也就是说**Container的派生类必须定义的函数。被称为纯虚函数**。因此，不可能定义仅为**Container**的对象

```c++
Container c; // error: there can be no objects of an abstract class
Container p = new Vector_container(10); // OK: Container is an interface for Vector_container
```

> [!tip] 具有纯虚函数的类被称为抽象类

```c++
void use(Container& c) {
	const int sz = c.size();
	for (int i = 0; i != sz; i++)
		std::cout << c[i] << "\n";
}
```

- 此时，我们并不清楚c使用的size()和\[\]是哪一种类型提供了实现。**为各种其他类提供接口的类通常称为多态类型(polymorphic type)**

- 同时，作为一个通用的抽象类，**Container**没有构造函数(也就是说，不需要自行定义)。毕竟，它没有任何要初始化的数据。另一方面，容器有一个析构函数，但是该析构函数是**virtual**的，因此**Container**的派生类可以提供实现。

> [!warning] 抽象类一般只提供出接口，而非具体的实现

```c++
class Vector_container: public Container { // Vector_container implements  
public:  
    Vector_container(int s): v(s) {} // Vector of s elements Container  
    ~Vector_container() {}  
  
    double& operator[] (int i) override { return v[i]; }  
    auto size() -> int const override { return v.size(); }  
private:  
    Vector v;  
};
```

- 对于**Container**和**Vector_container**通常被称为**base(基类)** 和 **dervied(派生/衍生类)** 或者**superclass(超类)** 和 **subclass(子类)**。
- **override**关键字显示的声明了哪一些接口是需要重写的。**override**的使用是可选的，如果显示的声明了，那么编译器就会捕获错误，例如函数名的拼写错误或者虚函数的类型细微差异等等。

> [!bug] 注意：**析构函数子类覆盖了基类的析构函数。而子类的析构函数默认隐式调用父类析构函数，如果你显式调用了，反而会出现预料之外的错误**

## 5.4 Virtual Function

```c++
void use(Container& c) {
	const int sz = c.size();
	for (int i = 0; i != sz; i++)
		std::cout << c[i] << "\n";
}
```

#Class/Virtual/vbtl[[#^quote111]]

- 在使用use()函数时，如何确定C的类型以及调用正确的函数是尤为关键的。要实现该解决方案，**Container**对象必须包含其在运行时选择要调用的正确函数的信息。**通常实现技术是编译器将虚函数的名称转化为指向函数的指针表的索引。该表通常称为vtbl来标识其虚函数**

> How is the call **c[i]** in **use()** resolved to the right **operator[]()**? When **h()** calls **use()**, **List_container**’s **operator[]()** must be called. When **g()** calls **use()**, **Vector_container**’s **operator[]()** must be called. To achieve this resolution, a **Container** object must contain information to allow it to select the right function to call at run time. The usual implementation technique is for the compiler to convert the name of a virtual function into an index into a table of pointers to functions. That table is usually called the _virtual function table_ or simply the **vtbl**. Each class with virtual functions has its own **vtbl** identifying its virtual functions. ^quote111

![[Virtual-vbtl.png]]

- **vbtl中的函数允许正确使用对象，即使调用方不知道对象的大小及其数据布局，调用者的实现只需要知道容器中vbtl指针的位置以及每个虚函数所使用的索引。这种虚拟调用机制的效率几乎与正常函数调用机制一样高(在25%以内，对同一对象的重复调用开销要小得多)。它的空间开销是具有虚拟函数的类的每个对象中的一个指针加上每个此类的一个vbtl**

## 5.5 Class Hierarchies

#Class/hierarchies[[#^quote112]]

- 类层次结构是在通过派生类创建的网格中有序排列的一组类。我们使用类的层次结构来表示具有层次关系的概念

> A _class hierarchy_ is a set of classes ordered in a lattice created by derivation (e.g., **: public**). We use class hierarchies to represent concepts that have hierarchical relationships ^quote112

![[Class Hierarchies.png]]

- 箭头表示继承关系。例如：类Circle派生自类Shape。类层次结构通常从最基本的类(根)向下绘制，向(后来定义的)派生类增长

- 我们先定义出所有类型的常规属性

```c++
class Point {  
public:  
    double x;  
    double y;  
};  
  
class Shape {  
public:  
    virtual Point center() const = 0; // pure virtual  
    virtual void move(Point to) = 0;  
  
    virtual void draw() const = 0;  
    virtual void rotate(int angle) = 0;  
  
    virtual  ~Shape() {}  
};
```

- 然后定义一个特定的形状，且指定其特定的属性

```c++
class Circle: public Shape {  
public:  
    Circle(Point p, int rad): x {p}, r {rad} {} // constructor  
    Point center() const override { return x; }  
    void move(Point to) override { x = to; }  
    void draw() const override;  
    void rotate(int) override {}  
private:  
    Point x; // center  
    int r; // radius  
};
```

- 但其实，Circle也没有增加更多的东西

```c++
class Smiley: public Circle {  
public:  
    Smiley(Point p, int rad): Circle {p, rad}, mouth {nullptr} {}  
    ~Smiley() {  
        delete mouth;  
        for (auto p : eyes)  
            delete p;  
    }  
  
    void move(Point to) override;  
    void draw() const override;  
    void add_eyes(Shape* s) {  
        eyes.push_back(s);  
    }  
    void set_mouth(Shape* s);  
    virtual void wink(int  i); // wink eye number  
private:  
    std::vector<Shape*> eyes; // usually two eyes  
    Shape* mouth;  
};

void Smiley::draw() const {  
    Circle::draw();  
    for (auto p : eyes)  
        p->draw();  
    mouth->draw();  
}
```

- 请注意：**Smiley** 将 **eyes** 放在**vector**中，并在析构函数中进行**delete**。**Shape**的析构函数是**virtual**修饰的。虚析构函数对于抽象类是必不可少的，因为派生类的对象通通过其抽象基类提供的接口进行操作。特别是，它可能被指向基类的指针进行**delete**操作。因此，虚函数调用机制确保调用正确的析构函数，然后，该析构函数隐式调用其基类和成员的析构函数。

### 5.5.1 Benefits from Hierachies

#Class/hierarchies/benifit[[#^quote113]]

- 类层次结构提供了两个好处：
	- 接口继承：派生类对象可以用于需要基类对象的任何地方。也就是说，基类充当派生类的接口 -> **此类通常是抽象类**
	- 实现继承：基类提供简化派生类实现的函数或数据 -> **此类基类通常具有数据成员和构造函数**

> A class hierarchy offers two kinds of benefits: 
>> Interface inheritance: An object of a derived class can be used wherever an object of a base class is required. That is, the base class acts as an interface for the derived class. The **Container** and **Shape** classes are examples. Such classes are often abstract classes.
>> Implementation inheritance: A base class provides functions or data that simplifies the implementation of derived classes. **Smiley**’s uses of **Circle**’s constructor and of **Circle::draw()** are examples. Such base classes often have data members and constructors. ^quote113

- 具体类 -- 尤其是带有数据域的类 -- 很像内置类型：我们将其定义为局部变量，使用它们的名称访问，拷贝等等。类层次结构中的类是不同的：我们倾向于使用**new**在自由存储区中分配它们，并且通过指针或者引用访问。

```c++
Shape* read_shape(std::istream& is) {  
    // read shape header from is and find its Kind k ...  
    Kind k;  
    switch (k) {  
        case Kind::circle:  
            // read circle data  
            return new Circle {p, r};  
        case Kind::traingle:  
            // read traingle data {p1, p2, p3}  
            return new Traingle {p1, p2, p3};  
        case Kind::smiley:  
            // read smiley data  
            Smiley* ps = new Smiley {p, r};  
            ps->add_eyes(e1);  
            ps->add_eyes(e2);  
            ps->set_mouth(m);  
            return ps;  
    }  
}

void user() {  
    std::vector<Shape*> v;  
    while (std::cin)  
        v.push_back(read_shape(std::cin));  
    draw_all(v); // call draw() for each element  
    rotate_all(v, 45); // call rotate(45) for each element  
  
    for (auto p : v)  
        delete p;  
}
```

- 显然，这个例子被简化了 -- 尤其在错误处理方面 -- 但是它说明了user()完全不知道其操纵的哪一种类型。**user（）代码可以编译一次，然后用于添加到程序中的新形状。请注意，在user（）之外没有指向形状的指针，因此user（）负责释放它们。这是通过delete运算符完成的，并且严重依赖于Shape的虚拟析构函数。由于该析构函数是虚拟的，delete将调用最派生类的析构函数。这是至关重要的，因为派生类可能已经获取了需要释放的所有类型的资源（如文件句柄、锁和输出流）。在这种情况下，Smiley将删除其眼睛和嘴巴对象。一旦它做到了这一点，它就会调用Circle的析构函数。对象由构造函数“自底向上”（先从基）构造，由析构函数“自上而下”（先派生）销毁**。

### 5.2.2 Hierarchy Navigation

> **read_shape()** 函数返回一个**Shape\***，以便我们可以一视同仁地对待所有形状，但是，**如果我们想要使用由特定派生类提供的成员函数，我们可以使用dynamic_cast运算符**

```C++
Shape* ps {read_shape(std::cin)};

if (Smiley* p = dynamic_cast<Smiley*> (ps)) { // does ps point to Smiley?
	// .. a Smiley; use it
}else {
	// .. not a Smiley
}
```

#Class/hierarchies/dynamic_cast[[#^quote104]]

- 如果在运行时**dynamic_cast**(此处，ps)**参数所指向的对象不是预期类型(此处，Smiley)或从预期类型派生的类，dynamic_cast返回nullptr**

> If at run time the object pointed to by the argument of **dynamic_cast** (here, **ps**) is not of the expected type (here, **Smiley**) or a class derived from the expected type, **dynamic_cast** returns **nullptr**. ^quote104

> [!tip] 当指向不同派生类对象的指针是有效参数时，我们使用指针类型的**dynamic_cast**来判断是否是预期类型。**当不同的类型不可接受时，dynamic_cast将引发bad_cast异常**

```c++
Shape* ps {read_shape(std::cin)};
Smiley& r {dynamic_cast<Smiley&> (ps)}; // catch std::bad_cast
```

- 当有约束的使用**dynamic_cast**时，代码会变得更加清晰。如果我们可以避免在运行时测试类型信息，我们可以编写更简单、高效的代码，但有时类型信息会丢失，必须回复。**当我们将对象传递给某个接受基类指定的接口的系统时，通常会发生这种情况。当系统稍后将对象传递给我们时，我们可能必须恢复原始类型。类似于dynamic_cast的操作称为“is kind of”和“is instance of”操作**

### 5.5.3 Avoiding Resource Leaks

#Class/hierarchies/resource_leak[[#^quote114]]

- 泄漏是当我们获取资源但未能释放它时会发生什么的常规术语。**我们必须避免资源泄漏，因为泄漏会使泄漏的资源对系统不可用** -> 泄漏最终会导致系统耗尽所需资源时速度变慢甚至崩溃

> A _leak_ is the conventional term for the what happens when we acquire a resource and fail to release it. Leaking resources must be avoided because a leak makes the leaked resource unavailable to the system. ^quote114

- 通常情况，我们不要使用裸指针，由于历史遗留原因，C++没有GC(垃圾回收机制)，因此在后续C++11标准中，标准库提供了**unque_ptr**来防止内存泄漏的问题

```c++
class Smiley: public Circle {
	// ...
private:
	std::vector<std::unque_ptr<Shape>> eyes;
	std::unique_ptr<Shape> mouth;
}
```

- 当我们使用**unique_ptr**后，就不需要显式的对**unique_ptr**进行**delete**，使用**unique_ptr**的代码将与正确使用原始指针的代码一样高效

# 6. Essential Operations

## 6.1 Introduction

> 某些**operation**，例如初始化、赋值、拷贝和移动，是语言规则对他们作出假设的基本操作。其他**operation**，比如**\=\=**和**<<**具有难以忽略的传统意义

### 6.1.1 Essential Operations

#Operations/essential[[#^quote115]]

- 类型的构造函数、析构函数以及拷贝和移动**operation**在逻辑上不是分开的。我们必须将它们定义为匹配集，否则会遇见逻辑或性能问题

> Constructors, destructors, and copy and move operations for a type are not logically separate. We must define them as a matched set or suffer logical or performance problems. ^quote115

- 例如：如果**class X**具有执行重要任务(**例如自由存储区释放或者锁的释放**)的析构函数，则该类可能需要完整的函数补充

```c++
class X {  
public:  
    X(Sometype); // "ordinary constructor": create an object  
    X(); // default constructor  
    X(const X&); // copy constructor  
    X(X&&); // move constructor  
  
    X& operator= (const X&); // copy assignment: clean up target and copy  
    X& operator= (X&&); // move assignment: clean up target and move  
    ~X(); // destructor: clean up  
};
```

- 在以下五种情况下一个对象能够被**copy**或者**move**：
	- 1. 作为赋值的源(As the source of an assignment)
	- 2. 作为对象的初始化(As object initializer)
	- 3. 作为函数参数(As a function argument)
	- 4. 作为函数返回值(As a function return value)
	- 5. 作为异常(As an exception)
- 赋值能够使用拷贝赋值或者移动赋值重载。**原则上，其他情况就使用拷贝或移动构造函数。但是，拷贝或移动构造函数调用通常是通过在目标对象中构造，用于优化初始化对象。**

```c++
X make(Sometype);
X x = make(value);
```

- 上述代码，编译器通常会直接从**make()** 构造X，也就是说，直接通过**X(const X&)** 构造了X对象，从而消除了还要通过赋值的开销 -> 实际上，如果没有编译器的优化，应该经过**operator=()** 和**X(const X&)** 这两步操作的
- **除了初始化命名对象和自由存储区上的对象之外，构造函数还用于初始化临时对象和实现显示类型转换。**

> [!tip] 除了类似于**X(Sometype)**这样的构造函数之外，特殊成员函数将由编译器更具需要生成，当然，也可以使用**default**关键字来指出，该函数由编译器默认实现

```c++
class Y {  
public:  
    Y(Sometype);  
    Y(const Y&) = default; // I really do want the default copy constructor  
    Y(Y&&) = default; // and the default move constructor  
};
```

#Operations/essential/default[[#^quote116]]

- 当类具有指针成员时，**最好明确指明拷贝和移动操作**。**因为指针可能指向的是需要“delete”的内容，在这种情况下，默认的成员拷贝将是错误的。或者，它也可能指向不能删除的内容。** 但是不论哪一种情况，代码的阅读者都应该知道。
	- **因为C++存在深浅拷贝问题，如果存在指针，那么就使用默认的成员拷贝就可能出现两个对象中的指针指向同一个地址的情况。**

> When a class has a pointer member, it is usually a good idea to be explicit about copy and move operations. The reason is that a pointer may point to something that the class needs to **delete**, in which case the default memberwise copy would be wrong. Alternatively, it might point to something that the class must _not_ **delete**. In either case, a reader of the code would like to know. ^quote116

> [!tip] **一个好的经验法则(有时称为零法则)是定义所有基本操作或不定义任何操作(对所有操作使用默认值)**

```c++
struct Z {  
    Vector v;  
    std::string s;  
};

Z z1; // default initialize z1.v and z1.s
Z z2 = z1; // default copy z1.v and z1.s
```

- 在这里，编译器会根据需要的合成成员默认构造、拷贝、移动和析构函数，并且所有这些都具有正确的语义 -> **但是请注意，当你在内部有自定义结构时，需要保证你的自定义结构能够被正确初始化**

#Operations/essential/delete[[#^quote117]]

- 为了补充 **=default**，我们用 **=delete**来指明不生成操作。
	- 就比如，类成次结构中的基类我们是不希望允许成员复制的

> To complement **=default**, we have **=delete** to indicate that an operation is not to be generated. A base class in a class hierarchy is the classic example where we don’t want to allow a memberwise copy. ^quote117

```c++
class Shape {
public:
	Shape(const Shape&) = delete; // no copying
	Shape& operator= (const Shape&) = delete;
	// ...
};

void copy(Shape& s1, const Shape& s2) {
	s1 = s2; // error: Shape copy is delete
}
```

> [!tip] **=delete** 使得尝试使用已删除的函数会在编译时报错，其不仅仅只用于基本成员函数，而是可以用于抑制任何函数

### 6.1.2 Conversions

#Operations/conversion[[#^quote118]]

- 采用单个参数的构造函数定义了从实参类型进行的隐式转换
	- 也就是说，一个类如果定义了一个参数的构造函数，他是能够自动发生转化的

> A constructor taking a single argument defines a conversion from its argument type. ^quote118

```c++
complex z1 = 3.14; // z1 becomes {3.14, 0.0}
complex z2 = z1 * 2; // z2 becomes z1 * {2.0, 0} == {6.28, 0}
```

- 这种隐式转换有时是很有用的，但是并不是总是有用的
- 例如，在我们自己写的**Vector**中

```c++
Vector v = 7; // OK: v has 7 elements
```

- 但是对于标准库中的**std::vector**来说，这样的隐式转换是糟糕的，是不被允许的

> [!tip] 因此，我们需要一种方式来杜绝这样的隐式类型转换：**explicit**。使用该关键字可以指明其不允许隐式类型转换，只允许显式转换

```c++
class Vector {
public:
	explicit Vector(int s); // no implicit conversion from int to Vector
};

Vector v1(7); // OK：v1 has 7 elements
Vector v2 = 7; // error：no implicit conversion from int to Vector
```

- **通常而言，我们一般会将单个参数构造函数进行显式声明，而非使其能够隐式转换。除非我们有足够的理由不这样做**

> [!tip] 定义类的数据成员时，是可以进行初始化操作的，被称为**默认成员初始化设定项** -> 实际上就是初始化列表

```c++
class complex {
	double re = 0;
	double im = 0; // representation: two doubles with default value 0.0
public:
	complex(double r, double i): re {r}, im {i} {}
	complex(double r): re {r} {}
	complex() {}
}
```

- 默认值常被用于构造函数不被提供任何值的时候，这样简单的处理能够避免未初始化情况的发生

## 6.2 Copy and Move

#Operations/copy[[#^quote119]]

- 默认情况下，对象可以被拷贝。不论是用户自定义类型的对象还是内置类型都是如此。**"copy"** 的默认含义是按成员拷贝：拷贝每个成员

> By default, objects can be copied. This is true for objects of user-defined types as well as for builtin types. The default meaning of copy is memberwise copy: copy each member. ^quote119

```c++
void test(complex z1) {
	complex z2 {z1}; // copy initialization
	complex z3;
	z3 = z2; // copy assignment
}
```

- 当我们设计一个类的时候，我们必须始终考虑是否拷贝且如何拷贝一个对象。**对于一个简单的具体类型，成员拷贝通常是正常的语义，也就是说，编译器默认构造的拷贝构造(X(const X&))是正确的，不需要我们自行更改的。但是对于那些复杂的具体类型(例如Vector)，那么默认提供的拷贝构造就不再正确。并且*对于抽象类型，默认提供的语义几乎都不是正确的***

### 6.2.1 Copying Containers

#Operations/copy/container[[#^quote120]]

- 当类是资源句柄时，也就是说，**当类负责通过指针访问的对象时，默认的拷贝构造通常会造成灾难(语义错误)**，按成员拷贝会违反资源句柄的不变性 -> 其实通俗来讲，就是，会导致深浅拷贝问题，被拷贝和拷贝的对象会同时指向同一块资源，从而导致问题

> When a class is a _resource handle_ – that is, when the class is responsible for an object accessed through a pointer – the default memberwise copy is typically a disaster. Memberwise copy would violate the resource handle’s invariant ^quote120

```c++
void bad_copy(Vector v1) {
	Vector v2 = v1; // copy v1's representation into v2
	v1[0] = 2; // v2[0] is now also 2!
	v2[1] = 3; // v2[1] is now also 3!
}
```

- 那么，如果我们假如**v1**有四个元素：

![[bad-copy.png]]

- **值得一提的是，如果你出现上述的情况，那么一定会在析构的时候报错。因为，析构会delete该空间两次从而导致delete一个不属于我们的内存从而段错误**

> [!tip] 我们知道，对象的拷贝被两个成员函数所定义：**拷贝构造**和**拷贝赋值重载**

```c++
class Vector {  
public:  
    Vector(int s); // constructor: establish invariant, acquire resources  
    ~Vector() { delete[] elem; } // destructor: release resources  
  
    Vector(const Vector& a); // copy constructor  
    Vector& operator= (const Vector& a); // copy assignment  
  
    double& operator[] (int i);  
    const double& operator[] (int i) const;  
  
    int size() const;  
private:  
    double* elem; // elem points to an array of sz doubles  
    int sz;  
};
```

- 对于**Vector**来说，**拷贝构造函数需要为所需要数量元素定义且分配合适的空间，然后将元素拷贝在里面。以便于拷贝后的Vector都有自己的一个数据空间**

```c++
Vector::Vector(const Vector &a)  
    : elem { new double[a.size()]}  
    , sz {a.size()} {  
    for (int i = 0; i != sz; i++)  
        elem[i] = a.elem[i];  
}
```

- 当然的，除了拷贝构造我们还需要赋值重载

```c++
Vector &Vector::operator=(const Vector &a) {  
    double* p = new double[a.size()];  
    for (int i = 0; i != a.size(); i++)  
        p[i] = a.elem[i];  
    delete[] elem; // delete old element  
    elem = p;  
    sz = a.size();  
    return *this;  
}
```

- 经过这两步之后，那么**"v2 = v1"**的结果为：

![[copy-result.png]]

### 6.2.2 Move Containers

#Pointer/move[[#^quote121]]

- 我们可以通过定义拷贝构造和赋值重载来控制拷贝。**但是对于大型容器来说，拷贝的开销是巨大的，就算我们使用引用来避免拷贝的开销，但是我们不能返回一个局部变量的引用来作为返回值** -> 因为局部变量会被销毁，一旦销毁后，引用就没了绑定的对象，这是C++语法所不允许的。用标准一点的话来说，就是**不允许将亡值作为引用返回**

> We can control copying by defining a copy constructor and a copy assignment, but copying can be costly for large containers. We avoid the cost of copying when we pass objects to a function by using references, but we can’t return a reference to a local object as the result (the local object would be destroyed by the time the caller got a chance to look at it). ^quote121

```c++
Vector Vector::operator+(const Vector &a) {  
    if (this->size() != a.size())  
        throw Vector_size_mismatch {};  
    Vector res(a.size());  
    for (int i = 0; i != a.size(); i++)  
        // res[i] = this->operator[](i) + a[i];  
         res[i] = (*this)[i] + a[i];  
    return res;  
}
```

- 在此处，就是将局部的res作为返回值返回

```c++
void f(const Vector& x, const Vector& y, const Vector& z) {
	Vector r;
	// ...
	r = x + y + z;
	// ...
}
```

- 在这里，$r = x + y + z$会导致拷贝一个**Vector**至少两次(每使用一次**operator+**一次)。如果这个**Vector**够大，那么会导致程序的开销很大，最为不能接受的是，我们每使用(**operator+**)一次，就会导致**res**被创建，然后被销毁一次且在销毁后，编译器还要拷贝一次然后再通过**operator=**赋值给r。而我们只是想要从函数中获取结果，而非一个拷贝

```c++
class Vector {
	// ...
	Vector(const Vector& a); // copy constructor
	Vector& operator= (const Vector& a); // copy assignment

	Vector(Vector&& a); // move constructor
	Vector& operator= (Vector&& a); // move assignment
}
```

- 通过给定移动定义，编译器将选择**move constructor**来实现返回值从函数中转移出来。**这意味着$r = x + y + z$将不涉及类的拷贝，相反，只是"move"**

```c++
Vector::Vector(Vector&& a)
	: elem {a.elem} // "grab the elements" from a
	, sz {a.size()} {
	a.elem = nullptr; // now a has no element
	a.sz = 0;
}
```

- **&&** 的意义是 **“右值引用(rvalue reference)”**，也就是说我们可以绑定右值的引用，“右值”一次是“左值”的补充
	- “左值”：变量，对象; **一般是可寻址的对象，具有持久性**
	- “右值“：常量，将亡值; **一般是不可寻址的常量，临时对象，是暂时存在的**

> [!tip] 移动构造函数不接受**const**参数，因为移动构造需要将参数**清除干净**，当然的，移动赋值也是如此

- 通常情况下，**进行移动的对象经过移动后处于允许运行析构函数的状态** -> 当然的，当你进行移动后，被移动的对象的数据转交给了其他人，因此它的存在是非必须的。

> [!tip] 我们可以通过标准库所提供的函数来进行移动**std::move()**

```c++
Vector f() {
	Vector x(1000);
	Vector y(1000);
	Vector z(1000);
	z = x; // we get a copy (x might be used later)
	y = std::move(x); // we get a move (move assignment)
	// ... better not use x here
	return z; // we get a move
}
```

- 标准库函数**std::move**实际上并没有移动任何东西。相反，它返回一个对我们可以从中移动的参数的引用 -> 右值引用

> [!bug] 注意：如果想要返回一个将亡值来调用移动构造，**完全不需要显式调用move，因为编译器会默认的优化该返回值**

![[return-move.png]]

- **编译器有义务(根据C++标准)消除与初始化相关的大多数副本。因此调用移动构造函数的频率实际上没有你认为的那么频繁，这种拷贝优化消除了移动的非常小的开销，另一方面，通常不可能隐式消除赋值中的拷贝和移动操作，因此移动赋值对性能是至关重要的**

## 6.3 Resource Management

#Operations/resource[[#^quote122]]

- 通过定义构造函数、拷贝复制、移动复制和析构函数，程序员可以完全控制所包含资源(例如容器的元素)的生命期。此外，移动构造函数允许对象可以从一个范围简单而 **“廉价”** 地移动到另外一个范围。这样，我们就能使得不能或不想复制出范围的对象可以简单而廉价地移出

> By defining constructors, copy operations, move operations, and a destructor, a programmer can provide complete control of the lifetime of a contained resource (such as the elements of a container). Furthermore, a move constructor allows an object to move simply and cheaply from one scope to another. That way, objects that we cannot or would not want to copy out of a scope can be simply and cheaply moved out instead. ^quote122

- 如果我们用标准库中的**thread**表示并发活动，或者一个百万级别的**Vector**，我们是不会想要拷贝任意一个的

```c++
std::vector<std::thread> my_thread;

Vector init(int n) {
	thread t {heartbeat}; // run heartbeat concurrently
	my_thread.push_back(std::move(t)); // move into my_threads
	// ... more initialization ...
	Vector vec(n);
	for (auto& x : vec)
		x = 777; 
	return vec; // move vec out of init()
}
```

- 在许多情况下，资源句柄(如**Vector**和**thread**)是直接使用指针的更好的代替方案。**事实上，标准库提供了智能指针(如unique_ptr)，其本身就是资源句柄**
- 在许多与严重，资源管理主要是委托给垃圾回收器(**Garbage Collector(GC)**)。而在C++中，你也可以选择插入垃圾回收器，但是，垃圾回收器在C++作为资源管理的最后选择方案，除非迫不得已，不然就不会选择。

> 此外，内存不是唯一的资源。**资源是必须在使用后获取和释放(显式或隐式)的任何内容**。例如内存、锁、套接字、文件句柄和线程句柄。因此，不只是内存的资源被称为非内存资源。**一个好的资源管理系统处理各种资源，在任何长时间运行的系统中都必须避免泄漏，但过度的资源保留几乎与泄漏一样糟糕**。

#Operations/resource/RAII[[#^quote123]]

- 在诉诸垃圾回收之前，需要系统地使用资源句柄：**让每个资源在某个范围内有一个所有者，默认情况下在其所有者的范围结束时释放**。这在C++中，被称为**RAII(Resource Acquisition Is Initialization)**，并以异常的形式与错误处理集成在一起。
- 当然的，可以使用移动语义或只能指针将资源从一个范围移动到另一个范围，共享所有权可以由**share_ptr**表示

> Before resorting to garbage collection, systematically use resource handles: let each resource have an owner in some scope and by default be released at the end of its owner’s scope. In C++, this is known as _RAII_ (_Resource Acquisition Is Initialization_) and is integrated with error handling in the form of exceptions. Resources can be moved from scope to scope using move semantics or “smart pointers,” and shared ownership can be represented by “shared pointers” ^quote123

- 在C++标准库中，**RAII**无处不在，例如：内存(string、vector、map、unordered_map等)，文件(ifstream、ofstream等)、线程(thread)、锁(lock_guard、unique_lock等)和通用对象(通过unique_ptr和share_ptr)。

## 6.4 Operator Overloading

#Operations/overloading[[#^quote124]]

- 我们可以为用户自定义类型赋予C++运算符的含义。**这被称为运算符重载**，因为在使用时，必须从一组具有相同名称的运算符中选择运算符的正确实现

> We can give meaning to C++’s operators for user-defined types. That’s called _operator overloading_ because when used, the correct implementation of an operator must be selected from a set of operators with that same name. ^quote124

- **C++不允许定义新的(也就是说，我们独创的)运算符**，例如：不能定义**operator^^，\=\=\=，\*\*，$或者一元%**。一旦允许这样，就会发生很多很乱，同时，**强烈建议使用常规语义定义运算符**。例如：**operator+的意义表示减法，显然这对谁都没有好处**

- 我们可以为自定义类型定义的运算符有：
	- 二进制算数运算符：**+、-、\*、/、%**
	- 二进制逻辑运算符：**&(按位与)、| (按位或)、^ (按位异或)**
	- 二进制关系运算符：**\=\=、!=、<、<=、>、>=、<\=\>**
	- 逻辑运算符：**&&、||**
	- 一元算数和逻辑运算符：**+、-、～(按位取反)、! (逻辑非)**
	- 赋值：**=、+=、\*=等等**
	- 自增自减：**++、--**
	- 指针操作：**->、一元\*(解引用)、一元&(取地址)**
	- 调用：**()**
	- 索引：**\[\]**
	- 逗号：**,**
	- 位移：**>>、<<**
- **我们不允许重载 "."运算符**

```c++
class Matrix {  
public:  
    Matrix& operator= (const Matrix& matrix); // assign m to *this; return a reference  
};
```

- 这通常是第一个作出修改的运算符重载，并且出于历史原因，一般我们会重载 **=、->、()和\[\]**

```c++
Matrix operator+ (const Matrix& matrix1, const Matrix& matrix2);
```

> [!tip] 如果在类中定义，**由于this指针的存在，类似operator+的重载只允许显式至多一个参数，但是在类外，可以实现两个**

- 我们通常将具有对称操作的运算符(比如a + b)定义为独立函数，这样两个操作数就可以被同等对待(**而不是a.operator+ (b)**)。而为了从返回一个潜在的大对象(比如Matrix)中还拥有良好的性能，我们依赖于移动语义

## 6.5 Conventianal Operations

#Operations/conversion/operation[[#^quote125]]

- 某些操作在为类型定义时具有常规含义。这些常规含义通常是由程序员和库(**特别是标准库**)承担，因此在设计操作有意义的新类型时，遵循它们是明智的

> Some operations have conventional meanings when defined for a type. These conventional meanings are often assumed by programmers and libraries (notably, the standard library), so it is wise to conform to them when designing new types for which the operations make sense. ^quote125

- 以下是具有常规含义的操作：
	- 比较符：**\=\=、!=、<、<=、>、>=、<\=\>
	- 容器操作：**size()、begin()、end()**
	- 迭代器或智能指针：**->、\*、\[\]、++、--、+、-、+=、-=**
	- 函数对象：**()**
	- 输出输入操作：**>>、<<**
	- **swap()**
	- 哈希函数：**hash<>**

### 6.5.1 Comparisons(Relational Operators)

- 相等比较(\=\=和!=)的含义与拷贝密切相关，拷贝后应该相等

```c++
X a = something;
X b = a;
assert(a == b); // if a != b here, something is very odd
```

- 定义**\=\=**时，还要定义 **!=**并确保**a != b**表示 **!(a == b)**
- 当然的，大于小于也是如此：
	-  $a <= b$ 意味着 $(a < b) || (a == b)$ 以及 $!(b < a)$
	- $a > b$ 意味着 $b < a$
	- $a >= b$ 意味着 $(a > b) || (a == b)$ 以及 $!(a < b)$ 

> [!tip] 对于二元运算符的两个操作数(例如：**\=\=**)提供相同的处理，最好将其定义为其类命名空间中的独立函数

```c++
namespace NX {
	class X {
		// ...	
	};
	bool operator== (const X&, const X&);
};
```

> [!warning] **<\=\>**(三路运算符(宇宙飞船运算符))本身就是一种规律(C++ 20), 其规则与其他运算符不同。**特别是，通过定义默认的<\=\>隐式定义了其他关系运算符**

```c++
class R {  
    auto operator<=> (const R& a) const = default;  
};  
  
void user(const R& r1, const R& r2) {  
    bool b1 = (r1 <=> r2) == 0; // r1 == r2;  
    bool b2 = (r1 <=> r2) < 0; // r1 < r2;  
    bool b3 = (r1 <=> r2) > 0; // r1 > r2;  
  
    bool b4 = (r1 == r2);  
    bool b5 = (r1 < r2);  
}
```

- 与C语言的**strcpm**一样，**<\=\>** 实现了三向比较。**负返回值表示小于，0表示等于，正值表示大于**

> [!bug] operator<\=\>的重载需要引入头文件**compare**，同时，如果**<\=\>**定义非默认值，则**\=\=**不是隐式定义的，但**<**和其他关系运算符是隐式定义的

```c++
struct R2 {
	int m;
	auto operator<=> (const R2& a) const {
		return a.m == m ? 0 : a.m < m ? -1 : 1;
	}
}

void user(const R2& r1, const R2& r2) {
	bool b4 = (r1 == r2); // error: no non-default == 
	bool b5 = (r1 < r2); // OK
}
```

> 大多数标准库类型(如string、vector)都是遵循该模式的。**因为，如果一个类型有多个元素参与比较，则默认的<\=\>一次检查一个元素，从而生成字典顺序。在这种情况下，通常得另外提供一个单独优化的\=\=，因为<\=\>必须检查所有元素以确定所有三个备选方案**

```c++
string s1 = "asdfghjkl";
string s2 = "asdfghjk";

bool b1 = s1 == s2; // false
bool b2 = (s1 <=> s2) == 0; // false
```

- 在这个案例中，如果使用普通的**\=\=**，只需要查看字符串的字符数就可以发现其是不相等的，而使用**<\=\>**，我们就必须读取s2的所有字符才能发现其小于s1。**默认需要自己定义\=\=，是为了C++中程序性能的考量**

### 6.5.2 Container Operations

#Operations/conversion/container[[#^quote126]]

- 除非有很好的理由不这么做，否则请以标准库容器的风格设计容器。**特别是，通过将容器资源实现为具体适当基本操作的句柄来确保容器资源的安全**

> Unless there is a really good reason not to, design containers in the style of the standard-library containers. In particular, make the container resource safe by implementing it as a handle with appropriate essential operations ^quote126

> [!tip] 对于标准库来说，会有一个接口用于自身的大小：**size()**

```c++
for (size_t i = 0; i < c.size(); i++) {
	// size_t is the name of the type return by a size()
	c[i] = 0;
}
```

- 然而，对于标准库的算法来说，不是使用**从0到size()的索引便利容器，而是依赖于由迭代器对分隔的序列**

```c++
for (auto p = c.begin(); p != c.end(); p++)
	*p = 0;
```

- 在此处，**begin()指向c的第一个元素，end()指向最后一个元素的后一个元素**。迭代器支持 **++**
- 当然的，迭代器也被**range-for**实现使用，因此我们可以简化循环

```c++
for (auto& x : c)
	x = 0;
```

- 迭代器用于将序列传递给标准库算法

```c++
std::sort(c.begin(), c.end());
```

> [!tip] 对于迭代器，还有**const**版本，cbegin和cend，其实际类型为**const_iterator**

### 6.5.3 Iteraors and "smart pointers"

#Operations/conversion/ierators[[#^quote127]]

- 用户定义的迭代器和智能指针实现其目的所需的运算符和指针放， 并经常根据需要添加语义

> User-defined iterators  and “smart pointers”  implement the operators and aspects of a pointer desired for their purpose and often add semantics as needed. ^quote127

- 访问符：**\*、->(for a class)、\[\](for a container)**
- 迭代器/导航：**++(forward)、--(backward)、+=、-=、+、-**
- 拷贝/移动：**=**

### 6.5.4 Input and Output Operations

- 详情请见第十一章

### 6.5.5 swap()

- 许多算法，尤其是sort（），使用swap（）函数来交换两个对象的值。这种算法通常假设swap（）非常快，不会抛出异常。标准库提供了一个std:：swap（a，b），实现为三个移动操作）。如果你设计了一个复制成本很高并且很可能被交换的类型（例如，通过排序函数），那么就给它一个移动操作或swap（）或两者。注意，标准库容器和字符串具有快速移动操作。

### 6.5.6 hash<>

- 标准库unordered_map<K,V>是一个哈希表，K是键类型，V是值类型)。要使用类型X作为键，必须定义hash\<X\>。对于常见类型，例如std::string，标准库为我们定义了hash\<\>。

## 6.6 User-Defined Literals

#Operations/Literals[[#^quote128]]

- 类的一个目的是使程序员能够设计和实现与内置类型紧密相似的类型。构造函数提供的初始化等于或超过内置类型初始化的灵活性和效率，但对于内置类型，我们有文本
	- 123 is an int
	- 0xFF00u is an unsigned int
	- 123.456 is a double
	- "Surprise!" is a const char\[10\]

> One purpose of classes was to enable the programmer to design and implement types to closely mimic built-in types. Constructors provide initialization that equals or exceeds the flexibility and efficiency of built-in type initialization, but for built-in types, we have literals ^quote128

- 为用户类型提供此类文本是很有用的。这是通过定义文字的合适后缀来完成的，因此：
	- "Surprise!"s is a std::string
	- 123s is seconds
	- 12.7i is imaginary so that 12.7i + 47 is a complex number

> [!tip] 我们可以通过使用合适的标头和命名空间从标准库中获取

| header file | literals | means |
| :---: | :---: | :---: |
| \<chrono\> | std::literals::chrono_literals | h, min, s, ms, us, ns |
| \<string\> | std::literals::string_literals | s |
| \<string_view\> | std::literals::string_literals | sv |
| \<complex\> | std::literals::complex_literals | i, il, if |

- 带有用户定义后缀的文字称为用户定义的文字或UDLs。此类文字是使用文字运算符定义的。文字运算符将其参数类型的文字（后跟下标）转换为其返回类型。

```c++
constexpr std::complex<long double> operator""_i (long double arg) {  
    return {0, arg};  
}

// the 12_i becomes 0, 12i
```

- **operator""** 说明了我们正在定义一个**literal operator**
- 而**operator""\_i** 后面的**i**是运算符赋予意义的后缀
- 浮点文本的类型一般是**long double**的

```c++
std::complex<double> z = 2.7182818+6.283185i;
```

> [!tip] 由于**operator""** 和**operator+** 都是**constexpr**的，因此都在编译期计算

# 7. Templates

## 7.1 Introduction

#Template/introduction[[#^quote129]]

- 模板是我们用一组类型或值参数化的类或函数。我们使用模板来表示最好理解为一般想法的想法，我们可以通过指定参数从中生成特定的类型和函数

> A _template_ is a class or a function that we parameterize with a set of types or values. We use templates to represent ideas that are best understood as something general from which we can generate specific types and functions by specifying arguments ^quote129

## 7.2 Parameterized Types

> 我们可以将我们的**double Vector**通过**template**推广为任意的**Vector**类型，其方法就是通过模板将特定类型替换为类型参数

```c++
template <typename T>  
class Vector {  
public:  
    explicit Vector(int s); // constructor: establish invariant, acquire resources  
    ~Vector() { delete[] elem; } // destructor: release resources  
public:  
    // copy and move operations  
    Vector(const Vector<T>& v);  
    Vector(Vector<T>&& v);  
    Vector<T>& operator= (const Vector<T>& v);  
    Vector<T>& operator= (Vector<T>&& v);  
  
    T& operator[] (int i); // for non-const Vectors  
    const T& operator[] (int i) const; // for const Vectors  
    int size() const { return sz; }  
private:  
    T* elem; // elem points to an array of sz elements of type T  
    int sz;  
};
```

- **template \<typename T\>** 前缀使**T**成为其前缀声明的类型形参。它就相当于是C++中的**for all T**更准确来说是**for all types T**。
- 如果你想要数学意义上的**for all T**，比如说$P(T)$，那么你可以使用**concepts(§7.2.1、§8.2)**。

> [!tip] 由于C++的历史原因，在老版本中，C++是采用**class**来代表**typename**的

- 而上述代码的定义可以如下所示

```c++
template <typename T>  
Vector<T>::Vector(int s) {  
    if (s < 0)  
        throw std::length_error {"Vector constructor: negative size"};  
    elem = new T[s];  
    sz = s;  
}  
  
template <typename T>  
const T &Vector<T>::operator[](int i) const {  
    if (i < 0 || size() <= i)  
        throw std::out_of_range {"Vector::operator[]"};  
    return elem[i];  
}

// 当我们给出这样的定义后，那么就能够有如下的实例

void func1() {  
    Vector<char> vc(200); // vector of 200 characters  
    Vector<std::string> vs(17); // vector of 17 strings  
    Vector<std::list<int>> vli(45); // vector of 45 lists of integers  
}
```

> [!bug] 在上述中，**Vector<std::list\<int\>>**中的**>>**不是输入或者右移操作符。在以前的老标准中，模板的**<>**应该分开：** Vector< std::list\<int\> >**否则会报错

> [!warning] 注意：如果你想要的你的容器能够用于**range-for**，那么必须有**begin()**和**end()**，而且大小写必须一致，否则仍然错误

```c++
template <typename T>  
T *Vector<T>::begin() {  
    return &elem[0];  
}  
  
template <typename T>  
T *Vector<T>::end() {  
    return &elem[size()];  
}

for (auto& v : vs)  
    std::cout << v << " ";
```

- **模板是一种编译时机制，因此其与手工编写代码相比，使用模板不会引起运行时的开销。也就是说，其实你的Vector\<double\>实际上是相当与自己写了一个“double Vector”，只不过这样的操作交给了编译器**

### 7.2.1 Constrained Template Arguments(C++20)

#Template/Constrained/Element[[#^quote130]]

- 通常，模板只对满足特定条件的模板参数有意义。例如：**Vector**通常提供拷贝操作，如果提供了，那么就说明其元素必须是可拷贝的。也就是说，我们必须要求**Vector**的模板参数**不仅仅只是一个类型名，还必须是一个“Element”，其中“Element”指定了可以元素类型的要求**

> Most often, a template will make sense only for template arguments that meet certain criteria. For example, a **Vector** typically offers a copy operation, and if it does, it must require that its elements are copyable. That is, we must require that **Vector**’s template argument is not just a **typename** but an **Element** where “**Element**” specifies the requirements of a type that can be an element ^quote130

```c++
template <Element T>
class Vector {
private:
	T* elem;
	int sz;
}
```

- **template \<Element T\>** 前缀是C++版本的**for all T such that Element(T)**，也就是说，**Element**是一个谓词(表明含义)，**它检查T是否具有Vector所需的所有属性。这样的概念被称为"concept(§8.2)"**。
- **而指定了“concept”的模板实参称为约束实参，参数受到约束的模板称为约束模板**

> [!tip] 尝试使用类型不符合其要求的模板是一个编译时错误

```c++
Vector<int> v; // OK
Vector<std::thread> v1; // erorr
```

> 因此，**"concept"可以让编译器在使用时进行类型检查，比不受约束的模板参数更早地给出更好的错误消息**。c++在c++ 20之前没有正式支持概念，所以旧的代码使用不受约束的模板参数，并将需求留给文档。但是，**从模板生成的代码会进行类型检查，因此即使是不受约束的模板代码也与手写代码一样是类型安全的。对于不受约束的参数，在所有相关实体的类型可用之前不能进行类型检查，因此它可能会在编译过程的晚期发生，在实例化时，并且错误消息通常很糟糕**。

### 7.2.2 Value Template Arguments

- 除了类型参数之外，模板还可以使用值的参数

```c++
template <typename T, int N>  
struct Buffer {  
    constexpr int size() { return N; }  
    T elem[N];  
};
```

- 值参在许多上下文中都很有用。例如：**Buffer**允许我们在不使用空闲存储区(动态内存)的情况下创建任意大小的**Buffer**

```c++
Buffer<char, 1024> glob; // global buffer of char(statically allocated)

void fct() {
	Buffer<int, 10> buf; // local buffer of int(on the stack)
}
```

> [!tip] 遗憾的是，由于一些技术原因，**字符串文本不能作为模板值参数**。但是在某些情况下，使用字符串进行参数化的能力至关重要，因此可以借助数组来完成

```c++
template <char* s>  
void outs() { std::cout << s; }  
  
char arr[] = "Weird workaround";  
  
void use() {  
    outs<"straightforward use">(); // error (for now)  
    outs<arr>(); // OK  
}
```

### 7.2.3 Template Argument Deduction

> 定义模板为实例化时，我们通常需要指定其类型

```c++
std::pair<int, double> p = {1, 5.2};
```

> [!tip] 必须指定模板参数是很单调的，因此，C++中可以由构造函数从初始化中推导出其类型

```c++
std::pair p = {1, 5.2};

template <typename T>
class Vector {
public:
	Vector (int);
	Vector (initialize_list<T>);
};

Vector v1 {1, 2, 3}; // deduce v1's element type from the initializer element type: int
Vector v2 = v1; // deduce v2's element type from v1's element type: int

auto p = new Vector {1, 2, 3}; // p is a Vector<int>*

Vector <int> v3(1); // here we need to be explicit about the element type (no element type is mentioned)
```

- 显然，这简化了表示，并可以消除错误键入冗余模板参数类型所引起的麻烦。然而，这并不是灵丹妙药。和所有其他强大的机制一样，演绎也会带来意外。

```c++
using namespace std::literals::string_literals;
Vector<string> vs {"Hello", "World"}; // OK: Vector<string>
Vector vs1 {"Hello", "World"}; // OK: deduces to Vector<const char*> (Surprise?)
Vector vs2 {"Hello"s, "World"s}; // OK: deduces to Vector<string>
Vector vs3 {"Hello"s, "World"}; // error: the initializer list is not homogenous
Vector<string> vs4 {"Hello"s, "World"}; // OK: the element type is explicit
```

> 如果初始化设定项序列中的元素有不同的类型，则我们无法推断出唯一的元素类型，因此会发生歧义错误。而标准库中有一个构造函数，采用一对分隔序列的迭代器，还有一个可以采用一对值的构造函数

```c++
template <typename T>
class Vector {
public:
	Vector (initialize_list<T>); // initialize_list constructor
	template <typename Iter>
	Vector (Iterb, Iter e); [b, e) iterator-pair constructor
	struct iterator {
		using value_type = T;
		// ...
	}; 
	ierator begin();
};

Vector v1 {1, 2, 3, 4, 5}; //element type is int
Vector v2 (v1.begin(), v1.begin() + 2); // a pair of iterators
Vector v3(9, 17); // error: ambiguous
```

- 事实上，我们可以使用**concept**来解决这个问题，但是由于该概念是C++20中才出现的标准，因此在以前的代码中，我们需要**一种相同类型的值应该被视为迭代器**

```c++
template <typename Iter>
Vector (Iter, Iter) -> Vector <typename Iter::value_type>;

Vector v1 {1, 2, 3, 4, 5}; //element type is int
Vector v2 (v1.begin(), v1.begin() + 2); // element type is int
Vector v3 {v1.begin(), v2.begin() + 2}; // element type is Vector::iertaor
```

- **{}-initialize**语法总是指向初始化列表构造函数(如果存在的话)，因此**v3**是一个vector的迭代器：**Vector<Vector\<int\>>::iterator**
- **()-initialize**语法是在我们不需要初始化列表时约定俗成的
- **类模板参数推导的英文缩写为CTAD**

## 7.3 Parameterized Operations

#Template/Parameterized[[#^quote131]]

- 模板的用途远不止简单地参数化具有元素类型的容器。特别是，它们广泛用于标准库中类型和算法的参数化

> Templates have many more uses than simply parameterizing a container with an element type. In particular, they are extensively used for parameterization of both types and algorithms in the standard library ^quote131

- 有三种方法可以表示按类型或值参数化的操作：
	- 函数模板
	- 函数对象：可以携带数据并像函数一样被调用的对象
	- lambda表达式：函数对象的速记表示法

### 7.3.1 Function Templates

```c++
template <typename Sequence, typename Value>  
Value sum (const Sequence& s, Value v) {  
    for (auto x : s)  
        v += x;  
    return v;  
}
```

- 值模板参数和函数参数 v 用于允许调用方指定累加器的类型和初始值（累加总和的变量）

```c++
void user(Vector<int>& vi, std::list<double>& ld,  
          std::vector<std::complex<double>>& vc) {  
    int x = sum(vi, 0); // the sum of a vector of ints (add ints)  
    double d = sum(vi, 0.0); // the sum of a vector of ints (add doubles)  
    double dd = sum(ld, 0.0); // the sum of a list of doubles  
    auto z = sum(vc, std::complex {0.0, 0.0});  
    // the sum of a vector of complex<double> }
```

> [!bug] 函数模板可以是成员函数，但不能是虚拟成员。编译器不会知道程序中此类模板的所有实例化，因此它无法生成 vtbl

### 7.3.2 Fcuntion Objects

#Template/Parameterized/object[[#^quote132]]

- 一种特别有用的模板是函数对象(也被称为**funtor**)，它用于定义可以像函数一样调用的对象

> One particularly useful kind of template is the _function object_ (sometimes called a _functor_), which is used to define objects that can be called like functions. ^quote132

```c++
template <typename T>  
class Less_than {  
    const T val; // value to compare against  
public:  
    Less_than(const T& v): val(v) {}  
    bool operator() (const T& x) const { return x < val; } // call operator  
};
```

- 名为**operator()** 的函数实现了调用运算符 **()**，也被称为**函数调用**或者简称**调用**

```c++
void func3() {  
    Less_than lti {42}; // lti(i) will compare i to 42 using < (i<42)  
    using namespace std::literals::string_literals;  
    Less_than lts {"Backus"s}; // lts(s) will compare s to "Backus" using < (s<"Backus")  
    Less_than<std::string> lts2 {"Naur"}; // "Naur" is a C-style string, so we need <string> to get the right <  
}

void fct(int n, const std::string& s) {  
    bool b1 = lti(n); // true if n < 42  
    bool b2 = lts(s); // true is s < "Backus"  
}
```

- 函数对象被广泛用于算法的参数中

```c++
template <typename C, typename P>
int count(const C& c, P pred) {
	// assume that C is a container and P is a predicate on its elements
	int cnt = 0;
	for (const auto& x : c)
		if (pred(x))
			++cnt;
	return cnt;
}
```

- 给定**concept**，我们可以形式化**count()**关于其参数的假设，并在编译时检查它们。其是我们可以调用它来返回真假的东西

```c++
void f(const Vector<int>& vec, const std::list<std::string>& lst, int x, const std::string& s) {  
    std::cout << "number of values less than " << x << " : " << std::count(vec.begin(), Less_than {x}) << "\n";  
    std::cout << "number of values less than " << s << " : " << std::count(lst, Less_than {x});  
}
```

- 此处，**Less_than {x}** 构造了一个类型为**Less_than\<int\>**的对象，调用运算符将其与名为x的int值做比较，同理**Less_than {s}** 也是如此
> 函数对象的美妙之处在于它们携带要与之进行比较的值。我们不必为每个值（和每种类型）编写单独的函数，也不必引入讨厌的全局变量来保存值。此外，对于像 Less_than 这样的简单函数对象，内联很简单，因此调用 Less_than 比间接函数调用效率高得多。携带数据的能力加上它们的效率使函数对象作为算法的参数特别有用。

### Lambda Expressions

- 在上一节中，我们定义了**Less_than**，但这其实很不方便，而C++提供了一种用于隐式生成函数对象的方法：

```c++
void f(const Vector<int>& vec, const std::list<std::string>& lst, int x, const std::string& s) {  
    std::cout << "number of values less than "  
                << x << " : "  
                << std::count(vec.begin(), [&](int a) { return a < x; })  
                << "\n";  
    std::cout << "number of values less than "  
                << s << " : "  
              << std::count(lst, [&](const std::string& a) { return a < s; });  
}
```

> **[&]（int a）{ return a<x; }** 称为 lambda 表达式。它生成一个类似于 **Less_than\<int\>{x}** 的函数对象。
> [&] 是一个捕获列表，指定将通过引用访问 lambda 正文中使用的所有局部变量（例如 x）。如果我们只想“捕获”x，我们可以这样说：[&x]。如果我们想给生成的对象一个 x 的副本，我们可以这样说：[x]。 捕获任何内容是 [ ]，捕获引用使用的所有局部变量是 [&]，捕获值使用的所有局部变量是 [=]

> [!tip] 对于成员函数中定义的lambda表达式，**\[this\]** 捕获当前对象的引用，如果我们想要当前对象的拷贝，则是 **\[\*this\]** (C++11)

```c++
class X {  
public:  
    void f(X& x) {  
        auto f = [this]() { return *this; };  
        auto f1 = [*this](){ return *this; };  
    }  
};
```

#### 7.3.3.1 Lambdas as funtion arguments

#Template/Lambda[[#^quote133]]

- 使用**lambda表达式**会使代码更方便简洁，但是会使其晦涩难懂。对于一些不是很普通的操作(比如说简单的表达式)，更推荐给这个操作命名(也就是说，写成一个完整的函数)，使其更具有意义

> Using lambdas can be convenient and terse, but also obscure. For nontrivial actions (say, more than a simple expression), I prefer to name the operation so as to more clearly state its purpose and to make it available for use in several places in a program. ^quote133

```c++
template <typename C, typename Oper>
void for_each(C& c, Oper op) {
	for (auto& x : c)
		op(x);
}

void user() {
	vector <unique_ptr<Shape>> v;
	while (std::cin)
		v.push_back(read_shape(std::cin));
	for_each(v, [](unique_ptr<Shape>& ps) { ps->draw(); });
	for_each(v, [](unique_ptr<Shape>& ps) { ps->ratate(45); });
}
```

#### 7.3.3.2 Lambdas for initialization

> 使用lambda表达式，我们可以将任何语句转化为表达式。这主要用于提供将值计算为参数值的操作，但功能是通用的。

```c++
void user(Init_mode m, int n, std::vector<int>& arg, Iterator p, Iterator q) {  
    std::vector<int> v;  
  
    switch (m) {  
        case Init_mode::zero:  
            v = std::vector<int> (n);  
            break;  
        case Init_mode::cpy:  
            v = arg;  
            break;  
    }  
  
    if (m == Init_mode::seq)  
        v.assign(p, q);  
}
```

- 这是一个风格化的例子，但不幸的是不是非典型的。我们需要在一组用于初始化数据结构的替代方案中进行选择（此处为 v），并且我们需要为不同的替代方案进行不同的计算。这样的代码通常是混乱的，被认为是“效率”所必需的，并且是错误的来源。
	- 变量可以在获得其预期值之前使用
	- “初始化代码”可能与其他代码混合，使其难以理解。
	- 当“初始化代码”与其他代码混合时，更容易忘记案例。
	- 这不是初始化，而是赋值
- 因此，我们使用lambda表达式来作为初始化

```c++
void user(Init_mode m, int n, std::vector<int>& arg, Iterator p, Iterator q) {  
    std::vector<int> v = [&] {  
        switch (m) {  
            case Init_mode::zero:  
                return std::vector<int> (n);  
            case Init_mode::seq:  
                return std::vector<int> {p, q};  
            case Init_mode::cpy:  
                return arg;  
            case Init_mode::patrn:  
                break;  
        }  
    }();  
}
```

#### 7.3.3.3 Finally

> 析构函数提供了一种通用的隐式机制，用于在使用对象后进行清理 （RAII)，但是如果我们需要执行一些与单个对象无关的清理，或者与没有析构函数的对象相关联（例如，因为它是与 C 程序共享的类型）怎么办？我们可以定义一个函数 final（），该函数在退出作用域时执行一个动作

```c++
void old_type (int n) {  
    void* p = (void*) malloc(n * sizeof (int )); // C-type  
    auto act = finally([&]{ free(p); }); // call the lambda upon scope exit  
}// p is implicitly freed upon scope exit
```

- 这是临时的，但比尝试在函数的所有出口上正确且一致地调用 free（p） 要好得多。

```c++
template <class F>  
struct Final_action {  
    explicit Final_action(F f): act(f) {}  
    ~Final_action() { act(); }  
    F act;  
};  
  
template <class F>  
[[nodiscard]] auto finally(F f) {  
    return Final_action {f};  
}
```

- 使用 **\[\[nodiscard]]** 来确保用户不会忘记将生成的**Final_action**复制到其操作的预期范围内
- 而**Final_action**需要提供如上所示必须的析构函数

> [!tip] \[\[nodiscard]]属性其实就是声明，该函数、类、表达式的返回值是必须的

```c++
[[nodiscard("The empty return value must be used")]]  
bool empty() {  
    return false;  
}
```

- 在C++17中，可以使用该属性，但是如果你不使用其返回值实际上也不会报错，但是在C++20中，可以在该属性中输入字符文本，这时如果未使用则会报错

## 7.4 Template Mechnisms

