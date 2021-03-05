#pragma once
#include <SDL.h>
#include <GL/glew.h>

class Texture1D
{
private:
	GLuint textureId;
	int size;

public:
	Texture1D(int size, float *data)
	{
		this->size = size;
		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_1D, textureId);

		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA32F, size, 0, GL_RGBA, GL_FLOAT, data);
	}

	~Texture1D()
	{
		glDeleteTextures(1, &textureId);
	}

public:
	void bind() const noexcept
	{
		glBindTexture(GL_TEXTURE_1D, textureId);
	}

	void unbind() const noexcept
	{
		glBindTexture(GL_TEXTURE_1D, 0);
	}

	void reupload(float *data)
	{
		bind();
		glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA32F, size, 0, GL_RGBA, GL_FLOAT, data);
	}
};