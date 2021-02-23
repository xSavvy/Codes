/*
 * @Author: Liu Weilong
 * @Date: 2021-01-20 21:42:24
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-02-22 19:51:37
 * @Description: 
 */
#include <iostream>
#include <functional>
using namespace std;

template<typename T>
class LinearList
{
    public:
    LinearList(size_t capacity):capacity_(capacity){}
    virtual bool Init() =0 ;
    virtual bool Destroy() =0;
    virtual bool ClearList() {length_=0;}
    virtual bool Empty()const {if(length_==0)return true;return false;}
    virtual size_t Length() const {return length_;}
    virtual bool GetElem(size_t idx, T &e) const=0;
    virtual bool LocateElem(const T & e,size_t & idx)const =0;
    virtual bool PriorElem(const T & cur_e, T & pre_e)const =0;
    virtual bool NextElem(const T & cur_e, T & next_e) const=0;
    virtual bool InsertElem(size_t idx, const T & e) =0;
    virtual bool DeleteElem(size_t idx, T & e) =0;
    virtual bool Traverse(std::function<void(T&)> f) =0;
    bool CheckIdx(size_t idx) const {if(idx<=length_-1)return true; return false;}
    virtual ~LinearList(){}
    size_t capacity_;
    size_t length_;
};