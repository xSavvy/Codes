<!--
 * @Author: Liu Weilong
 * @Date: 2021-03-15 13:55:40
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-03-15 14:07:46
 * @FilePath: /3rd-test-learning/25. cpptest/circular_include/doc.md
 * @Description: 
-->
### 关于循环include存在问题
1. 在 A B 循环include的时候,

    如果结束这种循环声明，需要了解编译顺序，然后使用前置声明。
2. 在 A B 循环include的时候出现了uncomplete type 的情况怎么办？

    出现这种情况的原因后面进行解释。解决的方法就是在.cpp 文件对B.hpp进行include
3. 解决方法见code 即可

### 原因解释
1. 在编译的过程中，只是编译了.cpp文件，.h 是单纯的复制过去。
2. 对于不同.cpp 单独编译成.o 文件，所以需要编译的.cpp是完整的。
3. .cpp 是完整的是什么意思呢？就是里面使用的类都是有完成定义的。而不是只有声明，之前存在的uncomplete type 就是因为A.cpp 中没有包含B的定义
