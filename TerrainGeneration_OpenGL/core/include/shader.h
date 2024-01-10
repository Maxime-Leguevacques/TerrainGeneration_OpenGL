#pragma once

#include <iostream>
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "mymaths.hpp"


class Shader
{
private:
	void CheckCompileErrors(unsigned int _shader, std::string _type);

public:
	// Contructors
	Shader(const char* _vertexPath, const char* _fragmentPath);

	// Functions
	void Use();			// activate shader
	void SetBool(const std::string& _name, bool _value) const;
	void SetInt(const std::string& _name, int _value) const;

	void SetFloat(const std::string& _name, float _value) const;
	void SetFloat2(const std::string& _name, const float2& _value) const;
	void SetFloat2(const std::string& _name, float _x, float _y) const;
	void SetFloat3(const std::string& _name, const float3& _value) const;
	void SetFloat3(const std::string& _name, float _x, float _y, float _z) const;
	void SetFloat4(const std::string& _name, const float4& _value) const;
	void SetFloat4(const std::string& _name, float _x, float _y, float _z, float _w) const;

	void SetMatrix2(const std::string& _name, const matrix2& _matrix) const;
	void SetMatrix3(const std::string& _name, const matrix3& _matrix) const;
	void SetMatrix4(const std::string& _name, const matrix4& _matrix) const;

	// Variables
	unsigned int Id;
};