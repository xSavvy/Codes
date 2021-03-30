/*
 * @Author: Liu Weilong
 * @Date: 2021-03-28 10:46:22
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-03-30 17:13:20
 * @Description: 
 * 
 * 
 * 1. 这个的主要目的是VP 的初始化
 * 
 * 2. 我大概知道那个人的算法是怎么实现的了
 * 
 */






#ifndef _VP_DETECTION_H_
#define _VP_DETECTION_H_
#pragma once

#include <stdio.h>
#include <opencv2/opencv.hpp> 

#include <iostream>
using namespace std;

struct LineInfo
{
	cv::Mat_<double> para;
	double length;
	double orientation;
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

	void getVPHypVia2Lines( std::vector<std::vector<cv::Point3d> >  &vpHypo );

	void getSphereGrids( std::vector<std::vector<double> > &sphereGrid );

	void getBestVpsHyp( std::vector<std::vector<double> > &sphereGrid, std::vector<std::vector<cv::Point3d> >  &vpHypo, std::vector<cv::Point3d> &vps  );

	void lines2Vps( double thAngle, std::vector<cv::Point3d> &vps, std::vector<std::vector<int> > &clusters );

	std::vector<std::vector<double> > lines;
	std::vector<LineInfo> lineInfos;
	cv::Point2d pp;
	double f;
	double noiseRatio;
};






#endif // _VP_DETECTION_H_
