#include "Image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

namespace Engine
{
	Image::Image() noexcept
	{
		data = nullptr;
		size = vi2d();
	}

	Image::Image(const std::string &sFilename) noexcept
	{
		int32_t bitsPerPixel = 0;

		stbi_set_flip_vertically_on_load(true);
		data = (Pixel *)stbi_load(sFilename.c_str(), &size.x, &size.y, &bitsPerPixel, 4);
	}
	
	Image::Image(const vi2d &size) noexcept
	{
		this->size = size;
		data = new Pixel[(std::size_t)size.x * size.y];
	}

	Image::~Image() noexcept
	{
		if (data)
			delete data;
	}
	
	void Image::SetPixel(const vu2d &pos, const Pixel &col) noexcept
	{
		data[pos.y * size.x + pos.x] = col;
	}

	Pixel Image::GetPixel(const vu2d &pos) const noexcept
	{
		return data[pos.y * size.x + pos.x];
	}
	
	vi2d Image::GetSize() const noexcept
	{
		return size;
	}

	Pixel *Image::GetData() const noexcept
	{
		return data;
	}
	
	void Image::save(const std::string &sFilename) const noexcept
	{
		stbi_flip_vertically_on_write(true);
		stbi_write_png(sFilename.c_str(), size.x, size.y, 4, data, 4 * size.x);
	}
}