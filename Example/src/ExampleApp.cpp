#include <Chaos.h>

#include <glm/glm.hpp>

class ExampleLayer : public Chaos::Layer
{
public:
	ExampleLayer()
		: Layer("ExampleLayer")
	{
		glm::vec2 posi = glm::vec2(1.0f);
	}

	void OnAttach() override
	{
		CH_TRACE("ExampleLayer::OnAttach");
	}

	void OnDetach() override
	{
		CH_TRACE("ExampleLayer::OnDetach");
	}

	void OnUpdate() override
	{
		if (Chaos::Input::IsKeyPressed(Chaos::Key::F))
		{
			CH_INFO("F Pressed");
		}
	}

	void OnEvent(Chaos::Event& event) override
	{
		CH_TRACE("ExampleLayer::OnEvent - {0}", event);
	}
};

class ExampleApp : public Chaos::Application
{
public:
	ExampleApp()
		: Application("Example App")
	{
		CH_INFO("ExampleApp started");

		PushLayer(new ExampleLayer());
	}

	~ExampleApp()
	{
	}
};

Chaos::Application* Chaos::CreateApplication()
{
	return new ExampleApp();
}