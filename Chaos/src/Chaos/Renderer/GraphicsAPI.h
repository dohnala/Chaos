#pragma once

namespace Chaos
{
	class GraphicsAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1
		};
	public:
		static API GetAPI() { return s_API; }
	private:
		static API s_API;
	};
}