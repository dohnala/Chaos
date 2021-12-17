#pragma once

#include "Chaos/Renderer/Buffer.h"

namespace Chaos
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;
	private:
		uint32_t m_ID;
	};
}