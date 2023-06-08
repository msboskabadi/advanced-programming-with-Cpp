#include "pch.h"
#include "Mat-util.h"

#pragma comment (lib,"gdiplus.lib")

//angle must be in degree
void imrotate(cv::Mat& src, double angle, cv::Mat& dst)
{
	double rad_angle = angle * PI / 180.0; //in radian
	//int len = MAX(src.cols, src.rows);

	double c = cos(rad_angle);
	double s = sin(rad_angle);

	// Calculate the size of the new Matrix
	double W = src.cols*abs(c) + src.rows * abs(s);
	double H = src.rows*abs(c) + src.cols * abs(s);

	//cv::Point2f pt(len / 2., len / 2.);
	auto cX = src.cols / 2.0f;
	auto cY = src.rows / 2.0f;
	cv::Point2f pt(cX, cY);
	//https://learnopencv.com/image-rotation-and-translation-using-opencv/
	cv::Mat r = cv::getRotationMatrix2D(pt, angle, 1.0);

	std::string my_str = "rotation mat :";
	my_str << r;  

	OutputDebugStringA(my_str.c_str());
	//adjust the rotation matrix to take care of TRANSLATION 
	r.at<double>(0, 2) += (W / 2) - cX;
	r.at<double>(1, 2) += (H / 2) - cY;

	cv::warpAffine(src, dst, r, cv::Size((int)W, (int)H), 1, 0, Scalar(127, 127, 127));
}

int Mat2CImage(Mat &mat, CImage &img)
{
	if(mat.empty())
		return -1;

	int bpp = mat.channels()*8;
	bool create_new = true;
	if (!img.IsNull())
	{
		if (img.GetHeight() == mat.rows && img.GetWidth() == mat.cols && img.GetBPP() == bpp)
			create_new = false;
		else
			img.Detach();
	}

	if (create_new)
		img.Create(mat.cols, mat.rows, bpp);

	if(bpp == 8)
	{
		static RGBQUAD pRGB[256];
		for (int i = 0; i < 256; i++) {
			pRGB[i].rgbBlue = pRGB[i].rgbGreen = pRGB[i].rgbRed = i;
		}
		img.SetColorTable(0, 256, pRGB);
	}
	
	uchar* psrc = mat.data;
	uchar* pdst = (uchar*) img.GetBits();
	
	int imgPitch = img.GetPitch();
	for(int y = 0; y < mat.rows; y++)
	{
		memcpy(pdst, psrc, mat.cols*mat.channels());//mat.step is incorrect for those images created by roi (sub-images!)
		psrc += mat.step;
		pdst += imgPitch;
	}
	//memcpy(pdst, psrc, mat.rows*mat.cols*mat.channels());
	return 0;
}



cv::Mat ReadImage(const wchar_t* filename)
{
	FILE* fp = 0;
	_wfopen_s(&fp, filename, L"rb");
	if (!fp)
	{
		std::wstring msg = L"File\n" + std::wstring(filename) + L" could not be openned";
		//ShowMessage(msg.c_str());
		return Mat::zeros(10, 10, CV_8U);
	}
	fseek(fp, 0, SEEK_END);
	long sz = ftell(fp);
	char* buf = new char[sz];
	fseek(fp, 0, SEEK_SET);
	long n = fread(buf, 1, sz, fp);
	_InputArray arr(buf, sz);
	Mat img = imdecode(arr, cv::IMREAD_COLOR);
	delete[] buf;
	fclose(fp);
	return img;
}

