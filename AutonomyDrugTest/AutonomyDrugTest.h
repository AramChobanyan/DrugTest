#pragma once
#include<iostream>
#include"Data.h"
class AutonomyDrugTest
{
private:
	cv::Mat m_Originalimg;
	cv::VideoCapture m_video;
	cv::Mat m_ResultImg;
	Data m_info;

	void run();
public:
	AutonomyDrugTest():m_info("D:\\Users\\source\\Aram\\AutonomyDrugTest\\Data\\ping",3){}
	void run(const std::string& path);




};

