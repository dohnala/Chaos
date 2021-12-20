#include "pch.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Chaos
{
	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;

		CH_CORE_ASSERT(false, "Unknown shader type!");
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		std::string fileContent = ReadFile(filepath);
		auto sources = PreProcess(fileContent);

		Compile(sources);

		// Extract name from filepath
		auto lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = filepath.rfind('.');
		auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		m_Name = filepath.substr(lastSlash, count);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
		: m_Name(name)
	{
		std::unordered_map<uint32_t, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;
		sources[GL_FRAGMENT_SHADER] = fragmentSrc;

		Compile(sources);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_ID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_ID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_ID, name.c_str());
		CH_CORE_ASSERT(location != -1, "Unknown uniform '{0}'!", name);

		glUniform1i(location, value);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
		GLint location = glGetUniformLocation(m_ID, name.c_str());
		CH_CORE_ASSERT(location != -1, "Unknown uniform '{0}'!", name);

		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
		GLint location = glGetUniformLocation(m_ID, name.c_str());
		CH_CORE_ASSERT(location != -1, "Unknown uniform '{0}'!", name);

		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
	{
		GLint location = glGetUniformLocation(m_ID, name.c_str());
		CH_CORE_ASSERT(location != -1, "Unknown uniform '{0}'!", name);

		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		std::string fileContent;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		
		if (in)
		{
			in.seekg(0, std::ios::end);
			fileContent.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&fileContent[0], fileContent.size());
			in.close();
		}
		else
		{
			CH_CORE_ERROR("Could not open file '{0}'", filepath);
		}

		return fileContent;
	}

	std::unordered_map<uint32_t, std::string> OpenGLShader::PreProcess(const std::string& fileContent)
	{
		std::unordered_map<GLenum, std::string> sources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);

		//Start of shader type declaration line
		size_t pos = fileContent.find(typeToken, 0);

		while (pos != std::string::npos)
		{
			//End of shader type declaration line
			size_t eol = fileContent.find_first_of("\r\n", pos);
			CH_CORE_ASSERT(eol != std::string::npos, "Syntax error");

			//Start of shader type name (after "#type " keyword)
			size_t begin = pos + typeTokenLength + 1;
			std::string type = fileContent.substr(begin, eol - begin);
			CH_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

			//Start of shader code after shader type declaration line
			size_t nextLinePos = fileContent.find_first_not_of("\r\n", eol);
			CH_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");

			//Start of next shader type declaration line
			pos = fileContent.find(typeToken, nextLinePos);

			sources[ShaderTypeFromString(type)] = (pos == std::string::npos) ? fileContent.substr(nextLinePos) : fileContent.substr(nextLinePos, pos - nextLinePos);
		}

		return sources;
	}

	void OpenGLShader::Compile(const std::unordered_map<uint32_t, std::string>& shaderSources)
	{
		CH_CORE_ASSERT(shaderSources.size() <= 2, "We only support 2 shaders for now");

		uint32_t program = glCreateProgram();

		std::array<uint32_t, 2> shaderIDs;
		int shaderIDIndex = 0;

		for (const auto& [type, source] : shaderSources)
		{
			uint32_t shader = glCreateShader(type);

			const GLchar* sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);

			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

			if (isCompiled == GL_FALSE)
			{
				GLint length = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

				char* message = (char*)alloca(length * sizeof(char));
				glGetShaderInfoLog(shader, length, &length, message);

				glDeleteShader(shader);

				CH_CORE_ERROR("{0}", message);
				CH_CORE_ASSERT(false, "Shader compilation failure!");
				break;
			}

			glAttachShader(program, shader);
			shaderIDs[shaderIDIndex++] = shader;
		}

		m_ID = program;

		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);

		if (isLinked == GL_FALSE)
		{
			GLint length = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

			char* message = (char*)alloca(length * sizeof(char));
			glGetProgramInfoLog(program, length, &length, message);

			glDeleteProgram(program);

			for (auto id : shaderIDs)
				glDeleteShader(id);

			CH_CORE_ERROR("{0}", message);
			CH_CORE_ASSERT(false, "Shader link failure!");
			return;
		}

		for (auto id : shaderIDs)
		{
			glDetachShader(program, id);
			glDeleteShader(id);
		}
	}
}