#include<iostream>
#include"AutonomyDrugTest.h"
#include"Data.h"
int main()
{
	double startTime = cv::getTickCount();//$(SolutionDir)
	
	/*std::string path = "D:\\Users\\source\\Aram\\AutonomyDrugTest\\Data\\ping";

	Data ob(path, 3);
	cv::namedWindow("img", cv::WINDOW_NORMAL);



    for (int i = 0; i < ob.SIZE(); ++i)
	{
		cv::Mat img = ob.getinfo().at(i).first.clone();
        cv::Ptr<cv::ORB> detector = cv::ORB::create();
		std::vector<cv::KeyPoint> keypoints;
		cv::Mat descriptors;
        detector->detectAndCompute(ob.getinfo().at(i).first, cv::noArray(), keypoints, descriptors);
		std::cout << ob.getinfo().at(i).second << std::endl;
		for (int j = 0; j < keypoints.size(); ++j)
		{
			cv::circle(img, keypoints.at(j).pt, 1, cv::Scalar(0, 255, 0), cv::FILLED);
		}
		cv::imshow("img", img);
		cv::imshow("orim", ob.getinfo().at(i).first);
		cv::waitKey(0);
	}*/


	
	/*
	cv::VideoCapture vid(videopath );
	cv::Mat fram;
	cv::namedWindow("frame", cv::WINDOW_NORMAL);
	while (true)
	{
		vid >> fram;
		cv::imshow("frame", fram);
		cv::waitKey(1);
	}*/

	

    std::string path = "D:\\Users\\source\\Aram\\AutonomyDrugTest\\Data\\DrugTest.mp4";

	AutonomyDrugTest ob;
	ob.run(path);
	


	std::cout << "Execution Time : " << (cv::getTickCount() - startTime) / cv::getTickFrequency() << std::endl;
	return 0;
}