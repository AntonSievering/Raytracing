#include "Shader.h"
#include <iostream>

namespace Engine
{
	Shader::Shader()
	{
		shaderId = 0;
	}

	Shader::Shader(const std::string &vertexShaderFilename, const std::string &fragmentShaderFilename)
	{
		shaderId = createShader(vertexShaderFilename, fragmentShaderFilename);
	}

	Shader::~Shader()
	{
		glDeleteProgram(shaderId);
	}

	GLuint Shader::compile(const std::string &shaderSource, GLenum type)
	{
		GLuint id = glCreateShader(type);
		const char const *src = shaderSource.c_str();
		glShaderSource(id, 1, &src, 0);
		glCompileShader(id);

		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (result != GL_TRUE)
		{
			std::cout << "OpenGL Shader Compile Error: " << result << std::endl;

			int length = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char *msg = new char[length];
			glGetShaderInfoLog(id, length, &length, msg);

			std::cout << msg << std::endl;
			delete[] msg;

			return 0;
		}

		return id;
	}

	std::string Shader::parse(const std::string &filename)
	{
		std::fstream file = std::fstream(filename);
		std::string sSource = std::string(), sLine = std::string();

		if (file.is_open())
		{
			while (std::getline(file, sLine))
				sSource += sLine + '\n';
			file.close();
		}

		return sSource;
	}

	GLuint Shader::createShader(const std::string &vertexShaderFilename, const std::string &fragmentShaderFilename)
	{
		std::string vertexShader = parse(vertexShaderFilename);
		std::string fragmentShader = parse(fragmentShaderFilename);

		GLuint program = glCreateProgram();
		GLuint vs = compile(vertexShader, GL_VERTEX_SHADER);
		GLuint fs = compile(fragmentShader, GL_FRAGMENT_SHADER);

		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);

		glDetachShader(program, vs);
		glDetachShader(program, fs);
		glDeleteShader(vs);
		glDeleteShader(fs);

		return program;
	}

	void Shader::bind()
	{
		glUseProgram(shaderId);
	}

	void Shader::unbind()
	{
		glUseProgram(0);
	}

	GLuint Shader::getShaderId()
	{
		return shaderId;
	}
	int Shader::getUniformLocation(const std::string &variableName)
	{
		return glGetUniformLocation(shaderId, variableName.c_str());
	}
}