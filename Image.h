#pragma once
#include <string>

class Image
{
public:
	static unsigned char* LoadImg(std::string filename, int* x, int* y, int* channels_in_file, int desired_channels);
	static void FreeImg(void* retval_from_stbi_load);
};


