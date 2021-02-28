/*
 * @Author: Liu Weilong
 * @Date: 2021-02-28 17:59:18
 * @LastEditors: Liu Weilong
 * @LastEditTime: 2021-02-28 21:51:15
 * @Description: 
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
   void LKSingleLayer(cv::Mat pre_img,cv::Mat cur_img,
                      const Corners & pre_corners, Corners & cur_corners,
                      std::vector<bool> & success,
                      bool inverse = false, bool has_initial = false);
   bool SinglePixelOperation(cv::Mat pre_img,cv::Mat cur_img, 
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
        scale_array.push_back(scale_array[i]*options_ptr_->scale_);

    for(int i =0;i<pre_corners_.size();i++)
    {
        Eigen::Vector2d p = pre_corners_[i]*scale_array.back();
        t_pre_corners.push_back(p);
        t_cur_corners.push_back(p);
    }
    double larger = 1.0/options_ptr_->scale_;
    for(int i = scale_array.size()-1;i<0;i--)
    {
        LKSingleLayer(pyr_pre_img_[i],pyr_pre_img_[i],t_pre_corners,t_cur_corners,success_);
        if(i!=0)
        {
            for(auto &p:t_pre_corners) p *= larger;
            for(auto &p:t_cur_corners) p *= larger;
        }
    }

    for(auto & p :t_cur_corners)
    cur_corners_.push_back(p);
}

void LKtracker::LKSingleLayer(cv::Mat pre_img,cv::Mat cur_img,
                              const Corners & pre_corners, Corners & cur_corners,
                              std::vector<bool> & success,
                              bool inverse, bool has_initial)
{
    omp_set_num_threads(4);
    success.resize(pre_corners_.size(),false);
    #pragma omp parallel for 
    for (int i = 0; i < pre_corners_.size(); i++)
    {
        success[i] = SinglePixelOperation(pre_img,cur_img,pre_corners_[i],cur_corners_[i]);
    }
}

// origin 是初始在cur_img 上的位置
bool LKtracker::SinglePixelOperation(cv::Mat pre_img,cv::Mat cur_img, 
                                     const Eigen::Vector2d origin, Eigen::Vector2d & cur_origin)
{
    int half_path_size = options_ptr_->template_/2;
    int iterations = 10;

    Eigen::Matrix2d H;
    Eigen::Vector2d b;
    Eigen::Vector2d J;
    Eigen::Vector2d temp_pos = cur_origin;
    H.setZero();b.setZero();J.setZero();

    double temp_x = temp_pos.x();
    double temp_y = temp_pos.y();
    double origin_x = origin.x();
    double origin_y = origin.y();
    double dx=0.,dy =0.,cost = 0.,lastCost =0.;
    // pixel postion check
    
    // 这里先使用自己的理解
    for(int i =0;i<iterations ; i++)
    {
        // 出 Jacobian 和 cost
        for(int x = -half_path_size;x<= half_path_size;x++)
            for(int y = -half_path_size;y<half_path_size;y++)
            {
                double error = GetPixelValue(pre_img,origin_x+x,origin_y+y) - 
                              GetPixelValue(cur_img,temp_x+dx+x,temp_y+dy+x);
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
            lastCost = cost;

            if (update.norm() < 1e-2) {
                // converge
                return true;
            }
    }
    cur_origin.x() += dx;
    cur_origin.y() += dy;
}