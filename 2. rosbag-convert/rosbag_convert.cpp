/*
 * @Author: Liu Weilong 
 * @Date: 2020-09-01 11:11:17 
 * @Last Modified by: Liu Weilong
 * @Last Modified time: 2020-09-01 13:22:05
 */

#include <iostream>
#include <vector>
#include <string>

#include "rosbag/bag.h"
#include "rosbag/view.h"
#include "sensor_msgs/MultiEchoLaserScan.h"
#include "sensor_msgs/LaserScan.h"
#include "sensor_msgs/Imu.h"

namespace LwlSLAM
{
    void structure_convert()
    {
        rosbag::Bag bag_input,bag_output;
        bag_input.open("/home/lwl/workspace/PublicData/lidar2d/b0-2014-07-11-11-00-49.bag",
        rosbag::bagmode::Read);
        bag_output.open("/home/lwl/workspace/PublicData/lidar2d/test.bag",rosbag::bagmode::Write);

        std::vector<std::string> topics{"horizontal_laser_2d","imu"};

        rosbag::View view(bag_input,rosbag::TopicQuery(topics));

        int a =0;

        uint32_t seq = 0;
        // 以下内容主要是为了数值转换
        for(auto element: view){
   
            sensor_msgs::MultiEchoLaserScan::ConstPtr mlaserElement = element.instantiate<sensor_msgs::MultiEchoLaserScan>();
            sensor_msgs::Imu::ConstPtr imuElement = element.instantiate<sensor_msgs::Imu>();
            std::cout<<a<<std::endl;
            a++;

            if(mlaserElement != NULL){  

                // for(const sensor_msgs::LaserEcho & element:mlaserElement->ranges)
                // {
                //     std::cout<<element.echoes.front()<<"  ";
                // }
                // std::cout<<std::endl;

                sensor_msgs::LaserScan laser_t ;
                laser_t.header = mlaserElement->header;
                laser_t.header.seq = seq;
                laser_t.angle_min = mlaserElement->angle_min;
                laser_t.angle_max = mlaserElement->angle_max;
                laser_t.angle_increment = mlaserElement->angle_increment;
                laser_t.range_max = mlaserElement->range_max;
                laser_t.range_min = mlaserElement->range_min;
                laser_t.scan_time = mlaserElement->scan_time;

                seq++;

                laser_t.ranges.resize(mlaserElement->ranges.size());
                auto iter = laser_t.ranges.begin();
                std::cout<<mlaserElement->ranges.size()<<std::endl;
                int count_ =0;
                for(auto echo: mlaserElement->ranges){
                    if(echo.echoes.size()==0)
                    continue;
                    *iter = echo.echoes.front();
                    iter++;
                }
                
                laser_t.intensities.resize(mlaserElement->intensities.size());
                auto iter_ = laser_t.intensities.begin();
                for(auto echo: mlaserElement->intensities){
                    if(echo.echoes.size()==0)
                    continue;
                    *iter_ = echo.echoes.front();
                    iter_++;
                }

                bag_output.write("horizontal_laser_2d",ros::Time(mlaserElement->header.stamp),laser_t);
            }
                
            if(imuElement != NULL){
                bag_output.write("imu",ros::Time(imuElement->header.stamp),*imuElement);
            }
        }
        bag_output.close();
        bag_input.close();
    }

    
}
int main()
{
    LwlSLAM::structure_convert();
    return 0;
}