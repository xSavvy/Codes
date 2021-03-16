/*
 * @Author: Liu Weilong
 * @Date: 2021-03-10 06:29:27
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-03-15 22:48:55
 * @Description: 
 */
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "opencv2/core/core.hpp"
#include "sophus/se3.hpp"

using namespace std;

class DataLoader
{
    public:
    DataLoader(const string & config_path);

    bool GetInfo(double & time, string & img);


    void LoadImg(int range);
    void LoadPose(const string & path);
    // LoadTime 和 SaveTime结合 可以用于生成times.txt
    void LoadTime(const string & path);
    // save time.txt
    void SaveTime(const string & path);

    void TransformPose(const vector<vector<double>> & origin, std::vector<Sophus::SE3d> & result );

    static Sophus::SO3d EulerToRotationMatrix(double x,double y, double z);

    std::vector<std::string> img_array_;
    std::vector<Sophus::SE3d> pose_array_;
    std::vector<double> time_array_;
    int count =0;
    int final;

};


bool DataLoader::GetInfo(double & time, string & img)
{
    if(count<final)
    {
        time = time_array_[count];
        img = img_array_[count];
        count++;
        return true;
    }
    return false;
}

DataLoader::DataLoader(const string & config_path)
{
    string pose_path,time_path;
    cv::FileStorage fin(config_path.c_str(),CV_STORAGE_READ);
    fin["DataLoader.PosePath"]>>pose_path;
    fin["DataLoader.TimePath"]>>time_path;
    final = (int)fin["DataLoader.FinalIdx"];
    cout<<"DataLoader.PosePath : "<<pose_path<<endl;
    cout<<"DataLoader.TimePath : "<<time_path<<endl;
    cout<<"DataLoader.FinalIdx : "<< final <<endl;
    // LoadPose(pose_path);
    LoadImg(1170);
    LoadTime(time_path);

    final = (final>time_array_.size()?time_array_.size():final);
    cout<<"Updated .FinalIdx : "<< final <<endl;
}

void DataLoader::LoadPose(const string & path){

    std::ifstream fin(path.c_str());
    if(!fin.is_open())
    {
        cerr<<"the path is wrong"<<endl;
        abort();
    }
    string s,info;
    stringstream ss;
    std::vector<double> xy;
    std::vector<vector<double>> origin_pose;
    origin_pose.reserve(1200);
    while(getline(fin,s))
    {
        ss.str(s);
        
        while(getline(ss,info,','))                           // 使用 ‘，’对一行数据进行分割
        {
            xy.push_back(atof(info.c_str())) ;         
        }
        origin_pose.push_back(xy);
        xy.clear();
        ss.clear();
    }

    TransformPose(origin_pose,pose_array_);
}


void DataLoader::TransformPose(const vector<vector<double>> & origin,
                               std::vector<Sophus::SE3d> & result)
{
    result.clear();
    result.reserve(origin.size());
    double x_angle ,y_angle ,z_angle;
    double x_trans, y_trans, z_trans;
    for(auto & pose:origin)
    {
        x_angle = pose[0];
        y_angle = pose[1];
        z_angle = pose[2];
        x_trans = pose[3];
        y_trans = pose[4];
        z_trans = pose[5];

        Sophus::SE3d se3;
        se3.so3() = EulerToRotationMatrix(y_angle,x_angle,z_angle);
        se3.translation() = Eigen::Vector3d(x_trans,y_trans,z_trans);

        result.push_back(se3);
    }
}

// 待测试

Sophus::SO3d DataLoader::EulerToRotationMatrix(double x,double y, double z)
{
    Eigen::AngleAxisd axis_x(x,Eigen::Vector3d(1.,0.,0.));
    Eigen::AngleAxisd axis_y(y,Eigen::Vector3d(0.,1.,0.));
    Eigen::AngleAxisd axis_z(z,Eigen::Vector3d(0.,0.,1.));

    Eigen::Quaterniond temp = (axis_z*axis_y*axis_x);
    return Sophus::SO3d(temp);
}

void DataLoader::LoadImg(int range)
{
    img_array_.clear();
    std::string end = ".png";
    std::string start = "0000000000";
    std::string temp;
    std::string a;
    for(int i=0;i<range;i++)
    {
        temp = start;
        a = to_string(i);
        temp = temp.substr(0,start.length()-a.length()) + a + end;
        img_array_.push_back(temp);
    }    
}

void DataLoader::LoadTime(const std::string & time_path)
{
    std::ifstream fin(time_path.c_str());
    if(!fin.is_open())
    {
        cerr<<"the path is wrong"<<endl;
        abort();
    }
    string s,info;
    std::vector<double> xy;
    while(getline(fin,s))
    {
        int h = atoi(s.substr(11,13).c_str());
        int m = atoi(s.substr(14,16).c_str());
        double sec = atof(s.substr(17).c_str());

        // cout<<"h :"<<h<<" m :"<<m<<" sec: "<<sec<<endl;
        double nsec = h*3600.0 + m*60.0+sec;

        // cout<<"nsec: "<<nsec<<endl;

        time_array_.push_back(nsec);
    }
}

void DataLoader::SaveTime(const std::string & path)
{
    if(time_array_.size()==0)
    {
        std::cerr<<" time array is empty!"<<endl;
        abort();
    }

    ofstream fout(path.c_str());
    if(!fout.is_open())
    {
        std::cerr<<"[SaveTime] can not open the file"<<endl;
        abort();
    }

    for(double t:time_array_){
        fout<<setprecision(16)<<t<<endl;
    }
    
}
