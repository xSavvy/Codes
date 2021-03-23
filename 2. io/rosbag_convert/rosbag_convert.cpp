/*
 * @Author: Liu Weilong 
 * @Date: 2020-09-01 11:11:17 
 * @Last Modified by: Liu Weilong
 * @Last Modified time: 2020-09-01 13:22:05
 */

#include "rosbag_convert.h"


int main()
{
    LoadImgAndSaveInFile("/home/sunny/workspace_public/Dataset/2021-03-23-19-46-13.bag",
                                  "/home/sunny/workspace_public/Dataset/self_test2");
    LoadImgAndSaveInFile("/home/sunny/workspace_public/Dataset/2021-03-23-19-48-01.bag",
                                    "/home/sunny/workspace_public/Dataset/self_test3");
    LoadImgAndSaveInFile("/home/sunny/workspace_public/Dataset/2021-03-23-19-50-13.bag",
                                    "/home/sunny/workspace_public/Dataset/self_test4");
    return 0;
}