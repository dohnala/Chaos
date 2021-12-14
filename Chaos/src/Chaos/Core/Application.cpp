#include "Chaos/Core/Application.h"

namespace Chaos
{
	Application* Application::s_Instance = nullptr;

	Application::Application(const std::string& name)
	{
		CH_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = Window::Create(WindowProps(name));
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (true)
		{
			m_Window->OnUpdate();
		}
	}
}