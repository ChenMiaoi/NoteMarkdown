# RISC-V

--- 

## GCC  

### 预处理 & 编译  

> GCC的编译和预处理是通过`CC`来处理的  

```c
#include <stdio.h>

int 
main()
{
	printf("Hello World\n");
	return 0;
}
```

- 使用`gcc -E test.c -o test.i` & `gcc -S test.i -o test.s`进行对应的操作  
- 此处，我们使用`gcc -v test.c`来查看完整的过程  

```linux
$ gcc -v test.c
Thread model: posix
gcc version 9.4.0 (Ubuntu 9.4.0-1ubuntu1~20.04.1) 
COLLECT_GCC_OPTIONS='-v' '-mtune=generic' '-march=x86-64'
 /usr/lib/gcc/x86_64-linux-gnu/9/cc1 -quiet -v -imultiarch x86_64-linux-gnu test.c -quiet -dumpbase test.c -mtune=generic -march=x86-64 -auxbase test -version -fasynchronous-unwind-tables -fstack-protector-strong -Wformat -Wformat-security -fstack-clash-protection -fcf-protection -o /tmp/ccJWCfDs.s
```

- 可以看见，在输出日志中有一行为`cc1 test.c -o /tmp/ccJWCfDs.s`，也就是说，将test.c生成了一个名为`ccJWCfDs.s`的临时汇编文件  

### 汇编  

> 通过`cc1`生成的临时汇编文件通过`as`工具来进行汇编生成可重定向目标文件  

- 使用`gcc -c test.s -o test.o`进行对应的操作  

``` linux
$ gcc -v test.c
GC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
Compiler executable checksum: c0c95c0b4209efec1c1892d5ff24030b
COLLECT_GCC_OPTIONS='-v' '-mtune=generic' '-march=x86-64'
 as -v --64 -o /tmp/cckKeIlu.o /tmp/ccJWCfDs.s
GNU assembler version 2.34 (x86_64-linux-gnu) using BFD version (GNU Binutils for Ubuntu) 2.34
```

- 从上面的输出日志中看出，`as -v --64 -o /tmp/cckKeIlu.o /tmp/ccJWCfDs.s`将刚刚由`cc1`生成的临时汇编文件编译为了`/tmp/cckKeIlu.o`可重定向目标文件  

### 链接  

> 通过`as`生成的可重定向目标文件需要经过`ld`链接器来链接各种库最后生成可执行文件`a.out`  

- 使用`gcc -o test.o -o test`  

``` linux
$ gcc -v test.c
/usr/lib/gcc/x86_64-linux-gnu/9/collect2 -plugin /usr/lib/gcc/x86_64-linux-gnu/9/liblto_plugin.so -plugin-opt=/usr/lib/gcc/x86_64-linux-gnu/9/lto-wrapper -plugin-opt=-fresolution=/tmp/ccRGCMBr.res -plugin-opt=-pass-through=-lgcc -plugin-opt=-pass-through=-lgcc_s -plugin-opt=-pass-through=-lc -plugin-opt=-pass-through=-lgcc -plugin-opt=-pass-through=-lgcc_s --build-id --eh-frame-hdr -m elf_x86_64 --hash-style=gnu --as-needed -dynamic-linker /lib64/ld-linux-x86-64.so.2 -pie -z now -z relro /usr/lib/gcc/x86_64-linux-gnu/9/../../../x86_64-linux-gnu/Scrt1.o /usr/lib/gcc/x86_64-linux-gnu/9/../../../x86_64-linux-gnu/crti.o /usr/lib/gcc/x86_64-linux-gnu/9/crtbeginS.o -L/usr/lib/gcc/x86_64-linux-gnu/9 -L/usr/lib/gcc/x86_64-linux-gnu/9/../../../x86_64-linux-gnu -L/usr/lib/gcc/x86_64-linux-gnu/9/../../../../lib -L/lib/x86_64-linux-gnu -L/lib/../lib -L/usr/lib/x86_64-linux-gnu -L/usr/lib/../lib -L/usr/lib/gcc/x86_64-linux-gnu/9/../../.. /tmp/cckKeIlu.o -lgcc --push-state --as-needed -lgcc_s --pop-state -lc -lgcc --push-state --as-needed -lgcc_s --pop-state /usr/lib/gcc/x86_64-linux-gnu/9/crtendS.o /usr/lib/gcc/x86_64-linux-gnu/9/../../../x86_64-linux-gnu/crtn.o
```

- 虽然在上述中没有出现`ld`的身影，但是可以看见，在最后一步是链接了很多的动态库和各种目标文件的  

## ELF  

> ELF (Executable Linkable Format)是一种Unix-like系统上的二进制文件格式标准  

### ELF文件格式分类  

- ELF文件格式的分类大致课分为四种：  

| ELF文件类型 | 说明 | 示例 |
| :---: | :---: | :---: | 
| 可重定位文件(RLelocatable File) | 内容包含了代码和数据，可以被链接称可执行文件或共享目标文件 | Linux上的.o文件 |
| 可执行文件(Execuatble File) | 可以直接执行的程序 | Linux上的a.out | 
| 共享目标文件(Shared Object File) | 内容包含了代码和数据，可以作为链接器的输入，在链接阶段和其他的 Relocatable File或者 Shared Object File一起链接成新的 Object File；或者在运行阶段，作为动态链接器 的输入，和 Executable File 结合，作为进程的一部分来运行 | Linux上的.so文件 |
| 核心转储文件(Core Dump File) | 进程意外终止时，系统可以将该进程的部分内容和终止时的其他状态信息保存到该文件中以供调试分析 | Linux上的core文件 |


### ELF处理工具Binutils

| 工具 | 作用 |
| :---: | :---: |
| ar | 归档文件，将多个文件打包成一个大文件 |
| as | 被`gcc`调用，输入汇编文件，输出目标文件供链接器`ld`链接 |
| ld | `GNU`链接器。被`gcc`调用，把目标文件和各种库文件结合在一起，重定位数据，并链接符号引用 |
| objcopy | 执行文件格式转换 |
| objdump | 显示`ELF`文件格式的信息 |
| readelf | 显示更多`ELF`格式文件的信息(包括DWARF调试信息) |  
| ... | ... |

### ELF文件格式  

> ELF文件的具体格式可以由下面的图例所表示  

![[ELF结构图.png]]

- 可以看见，ELF文件的格式主要由`ELF Header`、`Program Header Table`、`Section`以及`Section Header Table`组成  
- `ELF Header`存储着一些机器和该ELF文件的基本信息  

```linux
$ readelf -h test.o
ELF Header:
  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 
  Class:                             ELF64
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              REL (Relocatable file)
  Machine:                           Advanced Micro Devices X86-64
  Version:                           0x1
  Entry point address:               0x0
  Start of program headers:          0 (bytes into file)
  Start of section headers:          784 (bytes into file)
  Flags:                             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           0 (bytes)
  Number of program headers:         0
  Size of section headers:           64 (bytes)
  Number of section headers:         14
  Section header string table index: 13
```

- `Program Header Table`用于描述`segment`的特性。实际上其作为`segment`的运行视图，因此 **目标文件没有`Program Header Tabel`** 因为其不可运行。
- `Section Header Table`用来描述每个`section`的特性。因此，**`Section Header Table`管理了每一个`section`的结构和数据** 

```linux
$ readelf -SW test.o
There are 14 section headers, starting at offset 0x310:

Section Headers:
  [Nr] Name              Type            Address          Off    Size   ES Flg Lk Inf Al
  [ 0]                   NULL            0000000000000000 000000 000000 00      0   0  0
  [ 1] .text             PROGBITS        0000000000000000 000040 00001b 00  AX  0   0  1
  [ 2] .rela.text        RELA            0000000000000000 000250 000030 18   I 11   1  8
  [ 3] .data             PROGBITS        0000000000000000 00005b 000000 00  WA  0   0  1
  [ 4] .bss              NOBITS          0000000000000000 00005b 000000 00  WA  0   0  1
  [ 5] .rodata           PROGBITS        0000000000000000 00005b 00000c 00   A  0   0  1
  [ 6] .comment          PROGBITS        0000000000000000 000067 00002c 01  MS  0   0  1
  [ 7] .note.GNU-stack   PROGBITS        0000000000000000 000093 000000 00      0   0  1
  [ 8] .note.gnu.property NOTE            0000000000000000 000098 000020 00   A  0   0  8
  [ 9] .eh_frame         PROGBITS        0000000000000000 0000b8 000038 00   A  0   0  8
  [10] .rela.eh_frame    RELA            0000000000000000 000280 000018 18   I 11   9  8
  [11] .symtab           SYMTAB          0000000000000000 0000f0 000138 18     12  10  8
  [12] .strtab           STRTAB          0000000000000000 000228 000028 00      0   0  1
  [13] .shstrtab         STRTAB          0000000000000000 000298 000074 00      0   0  1
```

- `section`是程序中每一个结构的具体作用

### 练习：编译与链接

#### 练习3-1

> 使用`gcc`编译代码并使用`binutils`工具对生成的目标文件和可执行文件(ELF格式)进行分析

- 具体要求如下：
	- 编写一个简单的打印"hello world!"的程序源代码：`hello.c`
	- 对源文件进行本地编译，生成针对`x86_64`指令集架构处理器的目标文件`hello.o`
	- 查看`hello.o`的文件的`ELF Header`信息
	- 查看`hello.o`的`Section Header Table`
	- 对`hello.o`进行反汇编，并查看`hello.o`的C程序源码和机器指令对应之间的关系

- 编写源文件代码

``` c
#include <stdio.h>

int main()
{
	printf("hello world!");
	return 0;
}
```

- 进行本地编译

``` linux
$ gcc -c hello.c -o hello.o
```

- 查看`hello.o`的文件头信息

```linux
$ readelf -h hello.o
ELF Header:
  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 
  Class:                             ELF64
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              REL (Relocatable file)
  Machine:                           Advanced Micro Devices X86-64
  Version:                           0x1
  Entry point address:               0x0
  Start of program headers:          0 (bytes into file)
  Start of section headers:          800 (bytes into file)
  Flags:                             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           0 (bytes)
  Number of program headers:         0
  Size of section headers:           64 (bytes)
  Number of section headers:         14
  Section header string table index: 13
```

- 查看`hello.o`的`Section Header Table`

```linux
$ readelf -SW hello.o
There are 14 section headers, starting at offset 0x320:

Section Headers:
  [Nr] Name              Type            Address          Off    Size   ES Flg Lk Inf Al
  [ 0]                   NULL            0000000000000000 000000 000000 00      0   0  0
  [ 1] .text             PROGBITS        0000000000000000 000040 000020 00  AX  0   0  1
  [ 2] .rela.text        RELA            0000000000000000 000260 000030 18   I 11   1  8
  [ 3] .data             PROGBITS        0000000000000000 000060 000000 00  WA  0   0  1
  [ 4] .bss              NOBITS          0000000000000000 000060 000000 00  WA  0   0  1
  [ 5] .rodata           PROGBITS        0000000000000000 000060 00000d 00   A  0   0  1
  [ 6] .comment          PROGBITS        0000000000000000 00006d 00002c 01  MS  0   0  1
  [ 7] .note.GNU-stack   PROGBITS        0000000000000000 000099 000000 00      0   0  1
  [ 8] .note.gnu.property NOTE            0000000000000000 0000a0 000020 00   A  0   0  8
  [ 9] .eh_frame         PROGBITS        0000000000000000 0000c0 000038 00   A  0   0  8
  [10] .rela.eh_frame    RELA            0000000000000000 000290 000018 18   I 11   9  8
  [11] .symtab           SYMTAB          0000000000000000 0000f8 000138 18     12  10  8
  [12] .strtab           STRTAB          0000000000000000 000230 00002b 00      0   0  1
  [13] .shstrtab         STRTAB          0000000000000000 0002a8 000074 00      0   0  1
```

- 进行反汇编
	- **首先，需要生成带有debug标识的可执行二进制文件**
	- 然后再使用`objdump`进行反汇编操作

```linux
$ gcc hello.c -o hello -g

$ objdump -S hello
0000000000001149 <main>:
#include <stdio.h>

int main() 
{
    1149:       f3 0f 1e fa             endbr64 
    114d:       55                      push   %rbp
    114e:       48 89 e5                mov    %rsp,%rbp
    printf("hello world!");
    1151:       48 8d 3d ac 0e 00 00    lea    0xeac(%rip),%rdi        # 2004 <_IO_stdin_used+0x4>
    1158:       b8 00 00 00 00          mov    $0x0,%eax
    115d:       e8 ee fe ff ff          callq  1050 <printf@plt>
    return 0;
    1162:       b8 00 00 00 00          mov    $0x0,%eax
    1167:       5d                      pop    %rbp
    1168:       c3                      retq   
    1169:       0f 1f 80 00 00 00 00    nopl   0x0(%rax)
```

#### 练习3-2

> 如下例子C语言代码。请问编译为`.o`文件后`global_init`、`global_const`、`static_var`、`static_var_uninit`、`auto_var`这些变量**分别存放在哪些`section`中，`hello world!\n`这个字符串又在哪里？并尝试使用工具查看并验证你的猜测**

``` c
#include <stdio.h>

int global_init = 0x11111111;
const int global_const = 0x22222222;

int main() 
{
	static int static_var = 0x33333333;
	static int static_var_uninit;

	int auto_var = 0x44444444;
	printf("hello world!\n");
	return 0;
}
```

- 通过查询，使用了两种方法可以查看代码中对应变量在哪一些section中

> 注意，**在栈区的auto_var无法导出符号，也因此无法通过binutils工具查看。而hello world字符串也无法查看，无符号或者无导出符号，只能推断出在`.rodata`处**

- **必须带调试信息的可执行文件，才能够导出更多的信息**

##### 通过readelf查询

> 使用readelf中的`a`选项可以导出对应信息

```linux
$ gcc 3-2.c -g

$ readelf -a a.out
Section Headers:
  [Nr] Name              Type            Address          Off    Size   ES Flg Lk Inf Al
  [12] .init             PROGBITS        0000000000001000 001000 00001b 00  AX  0   0  4
  [17] .fini             PROGBITS        00000000000011e8 0011e8 00000d 00  AX  0   0  4
  [18] .rodata           PROGBITS        0000000000002000 002000 000015 00   A  0   0  4
  [19] .eh_frame_hdr     PROGBITS        0000000000002018 002018 000044 00   A  0   0  4
  [20] .eh_frame         PROGBITS        0000000000002060 002060 000108 00   A  0   0  8
  [21] .init_array       INIT_ARRAY      0000000000003db8 002db8 000008 08  WA  0   0  8
  [22] .fini_array       FINI_ARRAY      0000000000003dc0 002dc0 000008 08  WA  0   0  8
  [23] .dynamic          DYNAMIC         0000000000003dc8 002dc8 0001f0 10  WA  7   0  8
  [24] .got              PROGBITS        0000000000003fb8 002fb8 000048 08  WA  0   0  8
  [25] .data             PROGBITS        0000000000004000 003000 000018 00  WA  0   0  8
  [26] .bss              NOBITS          0000000000004018 003018 000008 00  WA  0   0  4
  [27] .comment          PROGBITS        0000000000000000 003018 00002b 01  MS  0   0  1
  [28] .debug_aranges    PROGBITS        0000000000000000 003043 000030 00      0   0  1
  [29] .debug_info       PROGBITS        0000000000000000 003073 000368 00      0   0  1
  [30] .debug_abbrev     PROGBITS        0000000000000000 0033db 000101 00      0   0  1
  [31] .debug_line       PROGBITS        0000000000000000 0034dc 000114 00      0   0  1
  [32] .debug_str        PROGBITS        0000000000000000 0035f0 0002f3 01  MS  0   0  1
  [33] .symtab           SYMTAB          0000000000000000 0038e8 0006f0 18     34  53  8
  [34] .strtab           STRTAB          0000000000000000 003fd8 000241 00      0   0  1
  [35] .shstrtab         STRTAB          0000000000000000 004219 00015a 00      0   0  1
```

- 注意，上述信息经过简化。通过`readelf -a`我们查询到其内部所有的`section header`

```linux
Symbol table '.symtab' contains 74 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
    37: 0000000000004018     1 OBJECT  LOCAL  DEFAULT   26 completed.8061
    38: 0000000000003dc0     0 OBJECT  LOCAL  DEFAULT   22 __do_global_dtors_aux_fini_array_entry
    39: 0000000000001140     0 FUNC    LOCAL  DEFAULT   16 frame_dummy
    40: 0000000000003db8     0 OBJECT  LOCAL  DEFAULT   21 __frame_dummy_init_array_entry
    41: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS 3-2.c
    42: 000000000000401c     4 OBJECT  LOCAL  DEFAULT   26 static_var_uninit.2318
    43: 0000000000004014     4 OBJECT  LOCAL  DEFAULT   25 static_var.2317
    44: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS crtstuff.c
    45: 0000000000002164     0 OBJECT  LOCAL  DEFAULT   20 __FRAME_END__
    46: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS 
    47: 0000000000003dc0     0 NOTYPE  LOCAL  DEFAULT   21 __init_array_end
    48: 0000000000003dc8     0 OBJECT  LOCAL  DEFAULT   23 _DYNAMIC
    49: 0000000000003db8     0 NOTYPE  LOCAL  DEFAULT   21 __init_array_start
    50: 0000000000002018     0 NOTYPE  LOCAL  DEFAULT   19 __GNU_EH_FRAME_HDR
    51: 0000000000003fb8     0 OBJECT  LOCAL  DEFAULT   24 _GLOBAL_OFFSET_TABLE_
    52: 0000000000001000     0 FUNC    LOCAL  DEFAULT   12 _init
    53: 00000000000011e0     5 FUNC    GLOBAL DEFAULT   16 __libc_csu_fini
    54: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_deregisterTMCloneTable
    55: 0000000000004000     0 NOTYPE  WEAK   DEFAULT   25 data_start
    56: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND puts@@GLIBC_2.2.5
    57: 0000000000004018     0 NOTYPE  GLOBAL DEFAULT   25 _edata
    58: 00000000000011e8     0 FUNC    GLOBAL HIDDEN    17 _fini
    59: 0000000000004010     4 OBJECT  GLOBAL DEFAULT   25 global_init
    60: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND __libc_start_main@@GLIBC_2.2.5
    61: 0000000000004000     0 NOTYPE  GLOBAL DEFAULT   25 __data_start
    62: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND __gmon_start__
    63: 0000000000004008     0 OBJECT  GLOBAL HIDDEN    25 __dso_handle
    64: 0000000000002000     4 OBJECT  GLOBAL DEFAULT   18 _IO_stdin_used
    65: 0000000000002004     4 OBJECT  GLOBAL DEFAULT   18 global_const
    66: 0000000000001170   101 FUNC    GLOBAL DEFAULT   16 __libc_csu_init
    67: 0000000000004020     0 NOTYPE  GLOBAL DEFAULT   26 _end
    68: 0000000000001060    47 FUNC    GLOBAL DEFAULT   16 _start
    69: 0000000000004018     0 NOTYPE  GLOBAL DEFAULT   26 __bss_start
    70: 0000000000001149    38 FUNC    GLOBAL DEFAULT   16 main
```

-  这是`readelf -a`的后续信息，我们可以发现：
	- 在第42行中，有符号`static_var_uninit.2318`的`Ndx`值为26，而26在上一个输出中的`Nr`对应的刚好是`.bss Section`
	- 因此，我们就可以依次找到对应的值，去对应各自的`Section`
	- `static_var.2317`对应`.data Section`
	- `global_init`对应`.data Section`
	- `global_const`对应`.rodata Section`

##### 通过nm查询

> 使用`nm -a`选项与`readelf -a`类似，都可以对`Section`进行查询

- nm中的一些格式信息

| 字符 | 英文释义 | 含义 |
| :---: | :---: | :---: |
| A | The symbol's value is absolute, and will not be changed by further linking. | 符号的值是绝对值，且在未来不会被更改 |
| B/b | The symbol is in the BSS data section.  This section typically contains zero-initialized or uninitialized data, although the exact behavior is system dependent. | 未初始化全局数据，也就是对应的`.bss` |
| C | The symbol is common.  Common symbols are uninitialized data. | 该符号是common，common symbol是未初始化数据段 |
| D/d | The symbol is in the initialized data section. | 已初始化全局数据，也就是`.data` |
| G/g | The symbol is in an initialized data section for small objects. | 该符号位于初始化数据段中 |
| I | The symbol is an indirect reference to another symbol. | 另一个符号的间接引用 |
| N | The symbol is a debugging symbol. | debugging符号，也就是`.debug_xxx` | 
| R/r | The symbol is in a read only data section. | 只读数据段，也就是`.rodata` |
| T/t | The symbol is in the text (code) section. | 代码段，也就是`.text` |
| U | The symbol is undefined. | 符号未定义 |
| W/w | The symbol is a weak symbol that has not been specifically tagged as a weak object symbol. | 符号为弱符号，当系统有定义符号时，使用定义符号，当系统未定义符号且定义了弱符号时，使用弱符号。|

```linux
$ nm -a a.out
0000000000000000 a 
0000000000000000 a 3-2.c
0000000000004018 b .bss
0000000000004018 B __bss_start
0000000000000000 n .comment
0000000000004018 b completed.8061
0000000000004000 d .data
0000000000004000 D __data_start
0000000000004000 W data_start
0000000000000000 N .debug_abbrev
0000000000000000 N .debug_aranges
0000000000000000 N .debug_info
0000000000000000 N .debug_line
0000000000000000 N .debug_str
0000000000001090 t deregister_tm_clones
0000000000002004 R global_const
0000000000004010 D global_init
0000000000003fb8 d _GLOBAL_OFFSET_TABLE_
                 w __gmon_start__
0000000000000318 r .interp
0000000000002000 R _IO_stdin_used
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
0000000000001149 T main
0000000000001050 t .plt.sec
                 U puts@@GLIBC_2.2.5
00000000000010c0 t register_tm_clones
0000000000000520 r .rela.dyn
00000000000005e0 r .rela.plt
0000000000002000 r .rodata
0000000000001060 T _start
0000000000004014 d static_var.2317
000000000000401c b static_var_uninit.2318
0000000000001060 t .text
0000000000004018 D __TMC_END__
```

- 可以在上述的输入信息中发现对应的变量其所对应的字符，然后通过查询得知其对应的`Section`

```txt
0000000000002004 R global_const
0000000000004010 D global_init
0000000000002000 R _IO_stdin_used
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
0000000000004014 d static_var.2317
000000000000401c b static_var_uninit.2318
```

## 嵌入式开发

> 嵌入式开发是一种综合性的技术，不单指纯粹的软件开发技术，也不单是一种硬件配置技术，是在特定的硬件环境下针对某款硬件进行开发，是一种系统级别的与硬件结合比较紧密的软件开发技术

### 交叉编译

> 交叉编译在嵌入式中非常常见，因为各种目标机平台的不同，因此需要交叉编译

- 参与编译核运行的机器可分为以下三类：
	- 构建系统(`build`)：**执行编译构建动作**的计算机
	- 主机系统(`host`)：**运行build系统生成的可执行程序**的计算机
	- 目标系统(`target`)：**特别地，当以上生成的可执行程序是`GCC`时，我们用`target`来描述用来运行`GCC`讲生成的可执行程序**的计算机
- 因此，我们的编译方式可以有以下分类：
	- **本地编译(`native`)**：build == host == target
	- **交叉编译(`cross`)**：build == host != target

> 而我们所要学习的正是交叉编译链：`riscv64-unkown-elf-gcc`

![[riscv-toolchain.png]]

``` c
#include <stdio.h>

int main()
{
	printf("hello world\n");
	return 0;
}
```

- 使用交叉编译工具链进行编译

```linux
$ riscv64-unknown-elf-gcc -march=rv32im -mabi=ilp32 hello.c
```

#### 安装riscv-gnu-toolchain

> 我们所使用的环境是基于RISVC架构的裸机开发，因此需要自行编译工具链

- 首先下载需要的依赖(Ubuntu)

```linux
$ sudo apt-get update
$ sudo apt-get install autoconf automake autotools-dev curl python3 libmpc-dev libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib1g-dev libexpat-dev ninja-build
```

- 从官方拉去官方源 -> 该过程较慢，官方称有6.5G大小

```git
git clone --recursive https://github.com/riscv-collab/riscv-gnu-toolchain.git
```

- 进入该文件夹配置需要下载的架构
- 因为我们需要使用32位架构，此处使用`--enable-multi`编译64bit和32bit

```linux
$ ./configure --prefix=/opt/riscv --enable-multi
```

- `--prefix`：设置默认安装的路径
- `--enable-multi`：同时编译32位和64位

- 配置无误后，会在该文件夹下生成`Makefile`

```linux
$ sudo make -j$(nproc)
```

- 根据实际，**同时编译32&64 12核应该在1h左右**

#### QEMU

- 准备依赖

``` linux
$ sudo apt install autoconf automake autotools-dev curl libmpc-dev libmpfr-dev libgmp-dev \
                 gawk build-essential bison flex texinfo gperf libtool patchutils bc \
                 zlib1g-dev libexpat-dev git \
                 libglib2.0-dev libfdt-dev libpixman-1-dev \
                 libncurses5-dev libncursesw5-dev
```

> 我们有了交叉编译工具链后，还需要能够运行的平台。而`qemu`则能够支持编译运行

- 在官方网站下载编码进行编译

```linux
$ wget https://download.qemu.org/qemu-7.0.0.tar.xz
$ tar xvJf qemu-7.0.0.tar.xz
```

- **后面的版本号可以根据需要自行修改**

- 配置编译qemu

``` linux
$ ./configure --target-list=riscv64-softmmu,riscv64-linux-user --prefix=/opt/qemu
$ make -j$(nproc)
$ sudo make install
```

- `--prefix`：默认的安装路径
- `--enable-kvm`：支持kvm虚拟机
- `--target-list`：支持的架构

#### 配置PATH

> 由于我们自定义了其安装路径，因此我们需要自行指出路径

``` linux
$ vim .bashrc

export PATH=$PATH:/home/user/riscv-tool/bin:/opt/qemu/bin
```

### Make

> `make`是一种自动化工程管理工具

#### Makefile

>  `Makefile`：配合`make`，用于描述构建工程中所管理的对象以及如何构建工程的过程

- Makefile由一条或多条规则组成，而每条规则都有三要素
	- `target`：目标，可以是`obj`文件也可以是可执行文件
	- `prerequisites`：生成`target`所需要的依赖
	- `command`：为了生成`target`需要执行的命令，可以由多条

### 练习：使用riscv工具链

#### 练习4-1

> 熟悉交叉编译概念，使用`riscv gcc`编译代码并使用`binutils`工具对生成的目标文件核可执行文件(ELF格式)进行分析

- 具体要求如下
	- 编写一个简单的打印"hello world！"的程序源文件：`hello.c`
	- 对源文件进行编译，生成针对支持`rv32im`指令集架构处理器的目标文件`hello.o`
	- 查看`hello.o`的文件的文件头信息
	- 查看`hello.o`的`Section Header Table`
	- 对`hello.o`反汇编，并查看`hello.c`的C程序源码和机器指令的对应关系

- 首先先编写源文件`hello.c`

``` c
#include <stdio.h>

int main()
{
	printf("hello world!\n");
	return 0;
}
```

- 通过`riscv gcc`对源文件进行编译，此处使用`Makefile`

``` Makefile
GCC=riscv64-unknown-elf-gcc
ARCH=-march=rv32im
ABI=-mabi=ilp32
QEMU=qemu-riscv32
DEBUG=-g

hello:hello.o
    $(GCC) $(ARCH) $(ABI) $^ -o $@
hello.o:hello.c
    $(GCC) $(ARCH) $(ABI) $^ -c $@

.PHONY:run
run:
    $(QEMU) ./hello

.PHONY:debug
debug:
    $(GCC) $(ARCH) $(ABI) hello.c -c hello.o $(DEBUG)
    $(GCC) $(ARCH) $(ABI) hello.o -o hello $(DEBUG)

.PHONY:clean
clean:
    rm -rf hello hello.o
```

- 通过`make`以及编写好的`Makefile`对源文件进行编译，同时生成`hello.o`和可执行文件`hello`

```linux
$ make
riscv64-unknown-elf-gcc -march=rv32im -mabi=ilp32 hello.c -c hello.o
riscv64-unknown-elf-gcc -march=rv32im -mabi=ilp32 hello.o -o hello
```

- 使用`readelf`查看文件头

```linux
$ riscv64-unknown-elf-readelf -h hello.o
ELF Header:
  Magic:   7f 45 4c 46 01 01 01 00 00 00 00 00 00 00 00 00 
  Class:                             ELF32
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              REL (Relocatable file)
  Machine:                           RISC-V
  Version:                           0x1
  Entry point address:               0x0
  Start of program headers:          0 (bytes into file)
  Start of section headers:          592 (bytes into file)
  Flags:                             0x0
  Size of this header:               52 (bytes)
  Size of program headers:           0 (bytes)
  Number of program headers:         0
  Size of section headers:           40 (bytes)
  Number of section headers:         11
  Section header string table index: 10
```

- 查看`Section Header Table`

```linux
$ riscv64-unknown-elf-readelf -S hello.o
There are 11 section headers, starting at offset 0x250:

Section Headers:
  [Nr] Name              Type            Addr     Off    Size   ES Flg Lk Inf Al
  [ 0]                   NULL            00000000 000000 000000 00      0   0  0
  [ 1] .text             PROGBITS        00000000 000034 000038 00  AX  0   0  4
  [ 2] .rela.text        RELA            00000000 0001b4 000048 0c   I  8   1  4
  [ 3] .data             PROGBITS        00000000 00006c 000000 00  WA  0   0  1
  [ 4] .bss              NOBITS          00000000 00006c 000000 00  WA  0   0  1
  [ 5] .rodata           PROGBITS        00000000 00006c 00000d 00   A  0   0  4
  [ 6] .comment          PROGBITS        00000000 000079 00001c 01  MS  0   0  1
  [ 7] .riscv.attributes RISCV_ATTRIBUTE 00000000 000095 00002a 00      0   0  1
  [ 8] .symtab           SYMTAB          00000000 0000c0 0000c0 10      9  10  4
  [ 9] .strtab           STRTAB          00000000 000180 000031 00      0   0  1
  [10] .shstrtab         STRTAB          00000000 0001fc 000054 00      0   0  1
```

- 使用`objdump`进行反汇编

```linux
$ riscv64-unknown-elf-objdump -S hello.o
hello.o:     file format elf32-littleriscv


Disassembly of section .text:

00000000 <main>:
   0:   ff010113                add     sp,sp,-16
   4:   00112623                sw      ra,12(sp)
   8:   00812423                sw      s0,8(sp)
   c:   01010413                add     s0,sp,16
  10:   000007b7                lui     a5,0x0
  14:   00078513                mv      a0,a5
  18:   00000097                auipc   ra,0x0
  1c:   000080e7                jalr    ra # 18 <main+0x18>
  20:   00000793                li      a5,0
  24:   00078513                mv      a0,a5
  28:   00c12083                lw      ra,12(sp)
  2c:   00812403                lw      s0,8(sp)
  30:   01010113                add     sp,sp,16
  34:   00008067                ret
```

#### 练习4-2

> 基于4-1继续熟悉qemu/gdb等工具

- 具体要求如下：
	- 将`hello.c`编译为可调试版本的可执行程序
	- 先执行`qemu-riscv32`运行`hello`
	- 使用`qemu-riscv32`和`gdb`调试`hello`

- 在上面，我们通过`Makefile`可以构建出带有调试信息的可执行文件

```linux
$ make debug
riscv64-unknown-elf-gcc -march=rv32im -mabi=ilp32 hello.c -c hello.o -g
riscv64-unknown-elf-gcc -march=rv32im -mabi=ilp32 hello.o -o hello -g
```

 - 使用`qemu-rv32`运行

```linux
$ make run
qemu-riscv32 ./hello
hello world!
```

##### 使用qemu & gdb进行调试

- 第一步，我们需要通过qemu来启动程序(原则上已经生成可调试的执行文件)

```linux
$ qemu-riscv32 -singlestep -g 8081 hello
```

- 此时，qemu已经通过该命令加载了程序
	- `-g`：wait gdb connection to `port`
- **需要注意的是，执行成功后，需要在另外一个窗口执行接下来的操作**

- 使用`gdb`进入调试模式

```linux
$ riscv64-unknown-elf-gdb hello
```

- **进入后需要执行`target remote localhost:port`来连接qemu**

```linux
(gdb) target remote localhost:8081
Remote debugging using localhost:8081
0x000100dc in _start ()
```

- 此时就可以和`gdb`正常操作调试一致

```linux
(gdb) l
1       #include <stdio.h>
2
3       int main() 
4       {
5           printf("hello world!\n");
6           return 0;
7       }
(gdb) b 5
Breakpoint 1 at 0x1019c: file hello.c, line 5.
(gdb) c
Continuing.
Breakpoint 1, main () at hello.c:5
5           printf("hello world!\n");
(gdb) n
6           return 0;
(gdb) n
7       }
(gdb) n
0x00010124 in _start ()
```

- 需要注意的是，在远程连接状态下，gdb无法使用run命令
- 使用`gdb`查看汇编

```linux
(gdb) disassemble main 
Dump of assembler code for function main:
   0x0001018c <+0>:     addi    sp,sp,-16
   0x00010190 <+4>:     sw      ra,12(sp)
   0x00010194 <+8>:     sw      s0,8(sp)
   0x00010198 <+12>:    addi    s0,sp,16
   0x0001019c <+16>:    lui     a5,0x13
   0x000101a0 <+20>:    addi    a0,a5,1408 # 0x13580
   0x000101a4 <+24>:    jal     ra,0x10408 <puts>
   0x000101a8 <+28>:    li      a5,0
   0x000101ac <+32>:    mv      a0,a5
   0x000101b0 <+36>:    lw      ra,12(sp)
   0x000101b4 <+40>:    lw      s0,8(sp)
   0x000101b8 <+44>:    addi    sp,sp,16
   0x000101bc <+48>:    ret
End of assembler dump.
```

#### 练习4-3

> 自学`Makefile`语法，理解下面代码的含义

```Makefile
SECTIONS = \
	code/asm \
	code/os \

.DEFAULT_GOAL := all
all :
	@echo "begin compile ALL exercises for assembly samples ......................."
	for dir in $(SECTIONS); do $(MAKE) -C $$dir || exit "$$?"; done
	@echo "compile ALL exercises finished successfully! ......"

.PHONY : clean
clean:
	for dir in $(SECTIONS); do $(MAKE) -C $$dir clean || exit "$$?"; done

.PHONY : slides
slides:
	rm -f ./slides/*.pdf
	soffice --headless --convert-to pdf:writer_pdf_Export --outdir ./slides ./docs/ppts/*.pptx
```

## RISC-V asm

### 汇编语言介绍

> 汇编语言(Assembly Language)是一种“低级”语言。

- 汇编语言的缺点很明显：
	- 难读
	- 难写
	- 难移植
- 但是优点又能够使其不断发展：
	- 灵活
	- 强大
- 汇编语言常用于**需要直接访问底层硬件的地方，需要对性能执行极致优化的地方**

### RV32介绍

#### 基本信息

- 寄存器
	- rv中有32个通用寄存器，x0~x31
	- 在rv中，Hart(**rv中的术语，指CPU执行流**)在执行算术逻辑运算时所操作的数据必须来自寄存器
- 内存
	- Hart可以执行寄存器和内存之间的数据读写操作
	- 读写操作使用字节为基本单位进行寻址
	- rv32最多可以访问$2^{32}$字节的内存空间

- 此处是rv32中的通用寄存器组所带的特殊含义

![[RV32 Register.png]]

#### 汇编指令编码格式

> RV32中具有六种编码格式，每一种格式内部的指令序列都有一定的差异

![[code type.png]]

- 编码解释：
	- opcode：判断一个编码的类型，首先通过该field中的6~2位判断
	- funct3/funct7：配合opcode能够决定一个具体的汇编指令
	- rd：register destination，目的寄存器
	- rs：register source，源寄存器
	- imm：immediate，立即数

![[opcode table.png]]

- 类型解释：
	- R-type：`Register`，每条指令中带有三个`fields`，用于指定3个寄存器参数
	- I-type：`Immediate`，每条指令除了带有两个寄存器之外，还带有一个立即数参数(其宽度为12bits)
	- S-type：`Store`，每条指令除了带有两个寄存器参数外，还带有一个立即数参数
	- B-type：`Branch`，每条指令除了带有两个寄存器参数外，还带有一个立即数参数(取值为2的倍数)
	- U-type：`Upper`，每条指令含有一个寄存器参数再加上一个立即数参数(宽度为20bits)
	- J-type：`Jump`，每条指令含有一个寄存器参数再加上一个立即数参数(宽度为20bits)

#### 算术运算指令

##### ADD

> 在RV32中，提供了add的汇编指令

- ADD汇编指令编码格式

![[ADD type.png]]

- 格式解析：
	- opcode(7)：011 0011对应表中的`OP`类型操作
	- funct3取值000
	- funct7取值000 0000
	- rs1(5)：第一个operand
	- rs2(5)：第二个operand
	- rd(5)：目的寄存器，存放求和结果

- 具体代码

```risc-v
# add
# Format:
#       ADD RD, RS1, RS2

    .text               # define beginning of text section
    .global _start      # define entry _start

_start:
    li x6, 1            # x6 = 1
    li x7, 2            # x7 = 2
    add x5, x6, x7      # x5 = x6 + x7

    .end                # end of file
```

- 反汇编代码

``` asm
Disassembly of section .text:

80000000 <_start>:

    .text               # define beginning of text section
    .global _start      # define entry _start

_start:
    li x6, 1            # x6 = 1
80000000:       00100313                li      t1,1
    li x7, 2            # x7 = 2
80000004:       00200393                li      t2,2
    add x5, x6, x7      # x5 = x6 + x7
80000008:       007302b3                add     t0,t1,t2
```

##### SUB

> 在RV32中，提供了sub的汇编指令

- SUB汇编指令编码格式

![[SUB type.png]]

- 格式解析：
	- opcode(7)：011 0011对应表中的`OP`类型操作
	- funct3取值000
	- funct7取值010 0000
	- rs1(5)：第一个operand
	- rs2(5)：第二个operand
	- rd(5)：目的寄存器，存放相减结果

- 具体代码

``` risc-v
# sub
# Format:
#       SUB RD, RS1, RS2

    .text
    .global _start

_start:
    li x6, -1           # x6 = -1
    li x7, -2           # x7 = -2
    sub x5, x6, x7      # x5 = x6 - x7

    .end
```

- 反汇编代码

```asm
Disassembly of section .text:

80000000 <_start>:

    .text
    .global _start

_start:
    li x6, -1           # x6 = -1
80000000:       fff00313                li      t1,-1
    li x7, -2           # x7 = -2
80000004:       ffe00393                li      t2,-2
    sub x5, x6, x7      # x5 = x6 - x7
80000008:       407302b3                sub     t0,t1,t2
```

##### ADDI

> add的立即数版本汇编指令

- ADDI汇编指令编码格式

![[ADDI type.png]]

- 格式解析：
	- opcode(7)：011 0011对应表中的`OP`类型操作
	- funct3取值000
	- imm(12)：12位立即数
	- rs1(5)：第一个operand
	- rd(5)：目的寄存器，存放相减结果

- 具体代码

```risc-v
# addi
# Format:
#       ADDI RD, RS, %imm

    .text
    .global _start

_start:
    li x6, 6            # x6 = 6
    addi x5, x6, -7;    # x5 = x6 + -7

    .end
```

- 反汇编代码

```asm
Disassembly of section .text:

80000000 <_start>:

    .text
    .global _start

_start:
    li x6, 6            # x6 = 6
80000000:       00600313                li      t1,6
    addi x5, x6, -7;    # x5 = x6 + -7
80000004:       ff930293                add     t0,t1,-7
```

- **注意**：
	- **addi指令中的立即数在参与运算前会被符号扩展为一个32位的数**
	- 该立即数的表示范围为：$[-2^{11}, +2^{11})$
	- *RISC-V*没有提供SUBI指令，因为SUBI指令可由ADDI实现

##### LUI(Load Upper Immediate)

> 由于ADDI的局限性：**立即数的范围只能是$[-2^{11}, +2^{11})$**，那么对于超出这一范围的立即数就无能为力，因此提供了LUI指令

- lui汇编指令编码格式

![[LUI type.png]]

- 格式解析：
	- opcode(7)：011 0111对应表中的`LUI`类型操作
	- imm(20)：20位立即数
	- rd(5)：目的寄存器，存放结果
- **LUI指令会构造一个32bits的立即数，这个立即数的高20位由指令中imm提供，低12位清零**

- 具体代码
- 利用LUI和ADDI指令为寄存器加载一个大数 0x12345678

```risc-v
# lui
# Format:
#       LUI RD, IMM

    .text              
    .global _start      

_start:
    lui x5, 0x12345     # int x5 = 0x12345 << 12
    addi x5, x5, 0x678  # x5 = x5 + 0x678

    .end                # End of file
```

- 加载大数 0x12345FFF
- 我们需要注意的是：**使用LUI后，剩下了0xFFF，那么经过符号扩展后，应该是0xFF..FFF**
- 因此，可以使用LUI加载大一位，然后减1

```risc-v
    .text              
    .global _start      

_start:
    lui x5, 0x12346     # int x5 = 0x12346 << 12
    addi x5, x5, -1     # x5 = x5 - 1

    .end                # End of file
```

##### AUIPC

> 除了立即数会进行符号扩展来解决位数不够的问题，地址会有由相同的问题。因此，RV提供了AUIPC(Add Upper Immediate PC)

- AUIPC汇编指令编码格式

![[AUIPC type.png]]

- 格式解析：
	- opcode(7)：001 0111对应表中的`AUIPC`类型操作
	- imm(20)：20位立即数
	- rd(5)：目的寄存器，存放结果
- **与LUI类似的，AUIPC指令会构造一个32bits的立即数，这个立即数的高20位由指令中imm提供，低12位清零。同时，在此基础上，会加上PC的值**

- 具体代码

```risc-v
# Add Upper Immediate to PC
# Format:
#       AUIPC RD, IMM

    .text               # Define beginning of text section
    .global _start      # Define entry _start

_start:
    auipc x5, 0x12345   # x5 = PC + (0x12345 << 12)
    auipc x6, 0         # x6 = PC, to obtain the current PC

    .end
```

- 反汇编代码

```asm
Disassembly of section .text:

80000000 <_start>:

        .text                       # Define beginning of text section
        .global _start              # Define entry _start

_start:
        auipc x5, 0x12345           # x5 = PC + (0x12345 << 12)
80000000:       12345297                auipc   t0,0x12345
        auipc x6, 0                 # x6 = PC, to obtain the current PC
80000004:       00000317                auipc   t1,0x0
```

##### 伪指令NEG

> NEG伪指令是由SUB汇编指令而来，其基本操作是对一个寄存器中的值进行求反

- 其对应关系为：

$$
	neg \quad rd,\  rs \Leftrightarrow sub \quad rd,\ x0,\ rs
$$

- 具体代码

``` risc-v
# neg
# Format:
#       NEG RD, RS

    .text
    .global _start

_start:
    li x6, 1           # x6 = 1
    neg x5, x6         # sub x5, x0, x6  
    sub x5, x0, x6     # x5 = x0 - x6
    # neg是伪指令，其内部汇编代码就是 sub rd, 0, rs2

    .end
```

- 反汇编代码

```asm
Disassembly of section .text:

80000000 <_start>:

    .text
    .global _start

_start:
    li x6, 1 # x6 = 1
80000000:       00100313                li      t1,1
    neg x5, x6
80000004:       406002b3                neg     t0,t1
    sub x5, x0, x6 # x5 = x0 - x6
80000008:       406002b3                neg     t0,t1
```

##### 伪指令MV

> MV伪指令是由ADDI汇编指令而来，其基本操作是对一个寄存器中的值拷贝到另一个寄存器

- 其对应关系为：

$$
	mv \quad rd,\ rs \Leftrightarrow addi \quad rd,\ rs,\ x0
$$

- 具体代码

```risc-v
# mv
# Format:
#       MV RD, RS

    .text
    .global _start

_start:

    li x6, 30           # x6 = 30
    mv  x5, x6          # x5 = x6
    addi x5, x6, 0;     # x5 = x6 + 0  
    # mv是一条伪指令，其内部汇编为addi rd, rs1, 0

    .end
```

- 反汇编代码

```asm
Disassembly of section .text:

80000000 <_start>:

    .text
    .global _start

_start:
    li x6, 30 # x6 = 30
80000000:       01e00313                li      t1,30
    mv  x5, x6 # x5 = x6
80000004:       00030293                mv      t0,t1
    addi x5, x6, 0; # x5 = x6 + 0  
80000008:       00030293                mv      t0,t1
```

##### 伪指令NOP

> MOP伪指令是由ADDI汇编指令而来，其基本操作是空操作

- 其对应关系为

$$
	nop \Leftrightarrow addi \quad x0,\ x0, 0
$$

- 具体代码

```risc-v
# nop
# Format:
#       NOP

    .text
    .global _start

_start:
    nop
    addi x0, x0, 0; # x0 = x0 + 0
    # nop是一条伪指令，其内部汇编为addi x0, x0, 0
```

- 反汇编代码

```asm
Disassembly of section .text:

80000000 <_start>:

    .text
    .global _start

_start:
    nop
80000000:       00000013                nop
    addi x0, x0, 0; # x0 = x0 + 0
80000004:       00000013                nop
```

##### 伪指令LI

> 由于ADDI会使imm立即数进行符号扩展导致一些意料之外的事情发生，因此为了方便且自动选择合适的方法赋值，RV提供了LI汇编伪指令

- **编译器会根据IMM的实际情况自动生成正确的真实指令**

- 具体代码

```risc-v
# Load Immediate
# Format:
#       LI RD, IMM

    .text
    .global _start

_start:
    # 如果立即数的范围在[-2048, +2048)
    li x5, 0x80             # x5 = 0x80
    # 以下是等价汇编指令
    addi x5, x0, 0x80;      # x5 = x0 + 0x80

    # 如果立即数的范围不在[-2048, +2048)且最高符号位是0
    li x6, 0x12345001       # x6 = 0x12345001
    # 以下是等价汇编指令
    lui x6, 0x12345
    addi x6, x6, 0x001;     # x6 = x6 + 0x001

    # 如果立即数的范围不在[-2048, +2048)且最高符号位是1
    li x7, 0x12345FFF # x7 = 0x12345FFF
    # 以下是等价汇编指令
    lui x7, 0x12346
    addi x7, x7, -1; # x7 = x7 + -1

    .end
```

- 反汇编代码

```asm
Disassembly of section .text:

80000000 <_start>:
    .text
    .global _start

_start:
    # 如果立即数的范围在[-2048, +2048)
    li x5, 0x80             # x5 = 0x80
80000000:       08000293                li      t0,128
    # 以下是等价汇编指令
    addi x5, x0, 0x80;      # x5 = x0 + 0x80
80000004:       08000293                li      t0,128
    
    # 如果立即数的范围不在[-2048, +2048)且最高符号位是0
    li x6, 0x12345001       # x6 = 0x12345001
80000008:       12345337                lui     t1,0x12345
8000000c:       00130313                add     t1,t1,1 # 12345001 <_start-0x6dcbafff>
    # 以下是等价汇编指令
    lui x6, 0x12345
80000010:       12345337                lui     t1,0x12345
    addi x6, x6, 0x001;     # x6 = x6 + 0x001
80000014:       00130313                add     t1,t1,1 # 12345001 <_start-0x6dcbafff>
    
    # 如果立即数的范围不在[-2048, +2048)且最高符号位是1
    li x7, 0x12345FFF # x7 = 0x12345FFF
80000018:       123463b7                lui     t2,0x12346
8000001c:       fff38393                add     t2,t2,-1 # 12345fff <_start-0x6dcba001>
    # 以下是等价汇编指令
    lui x7, 0x12346
80000020:       123463b7                lui     t2,0x12346
    addi x7, x7, -1; # x7 = x7 + -1
80000024:       fff38393                add     t2,t2,-1 # 12345fff <_start-0x6dcba001>
```

##### 伪指令LA

> 和LI汇编指令一样的，LA指令是为了AUIPC指令中自行编译为具体实际汇编的指令

- 其在具体编程时给出需要加载的label，编译器会根据实际情况利用AUIPC和其他指令自动生成正确的指令序列
- **常用于加载一个函数或变量的地址**

- 具体代码

```risc-v
# Load Address
# Format:
#       LA RD, Address

    .text
    .global _start

_start:
    la x5, _start       # 
    jr x5               # jump to x5
    
    .end
```

- 反汇编代码

```asm
Disassembly of section .text:

80000000 <_start>:

    .text
    .global _start

_start:
    la x5, _start       # 
80000000:       00000297                auipc   t0,0x0
80000004:       00028293                mv      t0,t0
    jr x5               # jump to x5
80000008:       00028067                jr      t0 # 80000000 <_start>
```

##### 算术运算指令总结

![[Algorithm Instruction.png]]

### 练习

#### 练习5-1

> 对sub指令执行反汇编，查看`sub x5, x6, x7`这条汇编指令对应的机器指令的编码，并对照RISC-V的specification解析这条指令的编码

``` risc-v
# sub
# Format:
#       SUB RD, RS1, RS2

    .text
    .global _start

_start:
    li x6, -1           # x6 = -1
    li x7, -2           # x7 = -2
    sub x5, x6, x7      # x5 = x6 - x7

stop:
    j stop

    .end
```

``` linux
$ make code
test.elf:     file format elf32-littleriscv


Disassembly of section .text:

80000000 <_start>:

    .text
    .global _start

_start:
    li x6, -1           # x6 = -1
80000000:       fff00313                li      t1,-1
    li x7, -2           # x7 = -2
80000004:       ffe00393                li      t2,-2
    sub x5, x6, x7      # x5 = x6 - x7
80000008:       407302b3                sub     t0,t1,t2

8000000c <stop>:
    
stop:
    j stop
8000000c:       0000006f                j       8000000c <stop>
```

- 可以看见，sub对应的机器码为：`0x407302b3`，查询RISC-V手册，得到：

| 指令 | 31-25 | 24-20 | 19-15 | 14-12 | 11-7 | 6-0 |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| sub | 0100000 | rs2 | rs1 | 000 | rd | 0110011 |  

- 将对应的机器码`0x407302b3`分解：
	- 0x407302b3 = 0100 0000 0111 0011 0000 0010 1011 0011
	- 31~25：010 0000 
	- 24~20：0 0111 rs2寄存器：对应的是x7寄存器
	- 19~15：0 0110 rs1寄存器：对应的是x6寄存器
	- 14~12：000 
	- 11~7：0 0101 目的寄存器：对应的是x5寄存器
	- 6~0：011 0011 sub对应的操作码
		- 其中，6~5取01，4~2取100对应的是OP类型指令

> 现知道某条RISC-V的机器指令在内存中的值为：`b3 05 95 00`，从左往右从低地址到高地址，单位为字节，请翻译为对应的汇编指令

- 因为rv汇编是小端序，因此需要转化为：`00 95 05 b3`
- 将对应的机器码`00 95 05 b3`分解：
	- 0x00 95 05 b3 = 0000 0000 1001 0101 0000 0101 1011 0011
	- 进行查表，通过6~5取01，4~2取100可以查到为`OP`类型指令，也就是只能在`ADD`、`SUB`等OP类型中
	- 查询14~12位取000，查表可得为`ADD`指令
	- 也就是说该指令大致为：ADD rd, rs1, rs2
	- 查询11~7得到rd为：0 1011即x11寄存器
	- 查询19~15得到rs1为：0 1010即x10寄存器
	- 查询24~20得到rs2为：0 1001即x9寄存器
- 因此整体的汇编指令为：

```risc-v
add x11, x10, x9
```