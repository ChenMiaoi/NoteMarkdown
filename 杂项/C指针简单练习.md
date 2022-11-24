# 指针内容

> [!todo] 要求：必须使用markdown语法，将题目解答写入markdown文件中

## 题目一

> [!todo] 需求：仿写strlen函数，size_t strlen(const char\* string);

## 题目二

> [!todo] 需求：仿写 strcat函数，char\* strcat(char\* strDestination, const char\* strSource);

## 题目三

> [!todo] 需求：仿写strcpy函数，char\* strcpy(char\* strDestination, const char\* strSource);

## 题目四

> [!todo] 需求：判断以下代码是否正确，如果正确，为什么正确；如果错误，为什么错误

```c++
#include <iostream>

int main() {
	int i[10] = {0};
	i[10] = 5; index < 10
	i[5] = 10;
	int j = 5;
	i[j] = 8;
	j[i] = 8; i[j] == *(i + j) == *(j + i) == j[i]
	return 0;
}
```