#pragma once

#include "Chaos/Core/Base.h"
#include "Chaos/Core/Window.h"
#include "Chaos/Core/LayerStack.h"

namespace Chaos
{
	class Application
	{
	public:
		Application(const std::string& name = "Chaos App");
		virtual ~Application();

		void Run();
		void Close();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		Scope<Window> m_Window;
		LayerStack m_LayerStack;
		bool m_Running = true;
	private:
		static Application* s_Instance;
	};

	Application* CreateApplication();
}