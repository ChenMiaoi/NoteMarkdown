# Rust

---  

## Rust语法

### 第一个Rust程序

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

#### 编译

```Rlinux
# rustc main.rc
```

- **和C++一样，Rust是一门静态语言，也有着对应的编译器rustc**

#### 运行

```linux
# ./main
```

### Cargo

> Cargo是Rust提供的一个构建系统和包管理器。它能够处理构建代码、下载依赖库并编译等等

```linux
# cargo --version
```

#### 使用Cargo创建项目

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

#### 使用Cargo构建并运行

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

### Rust编程基本概念

#### 关键字

> 对于关键字的学习，我觉得应该跟随着语言逐步学习

| 关键字 | 说明 | 关键字 | 说明 | 关键字 | 说明 |
| --- | --- | --- | --- | --- | --- |
| let | 绑定一个变量 | mut | 表示引用、裸指针或者模式绑定的可变性 | const | 定义常量或不变裸指针 |


#### 变量和可变性

##### 不可变性

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

##### 可变性

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

##### 常量

> 类似不可变变量，**常量是绑定到一个名称的不允许改变的值**

```rust
const THREE_HOURS_IN_SECONDS: u32 = 60 * 60 * 3;
```

- 注意：
	- 常量的定义和C++一样，**const是Rust中的一个关键字**
	- 使用const修饰的常量，**不允许使用mut，且必须标明值的类型**
	- **Rust中使用 : 来声明类型，这一点会在后面提到**
	- **Rust中的常量用全大写，单词之间使用下划线来连接**

##### 隐藏

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

#### 数据类型

> 在Rust中，每一个值都有自己的一个数据类型，我们将看到**标量和复合**

> 比如：使用parse将String转换为数字时，**必须添加类型注解**
> 类型注解：Rust使用 : 来标注类型

##### 标量类型

> 标量代表一个单独的值。
> Rust中有四种的基本标量：**整形、浮点型、布尔类型和字符类型**

###### 整形

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

###### 整形溢出

> Rust的整形溢出和C++相差无几，但是Rust更安全，**因为Rust在debug编译下溢出会直接中断程序，而在release编译下，会采取和C++一致的操作也就是假如u8类型，最大值是255,那么如果是256就被记作0,依次类推**

- 同时，Rust在标准库中显示的定义了几个功能，来确保万一你需要处理溢出：
	- wrapping_\*方法，如wrapping_add，这就是如上所说的256变成0
	- check_\*方法，如果出现溢出，则返回None值
	- overflowing_\*方法，返回一个布尔值，来判断是否溢出
	- saturating_\*方法，在值的最小值或者最大值进行饱和处理

###### 浮点型

| 长度 | 类型 | 长度 | 类型 |
| --- | --- | --- | --- |
| 32-bit | f32 | 64-bit | f64 |

- 注意：
	- 如果没有指定类型，那么默认是f64的
	- **所有的浮点型都是有符号的**

###### 数值运算

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

###### 布尔值

> 和C++一样，Rust中的布尔值使用bool表示：true和flase

```rust
fn main(){
	let t = true;
	let f: bool = false;
}
```

- 注意：
	- bool的主要运用场景在条件表达式上

###### 字符类型

```rust
fn main(){
	let c = 'z';
	let z: char = 'Z';
}
```

- 注意：
	- Rust和C++一样，都是使用单引号来表面单个字符，双引号做字符串字面量
	- **Rust的char类型大小为4个字节，代表了一个Unicode的标量值**

##### 复合类型

> 复合类型可以将多个值组成一个类型。Rust有两个原生的复合类型：元组和数组

###### 元组

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

```