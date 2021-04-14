/*
 * @Author: Liu Weilong 
 * @Date: 2020-09-01 11:11:17 
 * @Last Modified by: Liu Weilong
 * @Last Modified time: 2020-09-01 13:22:05
 */

#include "rosbag_convert.h"


int main()
{
    LoadImgAndSaveInFile("/home/sunny/workspace_public/Dataset/VP/2021-04-14-14-13-57.bag",
                                  "/home/sunny/workspace_public/Dataset/self_test6");
    LoadImgAndSaveInFile("/home/sunny/workspace_public/Dataset/VP/2021-04-14-14-18-27.bag",
                                  "/home/sunny/workspace_public/Dataset/self_test7");
    return 0;

}