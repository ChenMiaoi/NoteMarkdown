# Activation functions  

---   

## sigmoid  

$$ \sigma{(z)} = \frac{1}{1 + e^{-z}}, z = w^Tx + b $$  
![[sigmoid.png]] 

- When we are have a data which is banary classification, u can use the sigmoid as a activation functions is suitable  

---  

## tanh -- tangent function

$$ tanh = \frac{e^z - e^{(-z)}}{e^z + e^{(-z)}}, z = w^Tx + b $$  

![[tanh.png]]  


- To compare the tanh and sigmoid, we should use tanh to replace sigmoid expect the binary classification 

---  

## ReLU  -- The rectified linear unit

$$ ReLU = max(0, z) $$  

- If u can't clearly find a activation function to do, u can choose the ReLU which is the most people using  

![[ReLU.png]]

---  

## lackReLU

$$ ReLU = max(0.01 * z, z) $$

![[lackReLU.png]]

--- 

# 为什么需要非线性激活函数

- 如果没有非线性激活函数，那么就变成了线性激活函数，**那么你的模型的输出不过就是你输入的特征的线性组合**

- 只有一个地方可能会用到线性函数，**那就是回归问题**

# 激活函数的导数

## Sigmoid

$$
	\frac{d}{dz}g(z) = \frac{1}{1 + e^{-z}}(1 - \frac{1}{1 + e^{-z}}) = g(z)(1 - g(z)), g(z) = \frac{1}{1 + e^{-z}}
$$

$$
	g'(z) = a(1 - a), a = g(z)
$$

$$
	g'(z) = \left\{\begin{array}{rcl}0 & {z = +\infty}\\\frac{1}{4} & {g(z) = \frac{1}{2}} \\1 & {z = -\infty} \end{array}\right.
$$

## tanh

$$
	\frac{d}{dz}g(z) = 1 - (tanh(z))^2
$$

$$
	g'(z) = \left\{\begin{array}{rcl}0 & {z = \infty, tanh(z) = 1}\\1 & {z = 0, tanh(z) = 0}\\0 & {z = -\infty, tanh(z) = -1} \end{array}\right.
$$

## ReLU

$$
	g'(z) = \left\{\begin{array}{rcl}0 & {z < 0}\\1 & {z > 0}\\ undef & {z = 0} \end{array}\right.
$$

