#pragma once
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#define GLM_ENABLE_EXPERIMENTAL 
#include<glm/gtx/transform.hpp>
#include<fstream>
#include<sstream>
#include<iostream>
#include<vector>
enum ShaderType
{
	VERTEX,
	FRAGMENT,
	GEOMETRY
};
class Shader
{
private:
	unsigned int m_ProgID;
	unsigned int m_VertID;
	unsigned int m_FragID;
	unsigned int m_GeomID;
public:
	Shader()
		:
		m_ProgID(0),
		m_VertID(0),
		m_FragID(0),
		m_GeomID(0)
	{

	}
	void LoadProgram()
	{
		std::cout << "Linking the program.\n";
		m_ProgID = glCreateProgram();
		if (m_VertID != 0)
			glAttachShader(m_ProgID, m_VertID);
		if (m_FragID != 0)
			glAttachShader(m_ProgID, m_FragID);
		if (m_GeomID != 0)
			glAttachShader(m_ProgID, m_GeomID);

		glLinkProgram(m_ProgID);

		GLint l_Result = 0;
		GLint l_LogLength = 0;
		glGetProgramiv(m_ProgID, GL_LINK_STATUS, &l_Result);
		glGetProgramiv(m_ProgID, GL_INFO_LOG_LENGTH, &l_LogLength);

		if (l_LogLength > 0)
		{
			std::vector<char> error(l_LogLength + 1);
			glGetProgramInfoLog(m_ProgID, l_LogLength, NULL, &error[0]);
			std::cout << (std::string(&error[0]));
		}

		if (m_VertID != 0)
			glDetachShader(m_ProgID, m_VertID);
		if (m_FragID != 0)
			glDetachShader(m_ProgID, m_FragID);
		if (m_GeomID != 0)
			glDetachShader(m_ProgID, m_GeomID);
	}
	void LoadShader(const char * p_Path, ShaderType p_Type)
	{
		std::ifstream l_InFileStream(p_Path, std::ios::in);
		std::stringstream l_SS;
		if (l_InFileStream.is_open())
		{
			l_SS << l_InFileStream.rdbuf();
			l_InFileStream.close();
		}
		else
		{
			std::cout << "Error Loading Shaders: Cannot open file stream.";
			return;
		}
		std::string l_Src = l_SS.str();
		const char * l_ShaderSrc = l_Src.c_str();
		unsigned int * l_ID = nullptr;
		std::string shader = " ";
		switch (p_Type)
		{
		case ShaderType::FRAGMENT:
			shader = "Fragment: ";
			m_FragID = glCreateShader(GL_FRAGMENT_SHADER);
			l_ID = &m_FragID;
			break;
		case ShaderType::GEOMETRY:
			shader = "Geometry: ";
			m_GeomID = glCreateShader(GL_GEOMETRY_SHADER);
			l_ID = &m_GeomID;
			break;
		case ShaderType::VERTEX:
			shader = "Vertex: ";
			m_VertID = glCreateShader(GL_VERTEX_SHADER);
			l_ID = &m_VertID;
			break;
		}
		GLint l_Result = GL_FALSE;
		GLint l_LogLength = 0;
		glShaderSource(*l_ID, 1, &l_ShaderSrc, NULL);
		glCompileShader(*l_ID);
		glGetShaderiv(*l_ID, GL_COMPILE_STATUS, &l_Result);
		glGetShaderiv(*l_ID, GL_INFO_LOG_LENGTH, &l_LogLength);

		if (l_LogLength > 0)
		{
			std::cout << "In " << shader;
			std::vector<char> error(l_LogLength + 1);
			glGetShaderInfoLog(*l_ID, l_LogLength, NULL, &error[0]);
			std::cout << (std::string(&error[0]));
		}
		else
		{
			std::cout << "Shader created..\n";
		}
	}
	unsigned int GetProgramID() const
	{
		return m_ProgID;
	}
	void Bind()
	{
		glUseProgram(m_ProgID);
	}
	unsigned int GetLocation(std::string p_Variable)
	{
		glGetUniformLocation(m_ProgID, p_Variable.c_str());
	}
	void setBool(const std::string &name, bool value) const
	{
		glUniform1i(glGetUniformLocation(m_ProgID, name.c_str()), (int)value);
	}
	// ------------------------------------------------------------------------
	void setInt(const std::string &name, int value) const
	{
		glUniform1i(glGetUniformLocation(m_ProgID, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void setFloat(const std::string &name, float value) const
	{
		glUniform1f(glGetUniformLocation(m_ProgID, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void setVec2(const std::string &name, const glm::vec2 &value) const
	{
		glUniform2fv(glGetUniformLocation(m_ProgID, name.c_str()), 1, &value[0]);
	}
	void setVec2(const std::string &name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(m_ProgID, name.c_str()), x, y);
	}
	// ------------------------------------------------------------------------
	void setVec3(const std::string &name, const glm::vec3 &value) const
	{
		glUniform3fv(glGetUniformLocation(m_ProgID, name.c_str()), 1, &value[0]);
	}
	void setVec3(const std::string &name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(m_ProgID, name.c_str()), x, y, z);
	}
	// ------------------------------------------------------------------------
	void setVec4(const std::string &name, const glm::vec4 &value) const
	{
		glUniform4fv(glGetUniformLocation(m_ProgID, name.c_str()), 1, &value[0]);
	}
	void setVec4(const std::string &name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(m_ProgID, name.c_str()), x, y, z, w);
	}
	// ------------------------------------------------------------------------
	void setMat2(const std::string &name, const glm::mat2 &mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(m_ProgID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void setMat3(const std::string &name, const glm::mat3 &mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(m_ProgID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void setMat4(const std::string &name, const glm::mat4 &mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(m_ProgID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	unsigned int GetShader(ShaderType p_Type) const
	{
		unsigned int l_RetnVal = -1;
		switch (p_Type)
		{
		case ShaderType::FRAGMENT:
			l_RetnVal = m_FragID;
			break;
		case ShaderType::GEOMETRY:
			l_RetnVal = m_GeomID;
			break;
		case ShaderType::VERTEX:
			l_RetnVal = m_VertID;
			break;
		}
		return l_RetnVal;
	}
};