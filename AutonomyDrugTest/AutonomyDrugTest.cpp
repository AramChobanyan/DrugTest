#include "AutonomyDrugTest.h"

double distanc(cv::Point p1, cv::Point p2)
{
    return std::sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}

void AutonomyDrugTest::run(const std::string& path)
{
	m_video.open(path);
	run();
}
void AutonomyDrugTest::run()
{
	
	cv::Mat frame;
	cv::namedWindow("frame", cv::WINDOW_NORMAL);
	while (true)
	{
		
		m_video >> frame;
		for (int i = 0; i < m_info.SIZE(); ++i)
		{
            std::cout << "LINE = " << __LINE__ << std::endl;
            cv::Ptr<cv::BRISK> detector = cv::BRISK::create();
            //cv::Ptr<cv::ORB> detector = cv::ORB::create();
            std::cout << "LINE = " << __LINE__ << std::endl;
            std::vector<cv::KeyPoint> keypoints1, keypoints2; 
            cv::Mat descriptors1, descriptors2;
            std::cout << "LINE = " << __LINE__ << std::endl;
            detector->detectAndCompute(m_info.getinfo().at(i).first, cv::noArray(), keypoints2, descriptors2);
            std::cout << "LINE = " << __LINE__ << std::endl;
            detector->detectAndCompute(frame, cv::noArray(), keypoints1, descriptors1);
            std::cout << "LINE = " << __LINE__ << std::endl;
            //////////////////////////////////////////////////
            cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create(cv::DescriptorMatcher::BRUTEFORCE);
            std::cout << "LINE = " << __LINE__ << std::endl;
            std::vector<cv::DMatch > matches, resultmatches;
            std::cout << "LINE = " << __LINE__ << std::endl;
            matcher->match(descriptors1, descriptors2, matches);
            std::cout << "LINE = " << __LINE__ << std::endl;
            std::vector<cv::Point2d> good_point1, good_point2;
            
            int minIndex = 0;
            for (int ii = 0; ii < matches.size(); ++ ii) {                
                if (matches.at(ii).distance < matches.at(minIndex).distance) {
                    minIndex = ii;
                }
            }

            double dist = matches.at(minIndex).distance;

            std::cout << "DIST : " << dist << "\n";

          
            
            for (int ii = 0; ii < matches.size(); ++ ii) {
                if (matches.at(ii).distance < 1.4 * dist) {
                    good_point1.push_back(keypoints1.at(matches.at(ii).queryIdx).pt);
                    good_point2.push_back(keypoints2.at(matches.at(ii).trainIdx).pt);
                    resultmatches.push_back(matches.at(ii));
                }
            }
            std::cout << "SIZE : " << resultmatches.size() << std::endl;

            
            cv::Mat img_matches;
            if (good_point2.size() < 4 || good_point2.size() > 100) { continue; }
            //cv::namedWindow("Homograf", cv::WINDOW_NORMAL);
            std::cout << "LINE = " << __LINE__ << std::endl;
            cv::Mat Homograf = cv::findHomography(good_point2, good_point1, /*cv::RANSAC */cv::USAC_PARALLEL);
           // cv::imshow("Homograf", Homograf);
            std::cout << "LINE = " << __LINE__ << std::endl;
            std::vector<cv::Point2f>p1(4), p2(4);
            p1.at(0) = cv::Point(0, 0);
            p1.at(1) = cv::Point(0, m_info.getinfo().at(i).first.rows);
            p1.at(2) = cv::Point(m_info.getinfo().at(i).first.cols, m_info.getinfo().at(i).first.rows);
            p1.at(3) = cv::Point(m_info.getinfo().at(i).first.cols, 0);
            std::cout << "LINE = " << __LINE__ << std::endl;
            std::cout << "p1.size() =" << p1.size() << std::endl;
            cv::namedWindow("homograf", cv::WINDOW_NORMAL);
            std::cout << "LINE = " << __LINE__ << std::endl;
            if (Homograf.cols == 0) { continue; }
            std::cout << "LINE = " << __LINE__ << std::endl;
            cv::perspectiveTransform(p1, p2, Homograf);




            cv::Mat orbimg = frame.clone();
            std::cout << "LINE = " << __LINE__ << std::endl;

           // if(std::abs(std::abs(p2[0].x - p2[1].x) - std::abs(p2[2].x - p2[3].x)) > 50){continue;}
           // if (std::abs(distanc(p2[0], p2[1])) < 100) { continue; }
           // if (std::abs(distanc(p2[0], p2[3])) < 100) { continue; }
           // if (std::abs(distanc(p2[2], p2[1])) < 100) { continue; }
            //if (std::abs(distanc(p2[2], p2[3])) < 100) { continue; }


            //if(std::abs(std::abs(p2[1].y - p2[2].y) - std::abs(p2[3].y - p2[0].y)) > 50){continue;}

            cv::line(orbimg, p2[0] ,p2[1] , cv::Scalar(0, 255, 0), 4);

            cv::line(orbimg, p2[1] ,p2[2] , cv::Scalar(0, 255, 0), 4);
           
            cv::line(orbimg, p2[2] ,p2[3], cv::Scalar(0, 255, 0), 4);
            
            cv::line(orbimg, p2[3] ,p2[0] , cv::Scalar(0, 255, 0), 4);

            cv::Point2d p = cv::Point2d((p2.at(1).x - p2.at(0).x) / distanc(p2.at(0), p2.at(1)), (p2.at(1).y - p2.at(0).y) / distanc(p2.at(0), p2.at(1)));
            p += cv::Point2d((p2.at(2).x - p2.at(3).x) / distanc(p2.at(3), p2.at(2)), (p2.at(2).y - p2.at(3).y) / distanc(p2.at(3), p2.at(2)));
            p /= 2;

       
           
                cv::line(orbimg, cv::Point2d(orbimg.cols / 2, orbimg.rows / 2) - (m_info.getinfo().at(i).second + p) * 1000, cv::Point2d(orbimg.cols / 2, orbimg.rows / 2) + (m_info.getinfo().at(i).second + p) * 1000, cv::Scalar(0, 0, 255), 2);
        

            cv::namedWindow("orbimg", cv::WINDOW_NORMAL);
            cv::imshow("orbimg", orbimg);

            

            cv::Mat warp;
            std::cout << "LINE = " << __LINE__ << std::endl;
            cv::warpPerspective(m_info.getinfo().at(i).first, warp, Homograf, frame.size());

            cv::namedWindow("warp", cv::WINDOW_NORMAL);
            cv::imshow("warp", warp);
            drawMatches( frame, keypoints1, m_info.getinfo().at(i).first, keypoints2,/*resultmatches */resultmatches, img_matches);
            //-- Show detected matches
            cv::namedWindow("Matches", cv::WINDOW_NORMAL);
            imshow("Matches", img_matches);

            std::cout << "------------------------------------------------------" << std::endl;
            cv::imshow("frame", frame);
		   cv::waitKey(0);
		}

       



		

	}








}