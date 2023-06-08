#include "stdafx.h"
#include "Mat-util.h"

//#pragma comment (lib,"gdiplus.lib")
using namespace cv;
//angle must be in degree
void imrotate(cv::Mat& src, double angle, cv::Mat& dst)
{
	double rad_angle = angle * PI / 180.0; //in radian
	int len = MAX(src.cols, src.rows);

	double c = cos(rad_angle);
	double s = sin(rad_angle);

	// Calculate the size of the new Matrix
	double W = src.cols*abs(c) + src.rows * abs(s);
	double H = src.rows*abs(c) + src.cols * abs(s);

	//cv::Point2f pt(len / 2., len / 2.);
	cv::Point2f pt(src.cols / 2.0f, src.rows / 2.0f);
	cv::Mat r = cv::getRotationMatrix2D(pt, angle, 1.0);

	cv::warpAffine(src, dst, r, cv::Size((int)W, (int)H), 1, 0, Scalar(255, 255, 255));
}

int Mat2CImage(cv::Mat *mat, CImage &img)
{
	if(!mat || mat->empty())
		return -1;
	int nBPP = mat->channels()*8;
	img.Create(mat->cols, mat->rows, nBPP);
	if(nBPP == 8)
	{
		static RGBQUAD pRGB[256];
		for (int i = 0; i < 256; i++)
			pRGB[i].rgbBlue = pRGB[i].rgbGreen = pRGB[i].rgbRed = i;
		img.SetColorTable(0, 256, pRGB);
	}
	uchar* psrc = mat->data;
	uchar* pdst = (uchar*) img.GetBits();
	int imgPitch = img.GetPitch();
	for(int y = 0; y < mat->rows; y++)
	{
		memcpy(pdst, psrc, mat->cols*mat->channels());//mat->step is incorrect for those images created by roi (sub-images!)
		psrc += mat->step;
		pdst += imgPitch;
	}
	//memcpy(pdst, psrc, mat->rows*mat->cols*mat->channels());
	return 0;
}


void ShowMessage(const wchar_t* msg, wchar_t* caption, UINT type)
{
	MessageBox(NULL, msg, caption, type);
}

cv::Mat ReadImage(const wchar_t* filename)
{
	FILE* fp = 0;
	_wfopen_s(&fp, filename, L"rb");
	if (!fp)
	{
		std::wstring msg = L"File\n" + std::wstring(filename) + L" could not be openned";
		ShowMessage(msg.c_str());
		return cv::Mat::zeros(10, 10, CV_8U);
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

