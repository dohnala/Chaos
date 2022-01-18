#include "pch.h"
#include "Chaos/Renderer/Renderer.h"
#include "Chaos/Renderer/Shader.h"

#include "Platform/OpenGL/OpenGLGraphicsAPI.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Chaos 
{
	Scope<GraphicsAPI> Renderer::s_GraphicsAPI = CreateScope<OpenGLGraphicsAPI>();

	struct RendererPrimitive
	{
		Ref<VertexArray> VertexArray;
		Ref<Shader> Shader;
	};

	static RendererPrimitive* s_Rect;
	static RendererPrimitive* s_Circle;

	CirclePropsBuilder CircleProps::Create()
	{
		return CirclePropsBuilder();
	}

	void Renderer::Init()
	{
		s_GraphicsAPI->Init();

		auto m_VertexArray = Chaos::VertexArray::Create();

		float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		auto m_VertexBuffer = Chaos::VertexBuffer::Create(vertices, sizeof(vertices));
		m_VertexBuffer->SetLayout({
			{Chaos::ShaderDataType::Float3, "a_Position"},
		});

		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		uint32_t indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		auto m_IndexBuffer = Chaos::IndexBuffer::Create(indices, sizeof(indices));

		m_VertexArray->AddIndexBuffer(m_IndexBuffer);

		s_Rect = new RendererPrimitive();
		s_Rect->VertexArray = m_VertexArray;
		s_Rect->Shader = Shader::Create("assets/shaders/Rect.glsl");

		s_Circle = new RendererPrimitive();
		s_Circle->VertexArray = m_VertexArray;
		s_Circle->Shader = Shader::Create("assets/shaders/Circle.glsl");

		// currently we support only rects geometry, so we bind vertex array only once both for rects and circles
		s_Rect->VertexArray->Bind();
	}

	void Renderer::Shutdown()
	{
		delete s_Rect;
	}

	void Renderer::Resize(uint32_t width, uint32_t height)
	{
		s_GraphicsAPI->SetViewport(0, 0, width, height);
	}

	void Renderer::SetClearColor(const glm::vec4& color)
	{
		s_GraphicsAPI->SetClearColor(color);
	}

	void Renderer::Clear()
	{
		s_GraphicsAPI->Clear();
	}

	void Renderer::BeginScene(const Camera& camera, const glm::vec2& cameraPosition, Timestep ts)
	{
		glm::mat4 view = glm::translate(glm::mat4(1.0f), { cameraPosition.x, cameraPosition.y, 0.0f });
		glm::mat4 viewProjection = camera.GetProjection() * glm::inverse(view);

		s_Rect->Shader->Bind();
		s_Rect->Shader->SetFloat("u_Time", ts.GetTime());
		s_Rect->Shader->SetMat4("u_ViewProjection", viewProjection);

		s_Circle->Shader->Bind();
		s_Circle->Shader->SetFloat("u_Time", ts.GetTime());
		s_Circle->Shader->SetMat4("u_ViewProjection", viewProjection);
	}

	void Renderer::EndScene()
	{}

	void Renderer::DrawRect(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, 0.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_Rect->Shader->Bind();
		s_Rect->Shader->SetMat4("u_Transform", transform);
		s_Rect->Shader->SetFloat4("u_Color", color);

		s_GraphicsAPI->DrawIndexed(s_Rect->VertexArray);
	}

	void Renderer::DrawCircle(const glm::vec2& position, float radius, const CircleProps& circleProps)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, 0.0f })
			* glm::scale(glm::mat4(1.0f), { radius * 2.0f, radius * 2.0f, 1.0f });

		s_Circle->Shader->Bind();
		s_Circle->Shader->SetMat4("u_Transform", transform);
		s_Circle->Shader->SetFloat("u_Radius", radius);
		s_Circle->Shader->SetFloat4("u_ColorInside", circleProps.ColorInside);
		s_Circle->Shader->SetFloat4("u_ColorOutside", circleProps.ColorOutside);
		s_Circle->Shader->SetFloat("u_ColorRatio", circleProps.ColorRatio);
		s_Circle->Shader->SetFloat("u_BorderDistortion", circleProps.BorderDistortion);
		s_Circle->Shader->SetFloat2("u_Direction", circleProps.Direction);
		s_Circle->Shader->SetFloat("u_DirectionDistortion", circleProps.DirectionDistortion);

		s_GraphicsAPI->DrawIndexed(s_Circle->VertexArray);
	}
}