#include "pch.h"
#include "Chaos/Renderer/Renderer.h"
#include "Chaos/Renderer/Shader.h"

#include "Platform/OpenGL/OpenGLGraphicsAPI.h"

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

		std::string rectVertexShaderSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			void main()
			{
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string rectFragmentShaderSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
}
		)";

		s_Rect = new RendererPrimitive();
		s_Rect->VertexArray = m_VertexArray;
		s_Rect->Shader = Shader::Create("rect", rectVertexShaderSrc, rectFragmentShaderSrc);

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

	void Renderer::DrawRect()
	{
		s_GraphicsAPI->DrawIndexed(s_Rect->VertexArray);
	}
}