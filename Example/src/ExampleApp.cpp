#include <Chaos.h>

#include <glm/glm.hpp>

class ExampleLayer : public Chaos::Layer
{
public:
	ExampleLayer()
		: Layer("ExampleLayer")
	{}

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
		Chaos::Renderer::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Chaos::Renderer::Clear();

		// Position, Rotation, Size, Color
		Chaos::Renderer::DrawCircle({ -4.0f, -4.0f }, 1.0f, { 0.8f, 0.8f, 0.3f, 1.0f }, 0.5f, 0.2f);
		Chaos::Renderer::DrawCircle({  4.0f, -4.0f }, 2.0f, { 0.2f, 0.8f, 0.3f, 1.0f }, 0.6f, 0.2f);
		Chaos::Renderer::DrawCircle({ 4.0f, 4.0f }, 4.0, { 0.2f, 0.3f, 0.8f, 1.0f });
		Chaos::Renderer::DrawRotatedRect({ -4.0f, 4.0f }, 225.0f, { 4.0f, 4.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
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
		: Application("Example App", 600, 600)
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