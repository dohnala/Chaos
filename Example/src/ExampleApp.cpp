#include <Chaos.h>

#include <glm/glm.hpp>

class ExampleLayer : public Chaos::Layer
{
public:
	ExampleLayer()
		: Layer("ExampleLayer")
	{
		auto& window = Chaos::Application::Get().GetWindow();
		CreateCamera(window.GetWidth(), window.GetHeight());
	}

	void OnAttach() override
	{
		CH_TRACE("ExampleLayer::OnAttach");
	}

	void OnDetach() override
	{
		CH_TRACE("ExampleLayer::OnDetach");
	}

	void OnUpdate(Chaos::Timestep ts) override
	{
		Chaos::Renderer::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Chaos::Renderer::Clear();

		Chaos::Renderer::BeginScene(*m_Camera);
		Chaos::Renderer::DrawCircle({ -4.0f, -4.0f }, 1.0f, { 0.8f, 0.8f, 0.3f, 1.0f }, 0.5f, 0.2f);
		Chaos::Renderer::DrawCircle({  4.0f, -4.0f }, 2.0f, { 0.2f, 0.8f, 0.3f, 1.0f }, 0.6f, 0.2f);
		Chaos::Renderer::DrawCircle({ 4.0f, 4.0f }, 4.0, { 0.2f, 0.3f, 0.8f, 1.0f });
		Chaos::Renderer::DrawRect({ -4.0f, 4.0f }, { 4.0f, 4.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Chaos::Renderer::EndScene();
	}

	void OnEvent(Chaos::Event& event) override
	{
		Chaos::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Chaos::WindowResizeEvent>(CH_BIND_EVENT_FN(ExampleLayer::OnWindowResize));
	}

	bool OnWindowResize(Chaos::WindowResizeEvent& event)
	{
		float aspectRation = (float)event.GetWidth() / (float)event.GetHeight();

		m_Camera->SetProjection(-m_CameraHeight * aspectRation, m_CameraHeight * aspectRation, -m_CameraHeight, m_CameraHeight);

		return false;
	}

	void CreateCamera(uint32_t width, uint32_t height)
	{
		float aspectRation = (float)width / (float)height;

		m_Camera = Chaos::CreateScope<Chaos::OrthographicCamera>(-m_CameraHeight * aspectRation, m_CameraHeight * aspectRation, -m_CameraHeight, m_CameraHeight);
	}
private:
	const float m_CameraHeight = 10.0f;
	Chaos::Scope<Chaos::OrthographicCamera> m_Camera;
};

class ExampleApp : public Chaos::Application
{
public:
	ExampleApp()
		: Application("Example App", 1280, 720)
	{
		CH_INFO("ExampleApp started");

		PushLayer(new ExampleLayer());
	}

	~ExampleApp()
	{}
};

Chaos::Application* Chaos::CreateApplication()
{
	return new ExampleApp();
}