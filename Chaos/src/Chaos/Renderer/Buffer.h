#pragma once

#include "Chaos/Core/Base.h"

namespace Chaos
{
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Ref<VertexBuffer> Create(float* vertices, uint32_t size);
	};
}