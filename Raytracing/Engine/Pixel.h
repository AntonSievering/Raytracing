#pragma once
#include <cstdint>
#include <iostream>

namespace Engine
{
	struct Pixel
	{
	public:
		// RGBA or 32-bit unsigned int
		union
		{
			uint32_t v;
			struct
			{
				uint8_t r, g, b, a;
			};
		};

	public:
		Pixel() noexcept
		{
			v = 0;
		}

		explicit Pixel(const uint32_t& n) noexcept
		{
			v = n;
		}

		Pixel(int r, int g, int b, int a = 255) noexcept
		{
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
		}

	public:
		Pixel operator+(const Pixel &col) const noexcept
		{
			return Pixel(col.r + r, col.g + g, col.b + b);
		}

		Pixel operator*(const float &val) const noexcept
		{
			return Pixel(r * val, g * val, b * val);
		}
	};

	Pixel PixelF(float r, float g, float b, float a = 1.0f);
}
