#pragma once

#include "Chaos/Renderer/Shader.h"

namespace Chaos
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const std::string& GetName() const override { return m_Name; };
	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<uint32_t, std::string> PreProcess(const std::string& fileContent);
		void Compile(const std::unordered_map<uint32_t, std::string>& shaderSources);
	private:
		uint32_t m_ID;
		std::string m_Name;
	};
}