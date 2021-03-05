#pragma once
#include "VertexBuffer.h"
#include "Defines.h"
#include "Shader.h"
#include "Image.h"

namespace Engine
{
	class Sprite
	{
	private:
		GLuint textureId;
		Image *image;

	public:
		Sprite()                                                                                                        noexcept;
		Sprite(Image *image, const GLint &min_filter = GL_LINEAR, const GLint &mag_filter = GL_NEAREST)                 noexcept;
		Sprite(const vu2d &size, const GLint &min_filter = GL_LINEAR, const GLint &mag_filter = GL_NEAREST)             noexcept;
		Sprite(const std::string &sFilename, const GLint &min_filter = GL_LINEAR, const GLint &mag_filter = GL_NEAREST) noexcept;
		virtual ~Sprite()                                                                                               noexcept;

	private:
		void uploadData(const GLint &min_filter, const GLint &mag_filter) noexcept;

	public:
		void  SetPixel(const vu2d &pos, const Pixel &col) noexcept;
		Pixel GetPixel(const vu2d &pos)             const noexcept;
		vf2d  GetSize()                             const noexcept;
		Image *GetImage()                           const noexcept;

		void  reupload()                            const noexcept;
		void  bind()                                const noexcept;
		float getAspectRatio()                      const noexcept;
	};
}
