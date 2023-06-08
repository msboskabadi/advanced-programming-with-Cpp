// Object-Detection.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv.hpp>
#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
//
//
#ifdef _DEBUG
#pragma comment(lib, "opencv_world470d.lib")
#else
#pragma comment(lib, "opencv_world470.lib")
#endif


int main()
{
	cv::VideoCapture cap("D:\\Projects\\_OCV Samples\\768x576.avi");
	//cv::VideoCapture cap("http://192.168.43.1:8080/shot.jpg");
	if (!cap.isOpened())
	{
		printf("video file can not be opened!\n");
		return 0;
	}

	cv::Mat prev2_frame, prev_frame, gray_frame, dif1, dif2, diff, rgb_frame, back;
	
	cap >> rgb_frame;
	cv::cvtColor(rgb_frame, gray_frame, cv::COLOR_BGR2GRAY);
	
	//back = gray_frame;
	back = gray_frame.clone();
	prev_frame = gray_frame.clone();
	prev2_frame = gray_frame.clone();
	float alfa = 0.1;

	while (!rgb_frame.empty())
	{
		cv::imshow("RGB", rgb_frame);
		
		//cv::waitKey(30);
		//cap.release();
		//cap.open("http://192.168.43.1:8080/shot.jpg");
		cap >> rgb_frame;

		cv::cvtColor(rgb_frame, gray_frame, cv::COLOR_BGR2GRAY);
		cv::imshow("gray", gray_frame);
		
		//addWeighted(back, 1 - alfa, gray_frame, alfa, 0, back);
		back = back*(1.0f - alfa) + gray_frame*alfa;
		//double minVal=255, maxVal=0;
		//cv::minMaxLoc(back, &minVal, &maxVal);
		//cv::convertScaleAbs(back, back, 255.0 / (maxVal - minVal), -minVal * 255.0 / (maxVal - minVal));
		cv::imshow("back", back);

		//diff = abs(gray_frame - back);
		//cv::imshow("diff", diff);
		//diff = diff > 40;

		//diff = abs(gray_frame - prev_frame);
		//diff = diff > 15;

		dif1 = abs(gray_frame - prev_frame);
		dif2 = abs(prev_frame - prev2_frame);
		diff = max(dif1, dif2);
		cv::imshow("diff gray", diff);
		diff = diff > 15;
		cv::imshow("diff binary", diff);
		
		cv::Mat labels, stats, centers;
		int n = cv::connectedComponentsWithStats(diff, labels, stats, centers);
		for (int i = 0; i < n; i++)
		{
			cv::Rect rc;
			/*rc.x = stats.at<int>(i, cv::CC_STAT_LEFT);
			rc.y = stats.at<int>(i, cv::CC_STAT_TOP);
			rc.width = stats.at<int>(i, cv::CC_STAT_WIDTH);
			rc.height = stats.at<int>(i, cv::CC_STAT_HEIGHT);*/

			int* si   = stats.ptr<int>(i);
			rc.x	  = si[cv::CC_STAT_LEFT];
			rc.y	  = si[cv::CC_STAT_TOP];
			rc.width  = si[cv::CC_STAT_WIDTH];
			rc.height = si[cv::CC_STAT_HEIGHT];
			if (rc.width < 10 || rc.height < 20)
				continue;
			cv::rectangle(diff, rc, cv::Scalar(255, 0, 0));
			cv::rectangle(rgb_frame, rc, cv::Scalar(255, 0, 0));
		}
		cv::imshow("original", rgb_frame);
		cv::imshow("diff", diff);
		cv::imshow("diff1", dif1);
		cv::imshow("diff2", dif2);

		
		int key = cv::waitKey(20);
		if (key == 27)
			break;
		
		prev2_frame = prev_frame.clone();
		prev_frame = gray_frame.clone();
		
	}
    return 0;
}

