/*
 * @Author: Liu Weilong
 * @Date: 2020-10-25 17:15:21
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2020-10-26 15:08:47
 * @Description:  学习如何使用filesystem 进行文件夹的操作
 * 
 *                get_filenames 主要用于统计路径下的文件数 和文件名
 */

#include <boost/filesystem.hpp> 
#include <iostream> 
#include <string>
#include <fstream> 
#include <vector>
#include <boost/program_options.hpp>
 
namespace fs = boost::filesystem;  
namespace po = boost::program_options;
     
int get_filenames(const std::string& dir, std::vector<std::string>& filenames)   //获取文件名和个数
{  
    fs::path path(dir);  
    if (!fs::exists(path))  //判断文件路径是否为空
    {  
        return -1;  
    }  
    
    fs::directory_iterator end_iter;  
    for (fs::directory_iterator iter(path); iter!=end_iter; ++iter)  
    {
        if (fs::is_regular_file(iter->status()))  
        {  
            filenames.push_back(iter->path().string()); 
        }  
      
        if (fs::is_directory(iter->status()))  
        {  
            get_filenames(iter->path().string(), filenames);//是目录则递归  
        }  
    }  
     
    return filenames.size();  //返回文件大小
}  
 
int main(int argc,char *argv[])
{
    po::options_description desc("Allowed options");  
    desc.add_options()  
        ("help,h", "produce help message")  
	    ("directory,d",po::value<std::string>(), "output files' name and amount");  
  
    po::variables_map vm;  
    po::store(po::parse_command_line(argc, argv, desc), vm);  
    po::notify(vm);  
 
    if(vm.count("help"))  
    {  
        std::cout<<desc<<std::endl;  
        return 1;  
    }  
  
    if(vm.count("directory"))
	{   
        std::vector<std::string> filenames;
		int amount = get_filenames(vm["directory"].as<std::string>(),filenames);
		std::ofstream out("filenames.txt");
		if (out.fail())
		{
			std::cout << "Error 2: failed to open the destination file." << std::endl;
			out.close();
			return 0;
		}		
        if (out.is_open())   
        {  
           out <<"amount:"<<amount<<"  \n";  
           for(std::vector<std::string>::iterator iter = filenames.begin(); iter != filenames.end(); iter++ )    
           {
		        out<<*iter<<" \n";
		   }
           out.close();  
        }  
	}
    else  
    {  
        std::cout<<"error1"<<std::endl;  
    }  
	return 0;
}
