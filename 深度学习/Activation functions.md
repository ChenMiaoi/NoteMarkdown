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

---  
