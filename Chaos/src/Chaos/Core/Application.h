#pragma once

#include "Chaos/Core/Base.h"
#include "Chaos/Core/Window.h"

namespace Chaos
{
	class Application
	{
	public:
		Application(const std::string& name = "Chaos App");
		virtual ~Application();

		void Run();

		inline static Application& Get() { return *s_Instance; }
	private:
		Scope<Window> m_Window;
	private:
		static Application* s_Instance;
	};

	Application* CreateApplication();
}