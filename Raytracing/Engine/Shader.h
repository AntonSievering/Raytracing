#pragma once
#include <fstream>
#include "defines.h"
#include <GL/glew.h>
#include <string>

namespace Engine
{
	class Shader
	{
	private:
		GLuint shaderId;

	public:
		Shader();
		Shader(const std::string &vertexShaderFilename, const std::string &fragmentShaderFilename);
		virtual ~Shader();

	private:
		GLuint compile(const std::string &shaderSource, GLenum type);
		std::string parse(const std::string &filename);
		GLuint createShader(const std::string &vertexShaderFilename, const std::string &fragmentShaderFilename);

	public:
		void bind();
		void unbind();
		GLuint getShaderId();
		int getUniformLocation(const std::string &variableName);
	};
}
