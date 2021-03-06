#include "shader.hpp"

#include "../utils/utils.hpp"

#include <vector>
#include <iostream>
#include <GL/glew.h>

#define PROJECTION_MATRIX "projection_matrix"

#define LEFT 0.0F
#define RIGHT 20.0F
#define BOTTOM 0.0F
#define TOP 20.0F
#define NEAR (-1.0F)
#define FAR 1.0F

namespace graphics {
	Shader::Shader(const char* vertPath, const char* fragPath)
		: m_VertexShaderPath(vertPath), m_FragmentShaderPath(fragPath), m_ShaderID(load())
	{

	}

	Shader::~Shader()
	{
		glDeleteProgram(m_ShaderID);
	}

	GLuint Shader::load() const
	{
		const GLuint program = glCreateProgram();
		const GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
		const GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

		const std::string vertSourceString = utils::read_file(m_VertexShaderPath);
		const std::string fragSourceString = utils::read_file(m_FragmentShaderPath);

		const char* vertSource = vertSourceString.c_str();
		const char* fragSource = fragSourceString.c_str();

		glShaderSource(vertex, 1, &vertSource, nullptr);
		glCompileShader(vertex);

		GLint result;
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE) {
			GLint length;
			glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(vertex, length, &length, &error[0]);
			std::cout << &error[0] << std::endl;
			glDeleteShader(vertex);
			return 0;
		}

		glShaderSource(fragment, 1, &fragSource, nullptr);
		glCompileShader(fragment);

		glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE) {
			GLint length;
			glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(fragment, length, &length, &error[0]);
			std::cout << &error[0] << std::endl;
			glDeleteShader(fragment);
			return 0;
		}

		glAttachShader(program, vertex);
		glAttachShader(program, fragment);

		glLinkProgram(program);

		glValidateProgram(program);

		glDeleteShader(vertex);
		glDeleteShader(fragment);

		return program;
	}

	void Shader::enable() const
	{
		glUseProgram(m_ShaderID);

		const maths::mat4 orthographic = maths::mat4::orthographic(LEFT, RIGHT, BOTTOM, TOP, NEAR, FAR);
		setUniformMat4(PROJECTION_MATRIX, orthographic);
	}

	void Shader::disable()
	{
		glUseProgram(0);
	}

	void Shader::setUniform4f(const GLchar* name, const maths::vec4& vector) const
	{
		glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
	}

	void Shader::setUniformMat4(const GLchar* name, const maths::mat4& matrix) const
	{
		glUniformMatrix4fvARB(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
	}

	GLint Shader::getUniformLocation(const GLchar* name) const
	{
		return glGetUniformLocation(m_ShaderID, name);
	}
}