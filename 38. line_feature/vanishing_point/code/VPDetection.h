/*
 * @Author: Liu Weilong
 * @Date: 2021-03-28 10:46:22
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-03-31 15:00:34
 * @Description: 
 * 
 * 
 * 1. 这个的主要目的是VP 的初始化
 * 
 * 2. 我大概知道那个人的算法是怎么实现的了
 * 
 * 3. 目前，存在一个从匹配有错误的问题，导致得分不高
 *    原因是VanishingPoint没有进行精细化处理。
 *    改进有二: 1. 3N*L VP精细化   没有继续做了
 *            2. 竖线ransac        10m 正确率大幅上升但是速度还是不够快 加上 opencv_parallel 应该可以跑到 3ms
 * 
 * 
 * 
 * 
 */






#ifndef _VP_DETECTION_H_
#define _VP_DETECTION_H_
#pragma once

#include <stdio.h>
#include <opencv2/opencv.hpp> 
#include "Eigen/Eigen"
#include "omp.h"
#include <iostream>
using namespace std;

struct LineInfo
{
	cv::Mat_<double> para;
	double length;
	double orientation;
	double angle;
};

class VPDetection
{
public:
	VPDetection(void);
	~VPDetection(void);

	void run( std::vector<std::vector<double> > &lines, cv::Point2d pp, double f, std::vector<cv::Point3d> &vps, std::vector<std::vector<int> > &clusters );

	void runRANSAC1Line(cv::Point3d VP1, std::vector<std::vector<double> > &lines,cv::Point2d pp, double f,
						std::vector<cv::Point3d> &vps,
						std::vector<std::vector<int> > &clusters);

	void getVPHypVia1Lines(cv::Point3d VP1, std::vector<std::vector<cv::Point3d> >  &vpHypo);

	void getVPHypVia2LinesWithVerticalInfo( std::vector<std::vector<cv::Point3d> >  &vpHypo);
	
	void getVPHypVia2Lines( std::vector<std::vector<cv::Point3d> >  &vpHypo );

	void getSphereGrids( std::vector<std::vector<double> > &sphereGrid );

	void getBestVpsHyp( std::vector<std::vector<double> > &sphereGrid, std::vector<std::vector<cv::Point3d> >  &vpHypo, std::vector<cv::Point3d> &vps  );

	void lines2Vps( double thAngle, std::vector<cv::Point3d> &vps, std::vector<std::vector<int> > &clusters );
	
	void refineVP(const vector<vector<int>> & cluster,vector<Eigen::Vector3d> & vps);


	std::vector<std::vector<double> > lines;
	std::vector<LineInfo> lineInfos;
	std::vector<LineInfo> VerticalLineInfos;
	cv::Point2d pp;
	double f;
	double noiseRatio;
};






#endif // _VP_DETECTION_H_
