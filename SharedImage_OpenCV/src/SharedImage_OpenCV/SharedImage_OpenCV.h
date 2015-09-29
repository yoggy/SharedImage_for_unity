#pragma once

#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <string>

#pragma warning(disable : 4819)
#include <opencv2/core.hpp>

class SharedImage
{
public:
	SharedImage(const char *name, const int &width, const int &height);
	virtual ~SharedImage();

private:
	// noncopyable
	SharedImage(const SharedImage &obj) {}
	SharedImage& operator=(const SharedImage &obj) { return *this; }

public:
	bool flip_h() const;
	void flip_h(const bool &val);

	bool flip_v() const;
	void flip_v(const bool &val);

	void upload(const cv::Mat &img);
	void download(cv::Mat &img);

protected:
	std::string name_;

	HANDLE		shmem_;
	HANDLE		mutex_;
	uchar		*buf_;

	bool flip_h_;
	bool flip_v_;

	cv::Mat shared_image_;
};

