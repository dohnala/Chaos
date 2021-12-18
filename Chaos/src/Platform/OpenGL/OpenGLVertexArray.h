#pragma once

#include "Chaos/Renderer/VertexArray.h"

namespace Chaos
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; };
		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;

		virtual const Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; };
		virtual void AddIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;
	private:
		uint32_t m_ID;
		uint32_t m_VertexBufferIndex = 0;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}