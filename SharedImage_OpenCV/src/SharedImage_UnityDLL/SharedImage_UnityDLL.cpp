#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <stdlib.h>

typedef struct SharedImageData_ {
	unsigned char *buf_;
	HANDLE shmem_;
	int shmem_size_;
} SharedImageData;
 
extern "C" {
	__declspec(dllexport) void* SharedImageCreate(char* name, int width, int height)
	{

		SharedImageData *data = (SharedImageData*)malloc(sizeof(SharedImageData));
		memset(data, 0, sizeof(SharedImageData));

		data->shmem_size_ = width * height * 4;

		data->shmem_ = ::CreateFileMapping(
			INVALID_HANDLE_VALUE,
			NULL,
			PAGE_READWRITE,
			0,
			data->shmem_size_,
			name
			);

		data->buf_ = (unsigned char*)::MapViewOfFile(data->shmem_, FILE_MAP_ALL_ACCESS, 0, 0, data->shmem_size_);

		return data;
	}

	__declspec(dllexport) void* SharedImageGetBuffer(void *handle)
	{
		if (handle == nullptr) return nullptr;
		SharedImageData *data = (SharedImageData*)handle;

		return data->buf_;
	}

	__declspec(dllexport) void SharedImageRelease(void *handle)
	{
		if (handle == nullptr) return;
		SharedImageData *data = (SharedImageData*)handle;

		if (data->buf_ != nullptr) {
			::UnmapViewOfFile(data->buf_);
			data->buf_ = nullptr;
		}

		if (data->shmem_ != INVALID_HANDLE_VALUE) {
			::CloseHandle(data->shmem_);
			data->shmem_ = INVALID_HANDLE_VALUE;
		}
	}

	__declspec(dllexport) void SharedImageDownload(void *handle, void* buf)
	{
		if (handle == nullptr) return;
		if (buf == nullptr) return;

		SharedImageData *data = (SharedImageData*)handle;

		memcpy(buf, data->buf_, data->shmem_size_);
	}

	__declspec(dllexport) void SharedImageUpload(void *handle, void* buf)
	{
		if (handle == nullptr) return;
		if (buf == nullptr) return;

		SharedImageData *data = (SharedImageData*)handle;

		memcpy(data->buf_, buf, data->shmem_size_);
	}
};