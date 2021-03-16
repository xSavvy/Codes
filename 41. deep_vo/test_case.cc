/*
 * @Author: Liu Weilong
 * @Date: 2021-03-10 06:28:40
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-03-15 22:40:13
 * @Description: 
 */
#include "data_loader.h"


int main()
{
    DataLoader dl("/home/lwl/workspace/3rd-test-learning/41. deep_vo/config.yaml");
    string pose_path = "/home/lwl/workspace/DataSet/KITTI/out_01.txt";
    // dl.LoadPose(pose_path);
    // dl.LoadImg(1200);
    dl.LoadTime("/home/lwl/workspace/3rd-test-learning/41. deep_vo/timestamps.txt");
    dl.SaveTime("/home/lwl/workspace/3rd-test-learning/41. deep_vo/times.txt");
    for(auto & str:dl.img_array_)
    cout<<str<<endl;
}



