# 系统编程

## GCC & G++

```linux
$ gcc/g++ [option] params [option] params
```

| 选项 | 说明 | 
| --- | --- | 
| -o | 指定生成的输出文件 |
| -E | 仅进行编译的预处理操作 |
| -S | 将C代码转化为汇编语言 |
| -c | 将汇编代码编译为二进制 |


#### 程序翻译的过程

##### 预处理

```linux
$ gcc -E mytest.c -o mytest.i
```

- 预处理做的操作为：
	- 展开头文件
	- 宏定义
	- 条件编译
	- 去注释
	- ...
- **注意：预处理之后，mytest.i文件还是C语言文件**

##### 编译

```linux
$ gcc -S mytest.i -o mytest.s
```

##### 汇编

```linux
$ gcc -c mytest.s -o mytest.o
```

- **注意：此时虽然已经是二进制文件，但是不能执行**
	- 此时，Mytest.o被叫做**可重定位目标二进制文件**

##### 链接

```linux
$ gcc mytest.o -o test
```

##### ldd命令

> 打印程序或者库文件所依赖的共享库列表

```linux
$ ldd test
	linux-vdso.so.1 (0x00007ffdc0bfd000)
	libc.so.6 => /usr/lib/libc.so.6 (0x00007f44fd3c9000)
	/lib64/ld-linux-x86-64.so.2 => /usr/lib64/ld-linux-x86-64.so.2 (0x00007f44fd5d7000)

```

## make & Makefile

> 自动化构建项目

### make

> make是一个命令

### Makefile

> Makefile是一个文件

## GDB

> [!warning] gcc/g++默认编译后的二进制文件是release版本的，无法进行调试

### readelf

> **readelf**命令用来显示一个或者多个elf格式的目标文件的信息，可以通过它的选项来控制显示哪些信息。

#### ELF文件类型

- 可重定位文件
	- 用户和其他目标文件一起创建可执行文件或者共享目标文件,例如lib*.a文件。 
- 可执行文件
	- 用于生成进程映像，载入内存执行,例如编译好的可执行文件a.out。 
- 共享目标文件
	- 用于和其他共享目标文件或者可重定位文件一起生成elf目标文件或者和执行文件一起创建进程映像，例如lib*.so文件。

#### readelf options

| option | 含义 | 
| :---: | :---: | 
| a | all 显示全部信息,等价于 -h -l -S -s -r -d -V -A -I. |
| h | file-header 显示elf文件开始的文件头信息. |
| S | sections 显示节头信息(如果有的话) |

> [!todo] h选项的测试

```linux
$ readelf -h test
ELF 头：
  Magic：   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 
  类别:                              ELF64
  数据:                              2 补码，小端序 (little endian)
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI 版本:                          0
  类型:                              DYN (共享目标文件)
  系统架构:                          Advanced Micro Devices X86-64
  版本:                              0x1
  入口点地址：               0x10c0
  程序头起点：          64 (bytes into file)
  Start of section headers:          15336 (bytes into file)
  标志：             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           56 (bytes)
  Number of program headers:         13
  Size of section headers:           64 (bytes)
  Number of section headers:         31
  Section header string table index: 30
```

> [!todo] S选项的测试

```linux
$ readelf -S test
There are 31 section headers, starting at offset 0x3be8:

节头：
  [号] 名称              类型             地址              偏移量
       大小              全体大小          旗标   链接   信息   对齐
  [ 0]                   NULL             0000000000000000  00000000
       0000000000000000  0000000000000000           0     0     0
  [ 1] .interp           PROGBITS         0000000000000318  00000318
       000000000000001c  0000000000000000   A       0     0     1
  [ 2] .note.gnu.propert NOTE             0000000000000338  00000338
       0000000000000020  0000000000000000   A       0     0     8
  [ 3] .note.gnu.build-i NOTE             0000000000000358  00000358
       0000000000000024  0000000000000000   A       0     0     4
  [ 4] .note.ABI-tag     NOTE             000000000000037c  0000037c
       0000000000000020  0000000000000000   A       0     0     4
  [ 5] .gnu.hash         GNU_HASH         00000000000003a0  000003a0
       0000000000000028  0000000000000000   A       6     0     8

$ readelf -S test-debug
[28] .debug_aranges    PROGBITS         0000000000000000  0000303b
       0000000000000030  0000000000000000           0     0     1
  [29] .debug_info       PROGBITS         0000000000000000  0000306b
       0000000000002c90  0000000000000000           0     0     1
  [30] .debug_abbrev     PROGBITS         0000000000000000  00005cfb
       0000000000000649  0000000000000000           0     0     1
  [31] .debug_line       PROGBITS         0000000000000000  00006344
       00000000000003ea  0000000000000000           0     0     1
  [32] .debug_str        PROGBITS         0000000000000000  0000672e
       0000000000001cc9  0000000000000001  MS       0     0     1
```

- 可以看见，在debug版本下，readelf会多出.debug信息

### gdb的使用

#### gdb的启动和退出

> [!warning] gdb必须调用通过-g选项生成的文件

```linux
$ gdb test_debug -q
Reading symbols from test...
(gdb) quit
```

#### gdb显示代码块

```linux
$ gdb test_debug -q
Reading symbols from test...
(gdb) list 
1	#include <iostream>
2	
3	int AddTop(int top) {
4	    int res = 0;
5	    for (int i = 0; i <= top; i++) {
6	        res += i;
7	    }
8	    return res;
9	}
10	
(gdb) 
```

> [!todo] 如果使用\[list 0] 那么就会从第一行开始显示

```linux
(gdb) l 0
1	#include <iostream>
2	
3	int AddTop(int top) {
4	    int res = 0;
5	    for (int i = 0; i <= top; i++) {
6	        res += i;
7	    }
8	    return res;
9	}
10	
(gdb) 
11	int main(int argc, char* argv[]) {
12	    int top = 100;
13	    int result = AddTop(top);
14	    std::cout << "result: " << result << std::endl;
15	    return 0;
16	}
(gdb) 
```

> [!tip] 如果gdb不输入命令直接回车，那么会执行最近一行的命令

#### gdb开始调试


```linux
(gdb) r
Starting program: test 
result: 5050
[Inferior 1 (process 20583) exited normally]
```

> [!warning] 如果没有设置断点，那么使用r指令会直接运行结束，不会停止

#### gdb添加断点和删除断点

```linux
(gdb) b 12
Breakpoint 1 at 0x55555555520e: file test_1.cc, line 12.
(gdb) d 1
```

> [!warning] 删除断点需要通过断点的编号删除

#### gdb查看断点

```linux
(gdb) info b
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x000055555555520e in main(int, char**) at test_1.cc:12
```

#### 启动和关闭(使能)断点

```linux
(gdb) info b
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x000055555555520e in main(int, char**) at test_1.cc:12
	breakpoint already hit 1 time
2       breakpoint     keep y   0x0000555555555222 in main(int, char**) at test_1.cc:14
	breakpoint already hit 1 time
(gdb) disable 2
(gdb) info b
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x000055555555520e in main(int, char**) at test_1.cc:12
	breakpoint already hit 1 time
2       breakpoint     keep n   0x0000555555555222 in main(int, char**) at test_1.cc:14
(gdb) enable 2
(gdb) info b
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x000055555555520e in main(int, char**) at test_1.cc:12
	breakpoint already hit 1 time
2       breakpoint     keep y   0x0000555555555222 in main(int, char**) at test_1.cc:14
	breakpoint already hit 1 time
```

#### 单步跟踪和单步跟踪进入

- 单步跟踪进入**如果遇到函数，则会进入函数**
- 单步跟踪**如果遇到函数，不会进入函数，当作语句执行**

```linux
(gdb) n
13	    int result = AddTop(top);
(gdb) n
14	    std::cout << "result: " << result << std::endl;
(gdb) n
result: 5050
15	    return 0;

(gdb) s
13	    int result = AddTop(top);
(gdb) s
AddTop (top=21845) at test_1.cc:3
3	int AddTop(int top) {
(gdb) s
4	    int res = 0;
```

#### 查看变量值

```linux
(gdb) n
13	    int result = AddTop(top);
(gdb) n
14	    std::cout << "result: " << result << std::endl;
(gdb) p result
$1 = 5050
```

#### 查看调用堆栈

```linux
(gdb) bt
#0  AddTop (top=100) at test_1.cc:4
#1  0x000055555555521f in main (argc=1, argv=0x7fffffffdc08) at test_1.cc:13
(gdb) 
```

#### 终止(快速执行)函数调用

```linux
(gdb) finish 
Run till exit from #0  AddTop (top=100) at test_1.cc:4
0x000055555555521f in main (argc=1, argv=0x7fffffffdc08) at test_1.cc:13
13	    int result = AddTop(top);
Value returned is $2 = 5050
```

#### 常显示的增加和删除

```linux
(gdb) display i
3: i = 0
(gdb) n
5	    for (int i = 0; i <= top; i++) {
3: i = 0
(gdb) 
6	        res += i;
3: i = 1
(gdb) 
5	    for (int i = 0; i <= top; i++) {
3: i = 1
(gdb) undisplay 3
(gdb) n
6	        res += i;
```

#### 跳转

```linux
(gdb) s
4	    int res = 0;
(gdb) l 0
1	#include <iostream>
2	
3	int AddTop(int top) {
4	    int res = 0;
5	    for (int i = 0; i <= top; i++) {
6	        res += i;
7	    }
8	    return res;
9	}
10	
(gdb) until 8
AddTop (top=100) at test_1.cc:8
8	    return res;
```

> [!warning] 注意：until最好只在函数内部跳转。**非必要，不要跳出该函数**

#### 跳转断点

```linux
Breakpoint 1, main (argc=1, argv=0x7fffffffdc08) at test_1.cc:12
12	    int top = 100;
(gdb) info b
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x000055555555520e in main(int, char**) at test_1.cc:12
	breakpoint already hit 1 time
2       breakpoint     keep y   0x0000555555555222 in main(int, char**) at test_1.cc:14
(gdb) c
Continuing.

Breakpoint 2, main (argc=1, argv=0x7fffffffdc08) at test_1.cc:14
14	    std::cout << "result: " << result << std::endl;
(gdb) info b
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x000055555555520e in main(int, char**) at test_1.cc:12
	breakpoint already hit 1 time
2       breakpoint     keep y   0x0000555555555222 in main(int, char**) at test_1.cc:14
	breakpoint already hit 1 time
```

### 附录

| 命令 | 解释 | 示例 |
| :---: | :---: | :---: |
| file <文件名> | 加载被调试的可执行程序文件。因为一般都在被调试程序所在目录下执行GDB，因而文本名不需要带路径。 | (gdb) file gdb-sample |
| r | Run的简写，运行被调试的程序。如果此前没有下过断点，则执行完整个程序；如果有断点，则程序暂停在第一个可用断点处。 | (gdb) r |
| c | Continue的简写，继续执行被调试程序，直至下一个断点或程序结束。 | (gdb) c |
| b <行号>  | b: Breakpoint的简写，设置断点。两可以使用“行号”“函数名称”“执行地址”等方式指定断点位置。 | (gdb) b 8 |
| b <函数名称>  | 其中在函数名称前面加“\*”符号表示将断点设置在“由编译器生成的prolog代码处”。| (gdb) b main |
| b \*<函数名称>  | 如果不了解汇编，可以不予理会此用法。 | (gdb) b \*main |
| b \*<代码地址> d [编号] |  d: Delete breakpoint的简写，删除指定编号的某个断点，或删除所有断点。断点编号从1开始递增。| (gdb) b \*0x804835c (gdb) d |
| s | s: 执行一行源程序代码，如果此行代码中有函数调用，则进入该函数；| (gdb) s |
| n | n: 执行一行源程序代码，此行代码中的函数调用也一并执行。 s 相当于其它调试器中的“Step Into (单步跟踪进入)”；n 相当于其它调试器中的“Step Over (单步跟踪)”。 这两个命令必须在有源代码调试信息的情况下才可以使用（GCC编译时使用“-g”参数）。 | (gdb) n |
| si | si命令类似于s命令，ni命令类似于n命令。| (gdb) si |
| ni | 所不同的是，这两个命令（si/ni）所针对的是汇编指令，而s/n针对的是源代码。 | (gdb) ni |
| p <变量名称> | Print的简写，显示指定变量（临时变量或全局变量）的值。 | (gdb) p i, (gdb) p nGlobalVar |
| display ... undisplay <编号> |  display，设置程序中断后欲显示的数据及其格式。例如，如果希望每次程序中断后可以看到即将被执行的下一条汇编指令，可以使用命令“display /i $pc”其中 $pc 代表当前汇编指令，/i 表示以十六进行显示。当需要关心汇编代码时，此命令相当有用。 undispaly，取消先前的display设置，编号从1开始递增。 | (gdb) display /i $pc (gdb) undisplay 1 |
| i | info的简写，用于显示各类信息，详情请查阅“help i”。 | (gdb) i r |
| q | Quit的简写，退出GDB调试环境。 | (gdb) q |
| help [命令名称] | GDB帮助命令，提供对GDB名种命令的解释说明。如果指定了“命令名称”参数，则显示该命令的详细说明；如果没有指定参数，则分类显示所有GDB命令，供用户进一步浏览和查询。 | (gdb) help |

## 进程

### 