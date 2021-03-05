#pragma once

#include "vec2d.h"
#include "stb_image.h"
#include "Pixel.h"


namespace Engine
{
	class Image
	{
	private:
		Pixel *data;
		vi2d size;

	public:
		Image()                                         noexcept;
		Image(const std::string &sFilename)             noexcept;
		Image(const vi2d &size)                         noexcept;
		virtual ~Image()                                noexcept;

	public:
		void   SetPixel(const vu2d &pos, const Pixel &col) noexcept;
		Pixel  GetPixel(const vu2d &pos)             const noexcept;
		vi2d   GetSize()                             const noexcept;
		Pixel *GetData()                             const noexcept;
		void   save(const std::string &sFilename)    const noexcept;
	};
}
