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

#### 依赖关系

#### 依赖方法