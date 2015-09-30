#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <iostream>
#include <sstream>

#pragma warning(disable : 4819)

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#ifdef _DEBUG
#pragma comment(lib, "opencv_world300d.lib")
#else
#pragma comment(lib, "opencv_world300.lib")
#endif

#include "SharedImage_OpenCV.h"

void draw_text(cv::Mat &canvas, const char *str, int x, int y, float scale = 1.0)
{
	int w = 2;
	for (int dy = -w; dy <= w; ++dy) {
		for (int dx = -w; dx <= w; ++dx) {
			cv::putText(canvas, str, cv::Point(x + dx, y + dy), cv::FONT_HERSHEY_SIMPLEX, scale, cv::Scalar(0, 0, 0), 2, CV_AA);
		}
	}

	cv::putText(canvas, str, cv::Point(x, y), cv::FONT_HERSHEY_SIMPLEX, scale, cv::Scalar(255, 255, 255), 2, CV_AA);
}

void draw(cv::Mat &img)
{
	static std::vector<cv::Mat> rgb;
	cv::split(img, rgb);

	std::vector<cv::Mat>::iterator it;
	for (it = rgb.begin(); it != rgb.end(); ++it) {
		cv::randu(*it, 0, 255);
	}
	cv::merge(rgb, img);

	cv::rectangle(img, cv::Rect(100, 50, 200, 200), cv::Scalar(0, 0, 255), CV_FILLED); //R
	cv::rectangle(img, cv::Rect(250, 150, 200, 200), cv::Scalar(0, 255, 0), CV_FILLED); //G
	cv::rectangle(img, cv::Rect(400, 250, 200, 200), cv::Scalar(255, 0, 0), CV_FILLED); //B

	std::stringstream ss;
	DWORD t = GetTickCount();
	ss << "SharedImage_OpenCV : t=" << t;

	draw_text(img, ss.str().c_str(), 10, 30);
}

int main(int argc, char* argv[])
{
	cv::Mat img(cv::Size(640, 480), CV_8UC3);

	SharedImage shared_img("testname", 640, 480);

	while (true) {
		draw(img);
		shared_img.upload(img);

		cv::Mat resized_img;
		cv::resize(img, resized_img, cv::Size(320, 240));
		cv::imshow("SharedImage_OpenCV", resized_img);

		int c = cv::waitKey(1);
		if (c == 27) break;
	}

	cv::destroyAllWindows();

	return 0;
}
