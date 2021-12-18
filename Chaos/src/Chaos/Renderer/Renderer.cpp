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

		// currently we support only rects, so we bind vertex array and shader only once
		// later it should be inside Draw* method
		s_Rect->VertexArray->Bind();
		s_Rect->Shader->Bind();
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

	void Renderer::DrawRect(const glm::vec2& position, float rotation, const glm::vec2& size, const glm::vec4& color)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, 0.0f })
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_Rect->Shader->SetFloat4("u_Color", color);
		s_Rect->Shader->SetMat4("u_Transform", transform);

		s_GraphicsAPI->DrawIndexed(s_Rect->VertexArray);
	}
}