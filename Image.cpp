#include "Image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "./OpenGL/stb_image.h"

unsigned char* Image::LoadImg(std::string filename, int* x, int* y, int* channels_in_file, int desired_channels)
{
	// stbi_set_flip_vertically_on_load(true); //--- 이미지가 거꾸로 읽힌다면 추가
	return stbi_load(filename.c_str(), x, y, channels_in_file, desired_channels);
}

void Image::FreeImg(void* retval_from_stbi_load)
{
	stbi_image_free(retval_from_stbi_load);
}
