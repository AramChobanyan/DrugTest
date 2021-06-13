#pragma once
#include<opencv2/opencv.hpp>
#include<iostream>
#include<xutility>
#include<cmath>

class  Data
{
private:
	std::vector< std::pair<cv::Mat, cv::Point2d>> info;
	size_t size;
public:
	Data(const std::string& path, size_t n)
	{
		size = n;
		for (int i = 0; i < n; ++i)
		{
			info.push_back(std::pair<cv::Mat, cv::Point2d>(cv::imread(path + '(' + std::to_string(i) + ").jpeg"), cv::Point2d()));
		}
		/////////////////////////////
		cv::Point p1, p2;
		p1.x = 100; p1.y = 56;
		p2.x = 102; p2.y = 173;
		float dist = distanc(p1, p2);
		info.at(0).second = cv::Point2d((p2.x - p1.x) / dist, (p2.y - p1.y) / dist);
		/////////////////////////////
		p1 = cv::Point(378, 69);
		p2 = cv::Point(379, 167);
		dist = distanc(p1, p2);
		info.at(1).second = cv::Point2d((p2.x - p1.x) / dist, (p2.y - p1.y) / dist);
		/////////////////////////////
		p1 = cv::Point(359, 53);
		p2 = cv::Point(366, 182);
		dist = distanc(p1, p2);
		info.at(2).second = cv::Point2d((p2.x - p1.x) / dist, (p2.y - p1.y) / dist);
	}
	size_t SIZE()const { return size; }

	const std::vector< std::pair<cv::Mat, cv::Point2d>>& getinfo()const { return info; }


	double distanc(cv::Point p1, cv::Point p2)
	{
		return std::sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
	}
};
