<!--
 * @Author: Liu Weilong
 * @Date: 2021-02-23 07:25:43
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-02-23 07:40:30
 * @Description: 
-->
###  week2 
1. C++ 模板编译的二段式查找机制，导致出现编译不通过的情况。<br>
   a.1. 模板定义阶段，只有模板中非独立的对象可以通过查找。<br>
        这个阶段如果找不到，会直接报错会说没有进行声明，而不会等到第二阶段，再来查找一次。<br>
   a.2. 模板示例化阶段，和模板有关的对象开始进行查找<br>
2. 子类中，调用基类。<br>
   LinearList\<T1>::ClearList()