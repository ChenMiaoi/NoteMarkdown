## 1.1节练习

### 练习1

> 编译器和解释器之间的区别是什么？

- 编译器是程序，将某种语言的源代码翻译为一个等价的、用另一种语言编写的程序。
- 解释器通过用户提供的输入执行源和源程序，逐行的进行分析并得出结果

### 练习2

> 编译器相对于解释器的优点是什么？解释器相对于编译器的优点是什么？

- 编译器的优点
	- 产生目标文件的速度更快
	- 优化能力强
	- 可移植性好
- 解释器的优点
	- 灵活性高
	- 错误提醒能力好

### 练习3

> 在一个语言处理系统中，编译器产生汇编语言而不是机器语言的好处？

- 汇编语言便于调试和输出
- 可读性更高
- 便于移植(相较于机器语言)

### 练习4

> 把高级语言翻译为另一种高级语言的编译器称为源到源(source-to-source)的翻译器。编译器使用C语言作为目标语言有什么好处？

- 可移植性好，C语言在几乎所有主流的操作系统和平台上都有对应的支持
- 性能优化，C语言是一种底层的、高性能的编程语言
- 可读性和可维护性，C相较于更底层的低级语言具有较高的可读性和可维护性

### 练习5

> 描述一下汇编器所要完成的一些任务

1. **词法分析和语法分析**：汇编器首先对输入的汇编语言代码进行词法分析和语法分析。词法分析将源代码分解为词法单元（tokens），如指令、操作数、标签等。语法分析将词法单元组织成语法结构，如指令序列、标签引用等。
2. **符号解析和地址分配**：汇编器在进行符号解析时，将标签与其对应的内存地址关联起来。当遇到标签引用时，汇编器会查找标签的地址，并将其替换为相应的内存地址。地址分配阶段将指令和数据分配到内存中的适当位置。
3. **生成机器码**：汇编器根据汇编语言指令的操作码、操作数和地址信息，生成对应的机器码。机器码是由二进制表示的指令和数据，可以被计算机直接执行。
4. **生成目标文件**：汇编器将生成的机器码和其他相关信息组合成目标文件。目标文件通常包含可执行代码、数据段、符号表等。目标文件可以被链接器进一步处理，生成最终的可执行文件。
5. **错误检查和报告**：汇编器会进行错误检查，包括语法错误、符号错误、地址溢出等。如果发现错误，汇编器会生成相应的错误报告，指示出错误的位置和原因。
6. 汇编器的任务是将汇编语言代码转换为机器语言，以便计算机能够执行。它起到了连接高级语言和底层硬件的桥梁作用，是程序开发过程中不可或缺的一环。

## 1.6节练习

### 练习1

> 对下列块结构的C代码，指出赋给w、x、y和z的值

``` cpp
int w, x, y, z;
int i = 4; int j = 5;
{
	int j = 7;
	i = 6;
	w = i + j;
}
x = i + j;
{
	int i = 8;
	y = i + j;
}
z = i + j;
```

- w = 6 + 7 = 13
- x = 6 + 5 = 11
- y = 8 + 5 = 13
- z = 6 + 5 = 11

### 练习2

> 重复练习

``` cpp
int w, x, y, z;
int i = 3; int j = 4;
{
	int j = 5;
	w = i + j;
}
x = i + j;
{
	int j = 6;
	i = 7;
	y = i + j;
}
z = i + j;
```

- w = 3 + 5 = 8
- x = 3 + 4 = 7
- y = 6 + 7 = 13
- z = 7 + 4 = 11

### 练习3

> 对于下面的块结构代码，假设使用常见的声明的静态作用域规则，给出其中12个声明的每一个作用域

``` cpp
{
	int w, x, y, z;    // all
	{
		int x, z;      // B2, B3
		{
			int w, x;  // B3
		} /* B3 */
	} /* B2 */
	{
		int w, x;      // B4, B5
		{
			int y, z;  // B5
		} /* B5 */
	} /* B4 */
} /* B1 */
```

### 练习4

> 下面C代码打印结果是什么?

``` cpp
#define a (x + 1)
int x = 2;
void b () { x = a; printf("%d\n", x); }
void c () { int x = 1; printf("%d\n", a); }
void main () { b(); c(); }
```

- 3和2
