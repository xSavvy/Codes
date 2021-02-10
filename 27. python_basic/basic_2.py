'''
Author: Liu Weilong
Date: 2021-02-09 20:38:44
LastEditors: Liu Weilong
LastEditTime: 2021-02-09 20:38:44
Description: 
'''

# while 的使用 斐波纳契数列
# end 关键字
a=0;b=1;i=0
while a<10:
    print(a,end=str(i))
    m=b;b=a+b;a=m
    i=i+1

