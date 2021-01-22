/*
 * @Author: Liu Weilong
 * @Date: 2021-01-20 22:07:19
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-01-21 22:32:19
 * @Description: 
 */
#include "linear_list.h"

class Item
{
    public:
    bool operator==(const Item & item)
    {
        if(a==item.a&&b ==item.b)
        return true;
        return false;
    }
    int a,b;
};

template <typename T>
class SequenceList:public LinearList<T>
{
    public:

    SequenceList(size_t capacity);
    virtual bool Init()  override ;
    virtual bool Destroy()  override;
    virtual bool ClearList()  override;
    virtual bool GetElem(size_t idx, T &e) const override;
    virtual bool LocateElem(const T & e,size_t & idx)const  override;
    virtual bool PriorElem(const T & cur_e, T & pre_e)const  override;
    virtual bool NextElem(const T & cur_e, T & next_e) const override;
    virtual bool InsertElem(size_t idx, const T & e)  override;
    virtual bool DeleteElem(size_t idx, T & e)  override;
    virtual bool Traverse(std::function<void(T&)> f)  override;
    T * pool_;
};


template<typename T>
SequenceList<T>::SequencesList(size_t capacity):LinearList<T>(capacity){Init();}

template<typename T>
bool SequenceList<T>::Init()
{
    pool_ = new T[capacity_]();
    length_ = 0;
    cout<<"the SequenceList init "<<endl;
}

template<typename T>
bool SequenceList<T>::Destroy()
{
    delete [] pool_;
}

template<typename T>
bool SequenceList<T>::GetElem(size_t idx, T &e) const
{
    if(!CheckIdx(idx))
    return false;
    e = T[idx];
    return true;
}

template<typename T>
bool SequenceList<T>::LocateElem(const T & e,size_t & idx)const
{
    if(!CheckIdx(idx))
    return false;
    
    for(size_t i=0;i<length_;i++)
    {
        if(pool_[i]==e)
        {
            idx = i;
            return true;
        }
    }
    return false;
}

template<typename T>
bool SequenceList<T>::PriorElem(const T & cur_e, T & pre_e)const
{
    size_t idx =0;
    bool ok = LocateElem(cur_e,idx);
    if(idx==0||!ok)
    return false;
    GetElem(idx-1,pre_e);
    return true;
}

template<typename T>
bool SequenceList<T>::NextElem(const T & cur_e, T & next_e) const
{
    size_t idx =0;
    bool ok = LocateElem(cur_e,idx);
    if(idx==(length_-1)||!ok)
    return false;
    GetElem(idx+1,next_e);
    return true;
}

template<typename T>
bool SequenceList<T>::InsertElem(size_t idx, const T & e) 
{
    if(!CheckIdx(idx)&& length_!=0)
    return false;
    if(length_==capacity_)
    return false;
    length_++;
    for(size_t i = length_-1;i!=idx,i--)
    {
        pool_[i] = pool_[i-1];
    }
    pool_[idx] = e;
    return true;
}

template<typename T>
bool SequenceList<T>::DeleteElem(size_t idx, T & e)
{
    if(!CheckIdx(idx))
    return false;

    e=pool_[idx];
    
    for(size_t i = idx;i<(length_-1);i++)
    {
        pool_[i] = pool_[i+1];
    }
    length_--;
    return true;    
}

template<typename T>
bool SequenceList<T>::Traverse(std::function<void(T&)> f)
{
    for(size_t i=0;i<length_;i++)
    {
        f(pool_[i]);
    }
}