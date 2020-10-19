/*
 * @Author: Liu Weilong
 * @Date: 2020-09-07 14:09:08
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2020-09-07 14:18:38
 * @Description: yaml-cpp 测试程序
 */

#include <iostream>
#include "yaml-cpp/yaml.h"

using namespace std;



int main(){
    YAML::Node node_ = YAML::LoadFile("./");

    cout<<node_["Person"]["name"].as<string>().c_str()<<endl;
    
}