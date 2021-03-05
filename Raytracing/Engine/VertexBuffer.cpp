#include "VertexBuffer.h"

namespace Engine
{
	BaseVertexBuffer::BaseVertexBuffer() noexcept
	{
		bufferId = GLuint();
		vao      = GLuint();
	}

	BaseVertexBuffer::~BaseVertexBuffer() noexcept
	{
		glDeleteBuffers(1, &bufferId);
		glDeleteVertexArrays(1, &vao);
	}

	void BaseVertexBuffer::bind() const noexcept
	{
		glBindVertexArray(vao);
	}


	VertexBuffer::VertexBuffer() noexcept
		: BaseVertexBuffer()
	{
	}

	VertexBuffer::VertexBuffer(Vertex2D *data, uint32_t nVertices) noexcept
	{
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &bufferId);
		glBindBuffer(GL_ARRAY_BUFFER, bufferId);
		glBufferData(GL_ARRAY_BUFFER, nVertices * sizeof(Vertex2D), data, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void*)offsetof(Vertex2D, x));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void*)offsetof(Vertex2D, u));
	}

	void VertexBuffer::reshape(Vertex2D *data, uint32_t nVertices) noexcept
	{
		bind();
		glBindBuffer(GL_ARRAY_BUFFER, bufferId);
		glBufferData(GL_ARRAY_BUFFER, nVertices * sizeof(Vertex2D), data, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void *)offsetof(Vertex2D, x));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void *)offsetof(Vertex2D, u));
	}



	VertexBufferColor::VertexBufferColor() noexcept
		: BaseVertexBuffer()
	{
	}

	VertexBufferColor::VertexBufferColor(Vertex2DC *data, uint32_t nVertices) noexcept
	{
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &bufferId);
		glBindBuffer(GL_ARRAY_BUFFER, bufferId);
		glBufferData(GL_ARRAY_BUFFER, nVertices * sizeof(Vertex2DC), data, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DC), (void *)offsetof(Vertex2DC, x));
	}

	void VertexBufferColor::reshape(Vertex2DC *data, uint32_t nVertices) noexcept
	{
		bind();
		glBindBuffer(GL_ARRAY_BUFFER, bufferId);
		glBufferData(GL_ARRAY_BUFFER, nVertices * sizeof(Vertex2DC), data, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DC), (void *)offsetof(Vertex2DC, x));
	}

	VertexBuffer3D::VertexBuffer3D() noexcept
		: BaseVertexBuffer() {}

	VertexBuffer3D::VertexBuffer3D(Vertex *data, uint32_t nVertices) noexcept
	{
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &bufferId);
		glBindBuffer(GL_ARRAY_BUFFER, bufferId);
		glBufferData(GL_ARRAY_BUFFER, nVertices * sizeof(Vertex), data, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, pos));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
	}

	void VertexBuffer3D::reshape(Vertex *data, uint32_t nVertices) noexcept
	{
		bind();
		glBindBuffer(GL_ARRAY_BUFFER, bufferId);
		glBufferData(GL_ARRAY_BUFFER, nVertices * sizeof(Vertex), data, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, pos));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
	}
}