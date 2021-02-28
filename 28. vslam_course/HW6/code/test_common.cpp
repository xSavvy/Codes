/*
 * @Author: Liu Weilong
 * @Date: 2021-02-27 22:49:48
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-02-27 23:54:55
 * @Description: 
 */

#include "common.h"

int main()
{
    std::vector<Eigen::Vector2d,Eigen::aligned_allocator<Eigen::Vector2d>> temp;
    std::vector<cv::Point2f> t;
    for(int i=0;i<10;i++)
        temp.push_back(Eigen::Vector2d(i,i));
    eigen2cv(temp,t);
    cout<<"in the opencv array"<<endl;
    for(auto & p:t)
        cout<<"x: "<<p.x<<",y: "<<p.y<<endl;
    cout<<"in the eigen array"<<endl;
    cv2eigen(t,temp);
    for(auto & p:temp)
        cout<<"x: "<<p.x()<<",y: "<<p.y()<<endl;
}