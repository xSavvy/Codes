/*
 * @Author: Liu Weilong
 * @Date: 2021-01-20 22:07:19
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-01-21 08:14:34
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
    virtual bool Traverse(std::function<void()> f)  override;
    T * pool_;
};


template<typename T>
SequenceList<T>::SequencesList(size_t capacity):LinearList<T>(capacity){}

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
    std::find()
}
