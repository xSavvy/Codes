/*
 * @Author: Liu Weilong
 * @Date: 2020-09-27 18:46:14
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2020-09-27 18:56:30
 * @FilePath: /3rd-test-learning/13. boost-serialization/boost-serialization-simple-case-no-invasive.cpp
 * @Description: 想对于 simple-case-test 这里的是一个非入侵式的编写方法
 */
#include <fstream>
#include <iostream>

#include "boost/archive/text_iarchive.hpp"
#include "boost/archive/text_oarchive.hpp"

using namespace std;

class gps_position
{
public:
    int degrees;
    int minutes;
    float seconds;
    gps_position(){};
    gps_position(int d, int m, float s) :
        degrees(d), minutes(m), seconds(s)
    {}
};


namespace boost {
namespace serialization {

template<class Archive>
void serialize(Archive & ar, gps_position & g, const unsigned int version)
{
    ar & g.degrees;
    ar & g.minutes;
    ar & g.seconds;
}

} // namespace serialization
} // namespace boost

int main()
{
    std::string filename = "/home/sunny/workspace_private/3rd-test-learning/13. boost-serialization/build/file";

    std::ofstream ofs(filename.c_str());
    const gps_position g(35,59,24.567f);

    {
        boost::archive::text_oarchive oa(ofs);
        oa<<g;
    }

    // 第三步 进行提取
    gps_position new_g;
    {
        std::ifstream ifs(filename.c_str());
        boost::archive::text_iarchive ia(ifs);
        ia>>new_g;
    }

    cout << new_g.degrees<<endl;
    cout << new_g.minutes<<endl;
    cout << new_g.seconds<<endl;
    return 0;
}