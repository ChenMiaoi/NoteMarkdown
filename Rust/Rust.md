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
| let | 绑定一个变量 | mut | 表示引用、裸指针或者模式绑定的可变性 | | |


#### 变量和可变性

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

#### 变量和可变性

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

