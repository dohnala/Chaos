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
	static RendererPrimitive* s_Polygon;

	PolygonPropsBuilder PolygonProps::Create()
	{
		return PolygonPropsBuilder();
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

		s_Polygon = new RendererPrimitive();
		s_Polygon->VertexArray = m_VertexArray;
		s_Polygon->Shader = Shader::Create("assets/shaders/Polygon.glsl");

		// currently we support only rects geometry, so we bind vertex array only once
		s_Rect->VertexArray->Bind();
	}

	void Renderer::Shutdown()
	{
		delete s_Rect;
		delete s_Circle;
		delete s_Polygon;
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

		s_Polygon->Shader->Bind();
		s_Polygon->Shader->SetFloat("u_Time", ts.GetTime());
		s_Polygon->Shader->SetMat4("u_ViewProjection", viewProjection);
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
		s_Circle->Shader->SetFloat4("u_Color", circleProps.Color);
		s_Circle->Shader->SetFloat("u_Thickness", circleProps.Thickness);
		s_Circle->Shader->SetFloat("u_Circumference", circleProps.Circumference);
		s_Circle->Shader->SetInt("u_GapCount", circleProps.GapCount);
		s_Circle->Shader->SetFloat("u_GapSize", circleProps.GapSize);
		s_Circle->Shader->SetFloat("u_Rotation", circleProps.Rotation);

		s_GraphicsAPI->DrawIndexed(s_Circle->VertexArray);
	}

	void Renderer::DrawPolygon(const glm::vec2& position, const glm::vec2& size, const PolygonProps& polygonProps)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, 0.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawPolygon(transform, polygonProps);
	}

	void Renderer::DrawPolygon(const glm::vec2& position, float rotation, const glm::vec2& size, const PolygonProps& polygonProps)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, 0.0f })
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawPolygon(transform, polygonProps);
	}

	void Renderer::DrawPolygon(const glm::mat4& transform, const PolygonProps& polygonProps)
	{
		s_Polygon->Shader->Bind();
		s_Polygon->Shader->SetMat4("u_Transform", transform);
		s_Polygon->Shader->SetInt("u_VertexCount", polygonProps.VertexCount);
		s_Polygon->Shader->SetFloat4("u_Color", polygonProps.Color);

		s_GraphicsAPI->DrawIndexed(s_Polygon->VertexArray);
	}
}