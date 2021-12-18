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
		Application(const std::string& name = "Chaos App");
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
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	Application* CreateApplication();
}