
#include "stdafx.h"



#include <opencv.hpp>
#include <vector>
#ifdef _DEBUG
#pragma comment (lib, "opencv_world470d.lib")
#else
#pragma comment (lib, "opencv_world470.lib")
#endif

// all the new API is put into "cv" namespace. Export its content
using namespace cv;
using namespace std;
//calculates histogram of a 3 channel image and returns a 256*3 matrix
#if 0 //detailed code
Mat calc_hist(Mat img)
{
	Mat hist_mat = Mat::zeros(img.channels(), 256, CV_32F);

	float* hist = (float*)hist_mat.data;
	
	//hist_mat.at<float>(1, 0) = 1;
	//hist[0 + 256] = 1;

	uchar* data = img.data;

	std::cout << "step: " << img.step;
	std::cout << "\nhstep: " << hist_mat.step;
	//float a,b,c;
	for (int y = 0; y < img.rows; y++)
		for(int x = 0; x < img.cols; x++)
		{
			int pixel = y*img.step + img.channels()*x;
			//hist_mat.at<float>( 0, data[ pixel   ] )++;// = hist_mat.at<float>(0, data[pixel   ])+1;
			//hist_mat.at<float>( 1, data[ pixel+1 ] )++;// = hist_mat.at<float>(1, data[pixel+1 ])+1;
			//hist_mat.at<float>( 2, data[ pixel+2 ] )++;// = hist_mat.at<float>(2, data[pixel+2 ])+1;


			hist[ data[ pixel ] ] ++;//blue
			if(img.channels() == 3)
			{
				hist[ 256 + data[pixel+1] ] ++;//green
				hist[ 512 + data[pixel+2] ] ++;//red
			}
		}
	return hist_mat;
}

Mat drawHist(Mat hist_mat, int histSize, int fig_w = 512, int fig_h = 400)
{
	//std::cout << "\nhhist chan: " << hist_mat.channels();
	int bin_w = cvRound( (double) fig_w/histSize );

	Mat histImage( fig_h, fig_w, CV_8UC3, Scalar( 220, 220, 220) );

	/// Normalize the result to [ 0, histImage.rows ]
	float* hist = (float*)hist_mat.data;
	normalize(hist_mat, hist_mat, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
	/// Draw
	Scalar Color1 = (hist_mat.rows == 1) ? Scalar( 100, 100, 100) : Scalar( 255, 0, 0);

	for( int i = 1; i < histSize; i++ )
	{
		//float h0 = hist_mat.at<float>(0, i-1);
		//float h1 = hist_mat.at<float>(0, i  );
		float h0 = hist[i-1];//blue
		float h1 = hist[i];

		line( histImage, Point( bin_w*(i-1), fig_h - cvRound(h0) ) ,
			Point( bin_w*(i), fig_h - cvRound(h1) ),
			Color1, 1, 8, 0  );

		if(hist_mat.rows == 1)
			continue;

		//h0 = hist_mat.at<float>(1, i-1);
		//h1 = hist_mat.at<float>(1, i  );

		h0 = hist[histSize + i-1];//green
		h1 = hist[histSize + i];
		line( histImage, Point( bin_w*(i-1), fig_h - cvRound(h0) ) ,
			Point( bin_w*(i), fig_h - cvRound(h1) ),
			Scalar( 0, 255, 0), 2, 8, 0  );

		//h0 = hist_mat.at<float>(2, i-1);
		//h1 = hist_mat.at<float>(2, i  );

		h0 = hist[2*histSize + i-1];//red
		h1 = hist[2*histSize + i];

		line( histImage, Point( bin_w*(i-1), fig_h - cvRound(h0) ) ,
			Point( bin_w*(i), fig_h - cvRound(h1) ),
			Scalar( 0, 0, 255), 2, 8, 0  );
	}

	return histImage;
}

int main( int argc, char** argv )
{
	const char* imagename = argc > 1 ? argv[1] : "..\\sample.png";
	Mat img = imread(imagename);

	if( !img.data ) // check if the image has been loaded properly
		return -1;
	imshow("original", img);
	
	Mat hist = calc_hist(img);
	// Draw the histograms for B, G and R
	Mat imHist = drawHist(hist, 256);
	imshow("original Histogram", imHist);

	//cv::waitKey(0);
	Mat img_gray, img_hsv, img_yuv, dst;
	// convert image to Gray color space.
	// The output image will be allocated automatically
	cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);
	imshow("gray scale", img_gray);

	hist = calc_hist(img_gray);
	imHist = drawHist(hist, 256);
	imshow("Gray Histogram", imHist);

	equalizeHist( img_gray, dst );
	imshow("Gray after hist equalization", dst);
	
	if(1)
	{
		std::vector<Mat> channels;
		split(img, channels);
		imshow("blue channel", channels[0]);
		imshow("green channel", channels[1]);
		imshow("red channel", channels[2]);

		equalizeHist(channels[0], channels[0]);
		equalizeHist(channels[1], channels[1]);
		equalizeHist(channels[2], channels[2]);
		Mat img2;
		merge(channels, img2);
		imshow("equalized BGR", img2);
	}

	hist = calc_hist(dst);
	imHist = drawHist(hist, 256);
	imshow("Equalized Histogram", imHist);

	waitKey();

	return 0;
	// all the memory will automatically be released
	// by vector<>, Mat and Ptr<> destructors.
}
#elif 1 //using cv::calcHist
int main(int argc, char** argv)
{
	const char* imagename = argc > 1 ? argv[1] : "..\\sample.png";//low contrast
	//const char* imagename = argc > 1 ? argv[1] : "..\\board.jpg";//green
	//const char* imagename = argc > 1 ? argv[1] : "..\\red.png";
	//const char* imagename = argc > 1 ? argv[1] : "..\\hue_0_100.bmp";
	
	Mat src, dst;
	src = imread(imagename);

	if (!src.data)
	{
		return -1;
	}
	
	imshow("input image", src);
	/// Separate the image in 3 places ( B, G and R )
	vector<Mat> bgr_planes;
	split(src, bgr_planes);

	/// Establish the number of bins
	int histSize = 256;

	/// Set the ranges ( for B,G,R) )
	float range[] = { 0, 256 }; //the upper boundary is exclusive
	const float* histRange = { range };

	bool uniform = true; bool accumulate = false;
	//accumulate flag doesn't do a cummulative histogram, it just doesn't set the histogram to zero at the beginning, 
	//so you can accumulate histograms over multiple images.


	Mat b_hist, g_hist, r_hist;

	/// Compute the histograms:
	calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);

	//create accumulated Hist
	//for (int i = 1; i < histSize; i++)
		//b_hist.at<float>(i) += b_hist.at<float>(i - 1);

	// Draw the histograms for B, G and R
	int fig_w = 1024; int fig_h = 800;
	int bin_w = cvRound((double)fig_w / histSize);

	Mat histImage(fig_h, fig_w, CV_8UC3, Scalar(0, 0, 0));

	/// Normalize the result to [ 0, histImage.rows ]
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	/// Draw for each channel
	for (int i = 1; i < histSize; i++)
	{
		line(histImage, Point(bin_w * (i - 1), fig_h - cvRound(b_hist.at<float>(i - 1))),
			Point(bin_w * (i), fig_h - cvRound(b_hist.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);
		line(histImage, Point(bin_w * (i - 1), fig_h - cvRound(g_hist.at<float>(i - 1))),
			Point(bin_w * (i), fig_h - cvRound(g_hist.at<float>(i))),
			Scalar(0, 255, 0), 2, 8, 0);
		line(histImage, Point(bin_w * (i - 1), fig_h - cvRound(r_hist.at<float>(i - 1))),
			Point(bin_w * (i), fig_h - cvRound(r_hist.at<float>(i))),
			Scalar(0, 0, 255), 2, 8, 0);
	}

	/// Display
	namedWindow("calcHist Demo", WINDOW_AUTOSIZE);
	imshow("calcHist Demo", histImage);

	waitKey(0);

	return 0;
}
#endif