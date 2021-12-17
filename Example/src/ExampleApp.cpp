#include <Chaos.h>

#include <glm/glm.hpp>

class ExampleLayer : public Chaos::Layer
{
public:
	ExampleLayer()
		: Layer("ExampleLayer")
	{
		glm::vec2 posi = glm::vec2(1.0f);

		float vertices[3*4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		m_VertexBuffer = Chaos::VertexBuffer::Create(vertices, sizeof(vertices));
		m_VertexBuffer->SetLayout({
			{Chaos::ShaderDataType::Float3, "a_Position"},
		});
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
private:
	Chaos::Ref<Chaos::VertexBuffer> m_VertexBuffer;
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