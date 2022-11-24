> [!todo] 要求：必须使用markdown语法，将题目解答写入markdown文件中

> 做题注意事项：
> 1. 不允许打开浏览器
> 2. 不允许查询任何相关资料
> 4. 不允许猜答案，如果不会，直接跳过
> 5. 不允许不使用markdown语法
> 7. 不允许通过运行代码得到答案，只允许通过口算或草稿本计算得到答案
> 8. 必须对每个答案为什么错，错在哪，为什么对，对在哪，有了解

## 第一题 

```txt
关于C语言关键字说法正确的是:()
A .关键字可以自己创建

B .关键字不能自己创建

C .关键字可以做变量名

D .typedef不是关键字
```

## 第二题

```c++
/*
	(代码编写)将一个四位数，反向输出。
	输入描述：
		一行，输入一个整数n（1000 <= n <= 9999）。
	输出描述：
		针对每组输入，反向输出对应四位数。
*/
```

## 第三题

```txt
关于static说法不正确的是：()
A .static可以修饰局部变量

B .static可以修全局变量

C .static修饰的变量不能改变

D .static可以修饰函数
```

## 第四题

```c++
// 下面代码的结果是什么？（ ）
#include <stdio.h>
int sum(int a)
{
    int c = 0;
    static int b = 3;
    c += 1;
    b += 2;
    return (a + b + c);
}
int main()
{
    int i;
    int a = 2;
    for (i = 0; i < 5; i++) 
    { 
        printf("%d,", sum(a)); 
    } 
}
```

## 第五题

```txt
关于指针说法正确的是：（ ）
A .sizeof(char*)大小一定是1

B .指针变量是个变量，用来存放地址

C .指针变量的大小都是4个字节

D .指针不是变量
```

## 第六题

```txt
关于函数调用说法不正确的是：（ ）
A .函数可以传值调用，传值调用的时候形参是实参的一份临时拷贝

B .函数可以传址调用，传址调用的时候，可以通过形参操作实参

C .函数可以嵌套定义，但是不能嵌套调用

D .函数可以嵌套调用，但是不能嵌套定义
```

## 第七题

```txt
关于实参和形参描述错误的是：（ ）
A .形参是实参的一份临时拷贝

B .形参是在函数调用的时候才实例化，才开辟内存空间

C .改变形参就是改变实参

D .函数调用如果采用传值调用，改变形参不影响实参
```

## 第八题

```c++
// 根据下面递归函数：调用函数Fun(2)，返回值是多少（ ）
int Fun(int n)      
{ 
  if(n==5)   
    return 2;     
  else     
    return 2*Fun(n+1);      
}
```

>[!warning] 做到此处提醒我讲解递归函数 -- 斐波那契数列

```c++
/*
	斐波那契数列
*/

int fibonacci(int n) {
	if (n == 1 || n == 2) {
		return 1;
	}
	return fibonacci(n - 1) + fibonacci(n - 2);
}

int fibonacci(int n, int) {
	if (n <= 2) {
		return 1;
	}
	int temp = 0, num1 = 0, num2 = 0;
	for (int i = 0; i >= n - 2; i--) {
		temp = num1 + num2;
		num1 = num2;
		num2 = temp;
	}
	return temp;
}
```

## 第九题

```c++
/*
	计算一个数的每位之和（递归实现）
		写一个递归函数DigitSum(n)，输入一个非负整数，返回组成它的数字之和
		例如，调用DigitSum(1729)，则应该返回1+7+2+9，它的和是19
	输入：
		1729
	输出：
		19
*/
```

## 第十题

```c++
/*
	编写一个函数 reverse_string(char* string)(递归实现)
	实现：将参数字符串中的字符反向排列，不是逆序打印。
	要求：不能使用C函数库中的字符串操作函数。

	char arr[] = "abcdef";
	逆序之后就变为：fedcba
*/
```

## 第十一题

```c++
// 问题：下面两个数组是否相等，如果相等，为什么；如果不相等，为什么
char arr1[] = "hello\o";
char arr2[] = {'h', 'e', 'l', 'l', 'o'};
```

## 第十二题

```txt
关于表达式求值说法不正确的是：（ ）
A .表达式求值先看是否存在整形提升或算术转换，再进行计算

B .表达式真正计算的时候先看相邻操作符的优先级决定先算谁

C .相邻操作符的优先级相同的情况下，看操作符的结合性决定计算顺序

D .只要有了优先级和结合性，表达式就能求出唯一值
```

> [!warning] 如果下面的题不会，或者有知识点没有讲过，那么跳过，等待我讲或者百度查询

## 第十三题

```c++
/*
	打印整数二进制的奇数位和偶数位
	题目内容：
		获取一个整数二进制序列中所有的偶数位和奇数位，分别打印出二进制序列
	提示：
		int是32个比特位，如何得到二进制的数据？程序底层看到的int，其实已经是二进制了，使用 >> 或者 << 操作符，可以移动位，使用 & ^ !可以按位对二进制数据进行操作
		现在就是如何通过位操作符获得最后一位的数据，然后来输出
*/
```

## 第十四题

```c++
/*
	统计二进制中1的个数
	题目内容：
		写一个函数返回参数二进制中 1 的个数。
		比如： 15    0000 1111    4 个 1
*/
```

## 第十五题

```txt
以下系统中，int类型占几个字节，指针占几个字节，操作系统可以使用的最大内存空间是多大：( )
A .32位下：4,4,2^32 64位下：8,8,2^64

B .32位下：4,4,不限制 64位下：4,8,不限制

C .32位下：4,4,2^32 64位下：4,8,2^64

D .32位下：4,4,2^32 64位下：4,4,2^64
```

## 第十六题

```c++
// 下面代码的结果是：（ ）
#include <stdio.h>
int main()
{
  int arr[] = {1,2,3,4,5};
  short *p = (short*)arr;
  int i = 0;
  for(i=0; i<4; i++)
  {
    *(p+i) = 0;
  }
   
  for(i=0; i<5; i++)
  {
    printf("%d ", arr[i]);
  }
  return 0;
}
```

## 第十七题

```c++
// 下列程序段的输出结果为（ ）
unsigned long pulArray[] = {6,7,8,9,10};
unsigned long *pulPtr;
pulPtr = pulArray;
*(pulPtr + 3) += 3;
printf(“%d,%d\n”,*pulPtr, *(pulPtr + 3));
```

> [!warning] 指针讲解 -- 对于指针深层的理解

## 第十八题

```c++
如有以下代码：
struct student
{
  int num;
  char name[32];
  float score;
}stu;

则下面的叙述不正确的是：( )
A .struct 是结构体类型的关键字

B .struct student 是用户定义的结构体类型

C .num, score 都是结构体成员名

D .stu 是用户定义的结构体类型名
```

## 第十九题

```txt
结构体访问成员的操作符有：

```

## 第二十题

```c++
// 下面程序的输出结果是：（ ）
struct stu
{
    int num;
    char name[10];
    int age;
};

void fun(struct stu *p)
{
	printf(“%s\n”,(*p).name);
	return;
}

int main()
{
	struct stu students[3] = {
		{9801,”zhang”,20},
		{9802,”wang”,19},
        {9803,”zhao”,18}
     };
    fun(students + 1);
	return 0;
}
```

## 第二十一题

```txt
C程序常见的错误分类不包含：（ ）
A .编译错误

B .链接错误

C .栈溢出

D .运行时错误
```

## 第二十二题

```txt
语言中哪一种形式声明了一个指向char类型变量的指针p，p的值不可修改，但p指向的变量值可修改？( )
A .const char *p

B .char const *p

C .char*const p

D .const char *const p
```

## 第二十二题

```txt
以下关于指针的说法,正确的是( )
A .int *const p与int const *p等价

B .const int *p与int *const p等价

C .const int *p与int const *p等价

D .int *p[10]与int (*p)[10]等价
```

> [!warning] 调试讲解 -- 斐波那契数列

```c++
int fibonacci(int n, int) {
	if (n <= 2) {
		return 1;
	}
	int temp = 0, num1 = 0, num2 = 0;
	for (int i = 0; i >= n - 2; i--) {
		temp = num1 + num2;
		num1 = num2;
		num2 = temp;
	}
	return temp;
}
```

## 第二十三题

```c++
/*
	题目内容，调试下列程序，使之能正常运行
*/
void move_array(int arr[], int len, int key) {
	for (int i = len; i >= 0; i--) {
		arr[i] = arr[i - 1];
	}
	arr[0] = key;
}

int main() {
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 }; // 0用于占位，没有实际意义
	int key = 10;
	move_array(arr, 10, key);
}
```

## 第二十四题

```c++
/*
	题目内容：
		VS开发环境调试下面的代码，画图解释下面代码的问题
*/

#include <stdio.h>
int main()
{
    int i = 0;
    int arr[] = {1,2,3,4,5,6,7,8,9,10};
    for(i=0; i<=12; i++)
    {
        arr[i] = 0;
        printf("hello bit\n");
    }
    return 0;
}
```

