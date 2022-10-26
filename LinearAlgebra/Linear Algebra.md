# 线性代数

## 行列式

### 二阶三阶行列式

- 解二元线性方程组

$$
	\left\{
		\begin{matrix}
		a_{11}x_1 + a_{12}x_2 = b_1 &···& A \\\
		a_{21}x_1 + a_{22}x_2 = b_2 &···& B
		\end{matrix}
	\right.
$$

- 可以得知:

$$
	x_1 = \frac{b_1a_{22} - b_2a_{12}}{a_{11}a_{22} - a_{12}a_{21}} \
	x_2 = \frac{b_2a_{11} - b_1a_{21}}{a_{11}a_{22} - a_{12}a_{21}}
$$

#### 定义

> 定义：**表达式$a_{11}a_{22} - a_{12}a_{21} = \begin{vmatrix}a_{11} & a_{12} \\ a_{21} & a_{22}\end{vmatrix}$为数表所确定的二阶行列式
>> 注：$a_{ij}，i = 1, 2; j = 1, 2$为行列式的元素，i表示行 j表示列


#### 计算方法

$$
	D = 
	\begin{vmatrix}
	a_{11} & a_{12} \\
	a_{21} & a_{22}
	\end{vmatrix} = a_{11}a_{22} - a_{12}a_{21}
$$

- 若对上述有以下定义：
	- $b_1a_{22} - a_{12}b_2 = \begin{vmatrix}b_1 & a_{12} \\ b_2 & a_{22}\end{vmatrix} = D_1$
	- $a_{11}b_2 - b_1a_{21} = \begin{vmatrix}a_{11} & b_1 \\ a_{21} & b_2\end{vmatrix} = D_2$

$$
	x_1 = \frac{D_1}{D}, \ x_2 = \frac{D_2}{D}
$$

#### 二阶行列式的几何意义

- 若将行列式用向量表示：
$$
	\begin{vmatrix}
	a_{11} & a_{12} \\
	a_{21} & a_{22}
	\end{vmatrix} \Rightarrow \vec{a} = (a_{11} \ a_{12}), \vec{b} = (a_{21} \ a_{22})
$$

![[Pasted image 20221025214638.png]]

- 那么此时这个平行四边形的面积表示为：

$$
	S = \vec{a} \times \vec{b} = |\vec{a}|·|\vec{b}|sin\theta
$$
- 设$|\vec{a}| = L, |\vec{b}| = P$：
$$
	\begin{equation}
		\begin{aligned}\therefore 
			S &= L · P · sin(\beta - \alpha) \\ 
			&= L · P · (sin\beta cos\alpha - cos\beta sin\alpha) \\
			&= L · cos\alpha · P · sin\beta - L · sin\alpha · P · cos\beta \\
			&= a_{11}a_{22} - a_{12}a_{21} \\
			&= 
			\begin{vmatrix}
			a_{11} & a_{12} \\
			a_{21} & a_{22}
			\end{vmatrix}
		\end{aligned}
	\end{equation}
$$
> 因此，二阶行列式的几何意义为**以行向量围成的平行四边形面积**

### 全排列和对换

#### 全排列

> 定义：**把n个不同的数排成一列，叫做这n个数的全排列(排列)**
>> 注：一般1, 2, ..., n是n个数排列的标准次序

#### 逆序数

> 定义1：**当n个数的任意排列中两个数的先后顺序与标准次序不同时，就说有一个逆序**
> 定义2：**一个排列中所有的逆序总数叫做这个排列的逆序数**
>> 注：逆序数是奇数的排列叫做奇排列，反之，则是偶排列

- **定义：$a_1, a_2, a_3的逆序数记为\tau{(a_1, a_2, a_3)}$**

