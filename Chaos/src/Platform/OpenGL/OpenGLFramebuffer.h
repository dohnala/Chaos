#pragma once

#include "Chaos/Renderer/Framebuffer.h"

namespace Chaos
{
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferProps& props);
		virtual ~OpenGLFramebuffer();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void Resize(uint32_t width, uint32_t height) override;

		virtual const FramebufferProps& GetProps() const override { return m_Props; }
	private:
		void Invalidate();
	private:
		uint32_t m_ID = 0;
		uint32_t m_ColorAttachment;
		FramebufferProps m_Props;
	};
}