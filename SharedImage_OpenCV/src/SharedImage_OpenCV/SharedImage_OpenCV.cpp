#pragma warning(disable : 4819)
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#include "SharedImage_OpenCV.h"

SharedImage::SharedImage(const char *name, const int &width, const int &height)
	: shmem_(INVALID_HANDLE_VALUE), buf_(nullptr), flip_h_(false), flip_v_(true)
{
	this->name_ = name;
	int shmem_size = width * height * 4;

	shared_image_.create(cv::Size(width, height), CV_8UC4);

	shmem_ = ::CreateFileMapping(
		INVALID_HANDLE_VALUE,
		NULL,
		PAGE_READWRITE,
		0,
		shmem_size,
		name
		);

	buf_ = (uchar*)::MapViewOfFile(shmem_, FILE_MAP_ALL_ACCESS, 0, 0, shmem_size);

	shared_image_.data = buf_;
}

SharedImage::~SharedImage()
{
	shared_image_.release();
	
	if (buf_ != nullptr) {
		::UnmapViewOfFile(buf_);
		buf_ = nullptr;
	}

	if (shmem_ != INVALID_HANDLE_VALUE) {
		::CloseHandle(shmem_);
		shmem_ = INVALID_HANDLE_VALUE;
	}
}

bool SharedImage::flip_h() const
{
	return flip_h_;
}

void SharedImage::flip_h(const bool &val)
{
	flip_h_ = val;
}

bool SharedImage::flip_v() const
{
	return flip_v_;
}

void SharedImage::flip_v(const bool &val)
{
	flip_v_ = val;
}

void SharedImage::upload(const cv::Mat &img)
{
	cv::Mat target_img;

	if (shared_image_.cols != img.cols || shared_image_.rows != img.rows) {
		cv::Mat resized_img;
		cv::resize(img, resized_img, shared_image_.size());

		target_img = resized_img;
	}
	else {
		img.copyTo(target_img);
	}

	if (flip_v_ == true && flip_h_ == true) {
		cv::flip(target_img, target_img, -1);
	}
	else if (flip_v_ == false && flip_h_ == true) {
		cv::flip(target_img, target_img, 0);
	}
	else if (flip_v_ == true && flip_h_ == false) {
		cv::flip(target_img, target_img, 1);
	}

	if (img.type() == CV_8UC1) {
		cv::cvtColor(target_img, shared_image_, cv::COLOR_GRAY2RGBA);
	}
	else if (img.type() == CV_8UC3) {
		cv::cvtColor(target_img, shared_image_, cv::COLOR_BGR2RGBA);
	}
	else if (img.type() == CV_8UC4) {
		cv::cvtColor(target_img, shared_image_, cv::COLOR_BGRA2RGBA);
	}
}

void SharedImage::download(cv::Mat &img)
{
	shared_image_.copyTo(img);
}
