/*
 * @Author: Liu Weilong
 * @Date: 2021-01-21 21:54:58
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-01-21 22:07:05
 * @Description: 
 *              这个部分主要是为了测试继承和虚指针 调用的关系
 *              主要测试内容：
 *              1. 在构造函数中，基类还是会调用自己下面定义的函数 比如 base print 的Init() 
 *                 func2() 虽然在Derived里面进行了定义，但是在Base 的ctor 中会被认为是无定义
 *              2. 在动态绑定的过程中，func1() 就会调用派生类
 */

#include <iostream>

using namespace std;

class Base
{
    public:

    Base(){Init();
//    func2();
    }
    virtual void Init(){cout<<"base init "<<endl;}

    virtual void func1(){func2();}
    virtual void func2()=0;
    int content = 0;
};

class Derived:public Base
{
    public:
    Derived(){Init();}
    virtual void Init() override{cout<<"derived init"<<endl;};
    virtual void func2() override {cout<<"derived print "<< content<<endl;}
};

int main()
{
    Base * ptr = new Derived();
    ptr->func1();
}

