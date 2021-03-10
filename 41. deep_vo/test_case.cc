/*
 * @Author: Liu Weilong
 * @Date: 2021-03-10 06:28:40
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-03-10 06:55:44
 * @Description: 
 */
#include "data_loader.h"


int main()
{
    DataLoader dl("");
    string pose_path = "/home/lwl/workspace/DataSet/KITTI/out_01.txt";
    dl.LoadPose(pose_path);


}

