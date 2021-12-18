#include <Chaos.h>

#include <glm/glm.hpp>

class ExampleLayer : public Chaos::Layer
{
public:
	ExampleLayer()
		: Layer("ExampleLayer")
	{
		
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
		Chaos::Renderer::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Chaos::Renderer::Clear();

		Chaos::Renderer::DrawRect();
	}

	void OnEvent(Chaos::Event& event) override
	{
		CH_TRACE("ExampleLayer::OnEvent - {0}", event);
	}
private:
	Chaos::Ref<Chaos::VertexArray> m_VertexArray;
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