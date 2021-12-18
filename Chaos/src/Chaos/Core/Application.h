#pragma once

#include "Chaos/Core/Base.h"
#include "Chaos/Core/Window.h"
#include "Chaos/Core/LayerStack.h"
#include "Chaos/Events/ApplicationEvent.h"

int main(int argc, char** argv);

namespace Chaos
{
	class Application
	{
	public:
		Application(const std::string& name = "Chaos App", uint32_t width = 1280, uint32_t height = 720);
		virtual ~Application();

		void OnEvent(Event& e);

		void Close();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		Window& GetWindow() { return *m_Window; }

		static Application& Get() { return *s_Instance; }
	private:
		void Run();
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		Scope<Window> m_Window;
		LayerStack m_LayerStack;
		bool m_Running = true;
		bool m_Minimized = false;
	private:
		inline static Application* s_Instance = nullptr;
		friend int ::main(int argc, char** argv);
	};

	Application* CreateApplication();
}