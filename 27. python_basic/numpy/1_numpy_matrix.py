'''
Author: Liu Weilong
Date: 2021-05-30 19:31:55
LastEditors: Liu Weilong
LastEditTime: 2021-05-30 19:48:29
Description: 
创建数组
np.zero()生成数组的shape是[7,]



'''
import numpy as np 

tmp = np.array([[1,2,3,4,5,6,7]])
print(tmp.shape)

zero = np.zeros(5);
print(zero)

tmp = tmp+1
print(tmp)

one = np.ones((1,7))
print(one)

print(tmp*2)

print(tmp*(one*2))

# 矩阵运算
a = np.vstack((tmp,one))
print(a)

a = a+1
print(a)

# 提取矩阵块