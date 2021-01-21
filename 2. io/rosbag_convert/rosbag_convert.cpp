/*
 * @Author: Liu Weilong 
 * @Date: 2020-09-01 11:11:17 
 * @Last Modified by: Liu Weilong
 * @Last Modified time: 2020-09-01 13:22:05
 */

#include "rosbag_convert.h"


int main()
{
    LwlSLAM::LoadImgAndSaveInFile("/home/sunny/workspace_public/Dataset/2021-01-14-15-13-25.bag",
                                  "/home/sunny/workspace_public/Dataset/self_test");
    return 0;
}