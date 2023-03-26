# Rust

---  

## 第一个Rust程序

```Rust
//main.rs
fn main(){
	println!("Hello World!");
}
```

- 注意：
	- Rust的后缀名是rs
	- **Rust和C++一样，main作为一个程序的入口，且以;号结尾**
	- **Rust中只要看到 ! 就说明这个是一个宏，而不是普通函数**
	- **Rust强调缩进必须是4个空格**

### 编译

```Rlinux
# rustc main.rc
```

- **和C++一样，Rust是一门静态语言，也有着对应的编译器rustc**

### 运行

```linux
# ./main
```

## Cargo

> Cargo是Rust提供的一个构建系统和包管理器。它能够处理构建代码、下载依赖库并编译等等

```linux
# cargo --version
```

### 使用Cargo创建项目

```linux
cargo new hello_cargo
```

- 注意：
	- cargo创建使用new program_name
	- cargo会根据项目名称创建两个文件和一个目录
		- Cargo.toml文件
		- main.rs文件
		- src目录

```toml
[package]
name = "hello_cargo"
version = "0.1.0"
edition = "2021"

[dependencies]
```

- 注意：
	- Cargo.toml使用TOML格式，这也是Cargo配置文件的格式
	- 第一行的[package]表面下面的语句是用来配置一个包
	- 接下来的三行分别介绍了，**项目的名字、项目版本号以及使用Rust的版本**
		- **注意：name的名字是根据cargo new 的时候而来的**
	- 最后一行的[dependencies]，是罗列项目依赖片段的开始。**在Rust中，代码包被称为crates**

```rust
fn main(){
	println!("Hello, world!");
}
```

- 注意：
	- Cargo在创建的时候会自动帮你生成如上代码
	- **Cargo期望源文件都放置在src中。使得项目根目录只存放README、license信息、配置文件等**

### 使用Cargo构建并运行

```linux
# cargo build
	   Compiling hello_cargo v0.1.0 (/home/zack/code_work/github_work/My_Cpp_Programming/Rust/projects/hello_cargo)
    Finished dev [unoptimized + debuginfo] target(s) in 0.23s
```

- 注意：
	- **在cargo new创建的项目文件夹中使用cargo build**
	- **cargo build会自动创建一个可执行文件target/debug/hello_cargo, ==注意：生成的可执行文件是根据创建时的项目名称的==**
	- cargo build执行的默认方式是**debug构建，因此可执行文件会在target的debug中**
	- cargo build第一次执行后会生成一个Cargo.lock文件，这个文件**记录了项目依赖的实际版本。我们千万不要触碰这个文件，让Cargo处理就好**

```linux
# cargo run
    Finished dev [unoptimized + debuginfo] target(s) in 0.00s
     Running `target/debug/hello_cargo`
Hello, world!
```

- 注意：
	- 因为cargo build之后会将可执行文件放在target目录下，每次执行都会使用其路径，因此**使用cargo run来达到相同的目的**

```linux
# cargo check
    Checking hello_cargo v0.1.0 (/home/zack/code_work/github_work/My_Cpp_Programming/Rust/projects/hello_cargo)
    Finished dev [unoptimized + debuginfo] target(s) in 0.04s
```

- 注意：
	- cargo check可以**快速检查代码并确保可编译，但不会生成可执行文件

```linux
# cargo build --release
```

- 注意：
	- 这是**release版本编译**

## Rust编程基本概念

### 关键字

> 对于关键字的学习，我觉得应该跟随着语言逐步学习

| 关键字 | 说明 | 关键字 | 说明 | 关键字 | 说明 |
| --- | --- | --- | --- | --- | --- |
| let | 绑定一个变量 | mut | 表示引用、裸指针或者模式绑定的可变性 | const | 定义常量或不变裸指针 |


### 变量和可变性

#### 不可变性

> Rust中，**变量变量默认是不可改变的**

```rust
fn main(){
	let x = 5;
	println!("The value of x is {x}");
	x = 6;
	println!("The value of x is {x}");
}
```

```linux
# cargo run
   Compiling variables v0.1.0 (/home/zack/code_work/github_work/My_Cpp_Programming/Rust/projects/variables)
error[E0384]: cannot assign twice to immutable variable `x`
 --> src/main.rs:4:5
  |
2 |     let x = 5;
  |         -
  |         |
  |         first assignment to `x`
  |         help: consider making this binding mutable: `mut x`
3 |     println!("The value of x is : {x}");
4 |     x = 6;
  |     ^^^^^ cannot assign twice to immutable variable

For more information about this error, try `rustc --explain E0384`.
error: could not compile `variables` due to previous error
```

- 注意：
	- 这充分说明了，**在Rust中，变量是不可以更改的**
	- **let是Rust中的一个关键字，用来绑定一个变量**
	- 可以看见，Rust中的输出使用{var}

#### 可变性

```rust
fn main(){
	let mut x = 5;
	println!("The value of x is {x}");
	x = 6;
	println!("The value of x is {x}");
}
```

```linux
   Compiling variables v0.1.0 (/home/zack/code_work/github_work/My_Cpp_Programming/Rust/projects/variables)
    Finished dev [unoptimized + debuginfo] target(s) in 0.11s
     Running `/home/zack/code_work/github_work/My_Cpp_Programming/Rust/projects/variables/target/debug/variables`
The value of x is : 5
The value of x is : 6
```

- 注意：
	- **尽管Rust中通过let关键字绑定的变量不可更改，但是可以通过在变量名前添加mut关键字使得该变量可变**

#### 常量

> 类似不可变变量，**常量是绑定到一个名称的不允许改变的值**

```rust
const THREE_HOURS_IN_SECONDS: u32 = 60 * 60 * 3;
```

- 注意：
	- 常量的定义和C++一样，**const是Rust中的一个关键字**
	- 使用const修饰的常量，**不允许使用mut，且必须标明值的类型**
	- **Rust中使用 : 来声明类型，这一点会在后面提到**
	- **Rust中的常量用全大写，单词之间使用下划线来连接**

#### 隐藏

> 当我们定义了一个与之前变量相同的新变量时，第一个会被第二个隐藏。也就是说，当以后再次使用时，编译器看到的就是第二次定义的变量。**这类似与C++中的局部优先**

```rust
fn main(){
	let x = 5;

	let x = x + 1;
	
	{
		let x = x * 2;
		println!("The Value of x in the inner scope is : {x}");	
	}
	println!("The Value of x is : {x}");
}
```

```linux
# cargo run
    Finished dev [unoptimized + debuginfo] target(s) in 0.00s
     Running `target/debug/shadow`
The value of x in the linner scope is 12
The value of x is 6
```

- 可以发现，在内部的变化之后，没有影响外部
- **这类似于C++中的一个概念，作用域，当我们使用{}时，相当于就有了一个与main不同的作用于，那么我们在内部定义的x,就只能在其内部生效**
- let在此处本质上是创建了一个新的变量x
- **let可以改变一个变量的属性，因为他创建的变量是一个新的，如果使用mut,那么会发生编译错误**

```rust
fn main(){
	let mut spaces = "   ";
	spaces = spaces.len();
}
```

```linux
# cargo run
   Compiling shadow v0.1.0 (/home/zack/code_work/github_work/My_Cpp_Programming/Rust/projects/shadow)
error[E0308]: mismatched types
  --> src/main.rs:12:14
   |
11 |     let mut spaces = "  ";
   |                      ---- expected due to this value
12 |     spaces = spaces.len();
   |              ^^^^^^^^^^^^ expected `&str`, found `usize`

For more information about this error, try `rustc --explain E0308`.
error: could not compile `shadow` due to previous error
```

### 数据类型

> 在Rust中，每一个值都有自己的一个数据类型，我们将看到**标量和复合**

> 比如：使用parse将String转换为数字时，**必须添加类型注解**
> 类型注解：Rust使用 : 来标注类型

#### 标量类型

> 标量代表一个单独的值。
> Rust中有四种的基本标量：**整形、浮点型、布尔类型和字符类型**

##### 整形

| 长度 | 有符号 | 无符号 | 长度 | 有符号 | 无符号 |
| --- | --- | --- | --- | --- | --- |
| 8-bit | i8 | u8 | 16-bit | i16 | u16 |
| 32-bit | i32 | u32 | 64-bit | i64 | u64 |
| 128-bit | i128 | u128 | arch | isize | usize |

- 注意：
	- 在Rust中，有符号数是通过补码形式存储，这一点和C++一致
	- 如果没有指定类型，那么默认是u32的
	- 上述类型能表达的数量可以通过：$2^n - 1$来计算
	- **isize和usize类型依赖计算机的架构：64位架构上他们是64位的，32位架构上是32位的**
	- 在Rust中，数字字面值可以使用下划线分割

| 数字字面值 | 例子 |
| --- | --- |
| Decimal(十进制) | 98_222 | 
| Hex(十六进制) | 0xFF | 
| Octal(八进制) | Oo77 |
| Binary(二进制) | ob1111_0000 | 
| Byte(单字节字符) | b'A' |

> 可见，其实这和C++差距不大，差距就在于**Rust可以用下划线分割以及可以在后面使用类型后缀**

##### 整形溢出

> Rust的整形溢出和C++相差无几，但是Rust更安全，**因为Rust在debug编译下溢出会直接中断程序，而在release编译下，会采取和C++一致的操作也就是假如u8类型，最大值是255,那么如果是256就被记作0,依次类推**

- 同时，Rust在标准库中显示的定义了几个功能，来确保万一你需要处理溢出：
	- wrapping_\*方法，如wrapping_add，这就是如上所说的256变成0
	- check_\*方法，如果出现溢出，则返回None值
	- overflowing_\*方法，返回一个布尔值，来判断是否溢出
	- saturating_\*方法，在值的最小值或者最大值进行饱和处理

##### 浮点型

| 长度 | 类型 | 长度 | 类型 |
| --- | --- | --- | --- |
| 32-bit | f32 | 64-bit | f64 |

- 注意：
	- 如果没有指定类型，那么默认是f64的
	- **所有的浮点型都是有符号的**

##### 数值运算

> Rust中所有的数字类型都支持数学运算：加法、减法、乘法、除法和取余
> 在细节上和C++一致

```rust
fn main(){
	//add
	let sum = 5 + 10;

	//sub
	let dif = 95.5 - 4.3;

	//mul
	let prod = 4 * 30;

	//div
	let quo = 56.7 / 32.2;
	let flo = 2 / 3; //Result in 0

	//remainder
	let rem = 43 % 5;
}
```

##### 布尔值

> 和C++一样，Rust中的布尔值使用bool表示：true和flase

```rust
fn main(){
	let t = true;
	let f: bool = false;
}
```

- 注意：
	- bool的主要运用场景在条件表达式上

##### 字符类型

```rust
fn main(){
	let c = 'z';
	let z: char = 'Z';
}
```

- 注意：
	- Rust和C++一样，都是使用单引号来表面单个字符，双引号做字符串字面量
	- **Rust的char类型大小为4个字节，代表了一个Unicode的标量值**

#### 复合类型

> 复合类型可以将多个值组成一个类型。Rust有两个原生的复合类型：元组和数组

##### 元组

> 元组是一个将多个其他类型的值组合进一个复合类型的主要方式。**元组长度固定，一旦声明，其长度不再变化**

- 注意：
	- **元组的内部成员的类型可以是不相同的**
	- 元组使用()来声明，内部使用 , 来分隔

```rust
fn main(){
	let _tup: (i32, f64, u8) = (500, 6.4, 1);
}
```

- 注意：
	- 对于元组来说，可以不声明类型使用默认类型，也可以主动声明
	- **Rust要求使用元组时，元组的变量名加上前置下划线不然会出现以下警告**

```linux
# carho build
   Compiling tuple v0.1.0 (/home/zack/code_work/github_work/My_Cpp_Programming/Rust/projects/tuple)
warning: unused variable: `tup`
 --> src/main.rs:2:9
  |
2 |     let tup = (500, 6.4, 1);
  |         ^^^ help: if this is intentional, prefix it with an underscore: `_tup`
  |
  = note: `#[warn(unused_variables)]` on by default

warning: `tuple` (bin "tuple") generated 1 warning
    Finished dev [unoptimized + debuginfo] target(s) in 0.11s
```

- 为了从**元组中获取单个值，要进行解构操作**
	- 解构使得元组的每一个对应位置的值，都分别放在对应变量中

```rust
fn main(){
	let _tup: (i32, f64, u8) = (500, 6.4, 1);

	let (x, y, z) = _tup;//解构
}
```

- **Rust也提供了点访问操作符，来对元组单个元素进行访问**
	- 和C++一样，Rust的索引也是从0开始

```rust
let x: (i32, f64, u8) = (500, 6.4, 1);
let five_hundred = x.0;
```

##### 数组类型

> 和其他语言一样的，RUST也提供了数组类型(`array`)。**与元组不同的是，数组中的每个元素的类型必须相同，RUST中的数组长度是固定的**

```rust
let a = [1, 2, 3, 4, 5];
```

- **如果你想要使用动态数组，那么Rust提供了`vec`类型**
- 在很多语言中，数组的类型实际上是很简单的，但是在rust中，**每一个数组都有着他自己的一个类型**：

```rust
let r1: [i32; 3] = [1, 2, 3];
let r2: [i32; 2] = [1, 2];
```

- 在上面的代码中，`r1`的类型是`[i32; 3]`，而`r2`的类型是`[i32; 2]`，这两种是不同的类型。

- 当然，你可以可以像其他语言一样，创建一个拥有大量元素的数组

```rust
let r = [0; 100];
// 以0元素来填充100位
```

### 函数

> 函数在rust代码中非常普遍，而`main`函数你已经见过很多次了，其也是很多程序的入口。

- 在Rust中，函数的定义使用`fn`关键字，其命名风格为`snake case`规范风格

```rust
fn another_function() {
	printfln!("Another Function!");
}
```

- Rust要求**在函数签名标签中，必须声明每一个参数的类型。这意味着编译期不再需要你注释指明你的意图**

```rust
fn print_labeled_measurement(value: i32, unit_label: char) {
	println!("The measurement is: {value}{unit_label}");
}
```

#### 语句与表达式

> 语句(`Statements`)是执行一些操作但不返回值的指令。  
> 表达式(`Expressions`)计算并返回一个值

- Rust是容纳了函数式编程的风格，因此，函数的返回值是可以由表达式所返回的，而每一个表达式都有一个返回值。

```rust
let y = {
	let x = 3;
	x + 1
}

println!("The value of y is: {y}");
```

- 接下来看一下函数的返回

```rust
fn plus_one(x: i32) -> i32 {
	x + 1
}
```

### 控制流

> 控制流是编程语言中最为基础的一部分，最常见的就是`if表达式`和`循环`

#### if表达式

> if 表达式允许根据条件执行不同的代码分支。你提供一个条件并表示 ” **如果条件满足，运行这段代码； 如果条件不满足，不运行这段代码。**”

```rust
let number = 7;

if number < 5 {
	println!("condition was true");
} else {
	println!("condition was false");
}
```

- 如果你学习过`C/C++`，那么一定会有一个习惯：**使用一个变量来作为一种bool值**，这样很方便也很简单，但是，在Rust中，明确规定了：**条件表达式必须是一种bool值**

##### 在let语句中使用if

> 我们知道，因为`if`是一个表达式，因此我们可以在`let`语句的右侧使用它

```rust
let condition = true;
let number = if condition { 5 } else { 6 };
println!("The value of number is: {number}");
```

- **代码块的值是其最后一个表达式的值，而数字本身就是一个表达式。同时，if的每一个分支的可能的返回值都必须是相同类型**

#### 使用循环重复执行

> 多次执行同一段代码是很常用的，Rust 为此提供了多种 循环(`loops`)。一个循环执行循环体中的代码直 到结尾并紧接着回到开头继续执行。  

##### 使用loop执行代码

> `loop`关键字告诉Rust一遍又一遍地执行一段代码直到你明确要求停止

```rust
loop {
	println!("again!");
}
```

###### 从循环返回值

> `loop`可以返回一个表达式的值作为结果

```rust
let mut counter = 0;
let result = loop {
	counter += 1;
	if counter == 10 {
		break counter * 2;
	}
}
println!("The result is {result}");
```

###### 循环标签

> 如果存在嵌套循环，`break` 和 `continue` 应用于此时最内层的循环。你可以选择在一个循环上指定一个 循环标签(`loop label`)

```rust
let mut count = 0;
'counting_up': loop {
	println!("count = {count}");
	let mut remaining = 10;

	loop {
		println!("remaining == {remaining}");
		if remaining == 9 {
			break;
		}
		if count == 2 {
			bread 'counting_up';
		}
		remaining -= 1;
	}
	count += 1;
}
println!("End count = {count}");
```

##### while条件循环

> Rust 为此内置了一个语言结构，它被称为 `while` 循环

```rust
let mut number = 3;

while number != 0 {
	println!("{number}!");
	number -= 1;
}
println!("LIFT OFF!!");
```

##### 使用for遍历集合

> 可以使用while结构来遍历集合中的元素。

```rust
let a = [10, 20, 30, 40, 50];

for element in a {
	println!("the value is: {element}");
}
```

- **`for`循环的安全性和间接性使得它成为Rust中使用最多的循环结构。**

### 所有权

> `所有权(系统)`是Rust最为与众不同的特性。**其让Rust无需垃圾回收(`garbage collector`)即可保障内存安全，因此需要了解：借用(`borrowing`)、`slice`以及Rust的数据内存布局**

#### 所有权规则

- **Rust中的每一个值都有一个被称为`所有者(owner)`的变量
- **值在任一时刻有且仅有一个所有者**
- **当所有者(变量)离开作用域，这个值会被丢弃**

#### 变量作用域

> 变量的作用域和C/C++的作用域一致，不过多了所有权这一概念

```rust
let s = "hello";
{
	let s = "world";
}
```

- 在上述中，同一个变量名`s`，其实是两个不同的变量，其内部的值是不同的

#### 内存与分配

> Rust想要实现变量的内存自动分配和销毁。在有`垃圾回收(garbage collector)`的语言中，GC记录并清楚不再使用的内存，而没有GC的语言中，则需要手动的精确的记录下每一个内存分配。

- Rust 采取了一个不同的策略：**内存在拥有它的变量离开作用域后就被自动释放**。

```rust
{
	let s = String::from("hello");
}
// 出了作用域后，s无效
```

- 当 s 离开作用域的时候。当变量离开作用域，Rust 为我们调用一个特殊的函数。这个函数叫做 `drop`。
- 在C++中，这种` item`在生命周期结束时释放资源的模式有时被称作 资源获取即初始化 (`Resource Acquisition Is Initialization (RAII)`）

#### 变量和数据交互：移动

> 在Rust中，由于所有权的存在，变量之间的转移必须是移动的。也就是所有变量都加入了类似于`std::move`一般

```rust
let s1 = String::from("hello");
let s2 = s1;
```

- 在Rust中，为了防止类似于C++中的`浅拷贝`，Rust禁止了两个变量`简单的指向同一块空间`，在进行`let s2 = s1`之后，Rust认为s1不再有效。

![[浅拷贝.png]]

- **当然的，由于在栈上的元素大多数不会涉及到所有权的问题，因此Rust中`Copy trait`决定了哪一种元素不会被`move`**

#### 所有权与函数

> 在C/C++中，你应该听说过传指针和传值，而在Rust中，就涉及到了所有权的转移的问题

```rust
fn takes_ownership(some_string: String) {
	println!("{}", some_string);
}

let s = String::form("hello");
takes_ownership(s);
```

- 通过上面的代码，我们发现，一旦`s`进入了`takes_ownership`函数，其所有权就被转交给了`some_string`，因此`s`不再有效。
- 变量的所有权总是遵循相同的模式：**将值赋给另一个变量时移动它。当持有堆中数据值的变量离开作用 域时，其值将通过 `drop `被清理掉，除非数据被移动为另一个变量所有。**

### 引用与借用

> 引用(`reference`)像一个指针，因为它是一个地址，我们可以由此访问储存于该地 址的属于其他变量的数据。与指针不同，引用确保指向某个特定类型的有效值

- 其实有点与C++相反的意思，当你对一个变量进行引用时，你相当于进行了一份浅拷贝，但**又能通过该引用修改其值**

```rust
let s1 = String::from("hello");

let ten = calculate_length(&s1);

fn calculate_length(s: &String) -> usize {
	s.len()
}
```

- 此处，我们只是将值给了s，而非转交了所有权，可以通过下图认识

![[引用.png]]

> 我们将创建一个引用的行为称为 借用(`borrowing`)。正如现实生活中，如果一个人拥有某样东西，你可 以从他那里借来。当你使用完毕，必须还回去。我们并不拥有它。

#### 可变引用

> **通过引用允许修改一个借用的值**，这就是可变引用

```rust
let mut s = String::from("hello");
change(&mut s);

fn change(some_string: &mut String) {
	some_string.push_str(", world");
}
```

- 首先，我们必须将 s 改为`mut`。然后在调用`change` 函数的地方创建一个可变引用`&mut s`，并更新函 数签名以接受一个可变引用 `some_string: &mut String`。这就非常清楚地表明，change 函数将改变它 所借用的值。
- 可变引用有一个很大的限制：**在同一时间只能有一个对某一特定数据的可变引用。这些尝试创建两个 s 的可变引用的代码会失败**

```rust
let mut s = String::from("hello"); 
let r1 = &mut s;
let r2 = &mut s;
```

- 因为Rust极度的重视内存安全，因此，如果同一时间对同一个可变变量进行借用，那么会导致可能发生的数据冲突：当`r1`和`r2`都修改了数据，那么`s`的数据根据谁来修改呢？这叫做`数据竞争(data race)`
	- 两个或更多指针同时访问同一数据。
	- 至少有一个指针被用来写入数据。
	- 没有同步数据访问的机制。
- 当然的，**我们也不能在拥有不可变引用的同时拥有可变引用**。

#### 悬垂引用

> 在具有指针的语言中，很容易通过释放内存时保留指向它的指针而错误地生成一个 `悬垂指针(dangling pointer)`，所谓悬垂指针是其指向的内存可能已经被分配给其它持有者。

- 但是， Rust编译器确保了引用永远无法成为悬垂状态

```rust
fn main() {
	let reference_to_nothing = dangle();
}

fn dangle() -> &String {
	let s = String::from("hello");
	&s
}
```

- 假如我们用C/C++的知识来看，此处应该是`局部变量的生命周期`，因此，会返回一个悬垂引用，而Rust会将其指出错误，当然Rust也有生命周期的概念

### Slice类型

> `slice`允许你引用集合中一段连续的元素序列，而不用引用整个集合。**slice 是一类引用，所以它没有所有权**。

#### 字符串slice

> 字符串 `slice(string slice)`是 String 中一部分值的引用

```rust
fn main() {
	let s = String::from("hello world");
	let hello = &[0..5];
	let world = &[6..11];
}
```

- 不同于整个 String 的引用，hello 是一个部分 String 的引用，由一个额外的 `[0..5]` 部分指定。
- 可以使用 一个由中括号中的 `[starting_index..ending_index]` 指定的 range 创建一个 slice，其中 starting_index 是 slice 的第一个位置，`ending_index` 则是 slice 最后一个位置的后一个值。
- 在其内部，slice 的数据 结构存储了 slice 的开始位置和长度，长度对应于 `ending_index` 减去 `starting_index` 的值。所以对于` let world = &s[6..11];` 的情况，world 将是一个包含指向 s 索引 6 的指针和长度值 5 的 slice。

![[string slice.png]]

- 注意：
	- **字符串 `slice range` 的索引必须位于有效的 `UTF-8` 字符边界内，如果尝试从一个多字节字符的 中间位置创建字符串 `slice`，则程序将会因错误而退出。**

```rust
fn first_word(s: &String) -> &str {
	let bytes = s.as_bytes();

	for (i, &item) in bytes.iter().enumerate() {
		if item == b' ' {
			return &[..i];
		}
	}
	&s[..]
}
```

#### 其他类型的slice

> 除了字符串，我们对数组也可以进行slice操作

```rust
let a = [1, 2, 3, 4, 5];
let slice = &a[1..3];

assert_eq!(slice, &[2, 3]);
```