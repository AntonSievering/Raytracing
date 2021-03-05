#pragma once
#include <GL/glew.h>
#include "Defines.h"
#include <cstdint>
#include <stddef.h>

namespace Engine
{
	class BaseVertexBuffer
	{
	protected:
		GLuint bufferId;
		GLuint vao;

	public:
		BaseVertexBuffer()                                     noexcept;
		virtual ~BaseVertexBuffer()                            noexcept;

	public:
		void bind()                                      const noexcept;
	};


	class VertexBuffer : public BaseVertexBuffer
	{
	public:
		VertexBuffer()                                         noexcept;
		VertexBuffer(Vertex2D *data, uint32_t nVertices)       noexcept;
		
	public:
		void reshape(Vertex2D *data, uint32_t nVertices)       noexcept;
	};


	class VertexBufferColor : public BaseVertexBuffer
	{
	public:
		VertexBufferColor()                                    noexcept;
		VertexBufferColor(Vertex2DC *data, uint32_t nVertices) noexcept;

	public:
		void reshape(Vertex2DC *data, uint32_t nVertices)      noexcept;
	};


	class VertexBuffer3D : public BaseVertexBuffer
	{
	public:
		VertexBuffer3D()                                       noexcept;
		VertexBuffer3D(Vertex *data, uint32_t nVertices)       noexcept;

	public:
		void reshape(Vertex *data, uint32_t nVertices)         noexcept;
	};
}
