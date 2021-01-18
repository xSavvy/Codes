/*
 * @Author: Liu Weilong
 * @Date: 2021-01-15 07:00:51
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-01-16 11:25:12
 * @Description:
 *              测试内容
 *              1. 测试颜色的转换 ColorConvert
 *              2. 显示测试      EnvironmentShow
 */
#include "environment_builder.h"
#include "pointcloud_shower.h"

using namespace slam_demo;
using namespace std;

void ColorConvert()
{
    PangolinPointCloudShower shower_;
    Eigen::Vector3i color(128,128,128);
    Eigen::Vector3i color_converted;
    uint32_t ui32;
    shower_.ColorConvert(color,ui32);
    shower_.ColorConvert(ui32,color_converted);
    cout<<"the origin color is "<< color.transpose()<<endl;
    cout<<"the converted color is "<<color_converted.transpose()<<endl;
}
void EnvironmentShow()
{
    const string config_path= "../config/config.yaml";
    EnvironmentBuilder eb(config_path);
    Eigen::Vector3i color(255,0,0);
    PangolinPointCloudShower pps;
    pps.LoadPointCloud(color,eb.GetLandmarksVec3d());
    pps.Show();
}

int main()
{

}
