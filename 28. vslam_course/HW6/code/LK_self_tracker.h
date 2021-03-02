/*
 * @Author: Liu Weilong
 * @Date: 2021-02-28 17:59:18
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-03-02 14:48:10
 * @Description: 
 * 
 * 进一步加速: 
 * 1. double 换成 float 应该基本能跑到opencv 的速度 为了精度这个不进行改进
 * 2. openmp 加速效果不明显  不知道为什么,可以看一下为什么没有加速
 * 3. 换成 inverse 方法     在噪声的情况下，会出现不够稳定的情况，可以实现一下
 * 4. 换成 opencv 的 parallel_for 进行并行加速  可以实现一下
 * 
 * 
 * 
 */


#include "tracker_base.h"
#include "common.h"
#include "omp.h"

class LKtracker:public TrackerBase
{
   public:
   LKtracker(std::string & config):TrackerBase(config){}
   virtual void Impl() override;
   
   private:
   void LKSingleLayer(const cv::Mat & pre_img,const cv::Mat & cur_img,
                      const Corners & pre_corners, Corners & cur_corners,
                      std::vector<bool> & success,
                      bool inverse = false, bool has_initial = false);
   bool SinglePixelOperation(const cv::Mat & pre_img,const cv::Mat & cur_img, 
                             const Eigen::Vector2d origin, Eigen::Vector2d & cur_origin);
   std::vector<bool> success_;
};


void LKtracker::Impl()
{
    Corners t_pre_corners,t_cur_corners;
    t_cur_corners.reserve(pre_corners_.size());
    t_pre_corners.reserve(pre_corners_.size());
    vector<float> scale_array;
    scale_array.reserve(options_ptr_->level_);
    scale_array.push_back(1.0);

    for(int i=1;i<options_ptr_->level_;i++)
        scale_array.push_back(scale_array[i-1]*options_ptr_->scale_);

    for(auto & kp:pre_corners_)
    {
        Eigen::Vector2d  p= kp*scale_array.back();
        t_pre_corners.push_back(p);
        t_cur_corners.push_back(p);
    }
    
    double larger = 1.0/options_ptr_->scale_;
    
    for(int i = scale_array.size()-1;i>=0;i--)
    {
        LKSingleLayer(pyr_pre_img_[i],pyr_cur_img_[i],t_pre_corners,t_cur_corners,success_);
        if(i!=0)
        {
            for(auto &p:t_pre_corners) p *= larger;
            for(auto &p:t_cur_corners) p *= larger;
        }
    }

    for(auto & p :t_cur_corners)
    cur_corners_.push_back(p);
}

void LKtracker::LKSingleLayer(const cv::Mat & pre_img,const cv::Mat & cur_img,
                              const Corners & pre_corners, Corners & cur_corners,
                              std::vector<bool> & success,
                              bool inverse, bool has_initial)
{
    success.resize(pre_corners.size(),false); 
    for (int i = 0; i < pre_corners.size(); i++)
    {
        success[i] = SinglePixelOperation(pre_img,cur_img,pre_corners[i],cur_corners[i]);
    }
}

// origin 是初始在cur_img 上的位置
bool LKtracker::SinglePixelOperation(const cv::Mat & pre_img,const cv::Mat & cur_img, 
                                     const Eigen::Vector2d origin, Eigen::Vector2d & cur_origin)
{
    int half_path_size = options_ptr_->template_/2;
    int iterations = 10;

    Eigen::Matrix2d H;
    Eigen::Vector2d b;
    Eigen::Vector2d J;
    Eigen::Vector2d temp_pos = cur_origin;

    double temp_x = temp_pos.x();
    double temp_y = temp_pos.y();
    double origin_x = origin.x();
    double origin_y = origin.y();
    double dx=0.,dy =0.,cost = 0.,lastCost =0.;
    // pixel postion check
    
    // 
    for(int i =0;i<iterations ; i++)
    {
        H.setZero();
        b.setZero();
        cost = 0;
        // 出 Jacobian 和 cost
        for(int x = -half_path_size;x<half_path_size;x++)
            for(int y = -half_path_size;y<half_path_size;y++)
            {
                double error = GetPixelValue(pre_img,origin_x+x,origin_y+y) - 
                              GetPixelValue(cur_img,temp_x+dx+x,temp_y+dy+y);
                J = -1.0 * Eigen::Vector2d(
                    0.5 * (GetPixelValue(cur_img, temp_x+dx+x +1, temp_y+dy+y) -
                            GetPixelValue(cur_img, temp_x+dx+x -1, temp_y+dy+y)),
                    0.5 * (GetPixelValue(cur_img, temp_x+dx+x, temp_y+dy+y + 1) -
                            GetPixelValue(cur_img, temp_x+dx+x, temp_y+dy+y - 1))
                );
                b += -error * J;
                cost += error * error;
                H += J * J.transpose();
            }
            Eigen::Vector2d update = H.ldlt().solve(b);

            if (std::isnan(update[0])) {
                // sometimes occurred when we have a black or white patch and H is irreversible
                cout << "update is nan" << endl;
                return false;
            }

            dx += update[0];
            dy += update[1];
            if (i > 0 && cost > lastCost) {
                break;
            }
            lastCost = cost;

            if (update.norm() < 1e-2) {
                break;
            }
    }
    cur_origin.x() += dx;
    cur_origin.y() += dy;
    
    return true;
}