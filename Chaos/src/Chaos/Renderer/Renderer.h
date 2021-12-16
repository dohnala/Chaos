#pragma once

#include "Chaos/Renderer/GraphicsAPI.h"

namespace Chaos
{
	class Renderer
	{
	public:
		static GraphicsAPI::API GetAPI() { return GraphicsAPI::GetAPI(); }
	};
}