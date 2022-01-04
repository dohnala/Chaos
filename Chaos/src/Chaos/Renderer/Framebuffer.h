#pragma once

#include "Chaos/Core/Base.h"

namespace Chaos
{
	struct FramebufferProps
	{
		uint32_t Width = 0, Height = 0;
	};

	class Framebuffer
	{
	public:
		virtual ~Framebuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;

		virtual const FramebufferProps& GetProps() const = 0;

		static Ref<Framebuffer> Create(const FramebufferProps& props);
	};
}