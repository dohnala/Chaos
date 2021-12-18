#include "pch.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Chaos
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case Chaos::ShaderDataType::Float:    return GL_FLOAT;
			case Chaos::ShaderDataType::Float2:   return GL_FLOAT;
			case Chaos::ShaderDataType::Float3:   return GL_FLOAT;
			case Chaos::ShaderDataType::Float4:   return GL_FLOAT;
			case Chaos::ShaderDataType::Mat3:     return GL_FLOAT;
			case Chaos::ShaderDataType::Mat4:     return GL_FLOAT;
			case Chaos::ShaderDataType::Int:      return GL_INT;
			case Chaos::ShaderDataType::Int2:     return GL_INT;
			case Chaos::ShaderDataType::Int3:     return GL_INT;
			case Chaos::ShaderDataType::Int4:     return GL_INT;
			case Chaos::ShaderDataType::Bool:     return GL_BOOL;
		}

		CH_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_ID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_ID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_ID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		CH_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_ID);
		vertexBuffer->Bind();

		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(m_VertexBufferIndex);
			glVertexAttribPointer(m_VertexBufferIndex,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			m_VertexBufferIndex++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::AddIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_ID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}
}