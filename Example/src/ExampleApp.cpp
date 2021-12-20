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
		Chaos::Renderer::DrawRect({ -0.4f, -0.4f }, { 0.5f, 0.5f }, { 0.2, 0.8, 0.3, 1.0 });
		Chaos::Renderer::DrawRect({  0.4f, -0.4f }, { 0.5f, 0.5f }, { 0.8, 0.8, 0.3, 1.0 });
		Chaos::Renderer::DrawRotatedRect({  0.4f,  0.4f }, 135.0f, { 0.5f, 0.5f }, { 0.2, 0.3, 0.8, 1.0 });
		Chaos::Renderer::DrawRotatedRect({ -0.4f,  0.4f }, 225.0f, { 0.5f, 0.5f }, { 0.8, 0.2, 0.3, 1.0 });
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