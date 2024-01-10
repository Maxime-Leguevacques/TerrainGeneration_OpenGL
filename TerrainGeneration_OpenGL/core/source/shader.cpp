#include "shader.h"



void Shader::CheckCompileErrors(unsigned int _shader, std::string _type)
{
	int success;
	char infoLog[1024];
	if (_type != "PROGRAM") {
		glGetShaderiv(_shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(_shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << _type << "\n" << infoLog << "\n------------------------------" << std::endl;
		}
	}
	else {
		glGetProgramiv(_shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(_shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << _type << "\n" << infoLog << "\n------------------------------" << std::endl;
		}
	}
}


Shader::Shader(const char* _vertexPath, const char* _fragmentPath)
{
	/* 1. Retrieve the vertex/fragment source code from _filePath */
	std::string vertexCode, fragmentCode;
	std::ifstream vShaderFile, fShaderFile;
	// ensure ifstream objects throw exceptions
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		// open files
		vShaderFile.open(_vertexPath);
		fShaderFile.open(_fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer into the streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	/* 2. Compile shaders */
	unsigned int vertex, fragment;

	// Vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	// Print compile errors if any
	CheckCompileErrors(vertex, "VERTEX");

	// Fragment shader
	fragment = glad_glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	// Print compile errors if any
	CheckCompileErrors(fragment, "FRAGMENT");

	// Shader program
	Id = glCreateProgram();
	glAttachShader(Id, vertex);
	glAttachShader(Id, fragment);
	glLinkProgram(Id);
	// Print linking errors if any
	CheckCompileErrors(Id, "PROGRAM");

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::Use()
{
	glUseProgram(Id);
}
/*
void Shader::SetBool(const std::string& _name, bool _value) const
{
	glUniform1i(glGetUniformLocation(Id, _name.c_str()), (int)_value);
}

void Shader::SetInt(const std::string& _name, int _value) const
{
	glUniform1i(glGetUniformLocation(Id, _name.c_str()), _value);
}

void Shader::SetFloat(const std::string& _name, float _value) const
{
	glUniform1f(glGetUniformLocation(Id, _name.c_str()), _value);
}

void Shader::SetFloat2(const std::string& _name, const float2& _value) const
{
	glUniform2fv(glGetUniformLocation(Id, _name.c_str()), 1, &_value.x);
}

void Shader::SetFloat2(const std::string& _name, float _x, float _y) const
{
	glUniform2f(glGetUniformLocation(Id, _name.c_str()), _x, _y);
}

void Shader::SetFloat3(const std::string& _name, const float3& _value) const
{
	glUniform3fv(glGetUniformLocation(Id, _name.c_str()), 1, &_value.x);
}

void Shader::SetFloat3(const std::string& _name, float _x, float _y, float _z) const
{
	glUniform3f(glGetUniformLocation(Id, _name.c_str()), _x, _y, _z);
}

void Shader::SetFloat4(const std::string& _name, const float4& _value) const
{
	glUniform4fv(glGetUniformLocation(Id, _name.c_str()), 1, &_value.x);
}

void Shader::SetFloat4(const std::string& _name, float _x, float _y, float _z, float _w) const
{
	glUniform4f(glGetUniformLocation(Id, _name.c_str()), _x, _y, _z, _w);
}

void Shader::SetMatrix2(const std::string& _name, const matrix2& _matrix) const
{
	glUniformMatrix2fv(glGetUniformLocation(Id, _name.c_str()), 1, GL_TRUE, &_matrix.data[0][0]);
}

void Shader::SetMatrix3(const std::string& _name, const matrix3& _matrix) const
{
	glUniformMatrix3fv(glGetUniformLocation(Id, _name.c_str()), 1, GL_TRUE, &_matrix.data[0][0]);
}

void Shader::SetMatrix4(const std::string& _name, const matrix4& _matrix) const
{
	glUniformMatrix4fv(glGetUniformLocation(Id, _name.c_str()), 1, GL_TRUE, &_matrix.data[0][0]);
}*/