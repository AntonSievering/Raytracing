#include "Sprite.h"

namespace Engine
{
	Sprite::Sprite() noexcept
	{
		image = nullptr;
		textureId = GLuint();
	}
	
	Sprite::Sprite(Image *image, const GLint &min_filter, const GLint &mag_filter) noexcept
	{
		this->image = image;
		uploadData(min_filter, mag_filter);
	}

	Sprite::Sprite(const vu2d &size, const GLint &min_filter, const GLint &mag_filter) noexcept
	{
		image = new Image(size);
		uploadData(min_filter, mag_filter);
	}

	Sprite::Sprite(const std::string &sFilename, const GLint &min_filter, const GLint &mag_filter) noexcept
	{
		image = new Image(sFilename);
		uploadData(min_filter, mag_filter);
	}

	Sprite::~Sprite() noexcept
	{
		glDeleteTextures(1, &textureId);
		
		if (image)
			delete image;
	}

	void Sprite::uploadData(const GLint &min_filter, const GLint &mag_filter) noexcept
	{
		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image->GetSize().x, image->GetSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->GetData());
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Sprite::SetPixel(const vu2d &pos, const Pixel &col) noexcept
	{
		image->SetPixel(pos, col);
	}
	
	Pixel Sprite::GetPixel(const vu2d &pos) const noexcept
	{
		return image->GetPixel(pos);
	}

	vf2d Sprite::GetSize() const noexcept
	{
		return image->GetSize();
	}

	Image *Sprite::GetImage() const noexcept
	{
		return image;
	}

	void Sprite::reupload() const noexcept
	{
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image->GetSize().x, image->GetSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->GetData());
	}

	void Sprite::bind() const noexcept
	{
		glBindTexture(GL_TEXTURE_2D, textureId);
	}
	
	float Sprite::getAspectRatio() const noexcept
	{
		return (float)image->GetSize().x / (float)image->GetSize().y;
	}
}