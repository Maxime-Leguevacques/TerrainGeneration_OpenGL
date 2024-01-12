#pragma once

#include <iostream>
#include <vector>

#include "Float/float3.hpp"
#include "Float/float4.hpp"


class matrix4
{
public:
	// Constructors
	matrix4();
	~matrix4();
	matrix4(
		float a, float b, float c, float d,
		float e, float f, float g, float h,
		float i, float j, float k, float l,
		float m, float n, float o, float p
	);

	matrix4(float value);

	// Variables
	float data[4][4];
	float elements[16];

	// Functions
	void print() const;

	matrix4 Transpose();
	float4 Diagonal();
	float Trace();
	float Determinant();
	void Inverse();

	// rotation?
	matrix4 Translate(float3 t);
	static matrix4 Translate(matrix4 _mat4, float3 t);


	matrix4 Rotate(float3 XYZrad);
	static matrix4 Rotate(matrix4 _mat4, float angle, float3 v);

	matrix4 Scale(float3 s);
	matrix4 TRS(float3 translate, float3 rotate, float3 scale);
	static matrix4 Projection(float fov, float aspectRatio, float zNear, float zFar);
	static matrix4 LookAt(float3 cameraPos, float3 targetPos, float3 up);
};

matrix4 operator+(matrix4 A, float n);
matrix4 operator-(matrix4 A, float n);
matrix4 operator*(matrix4 A, float s);
matrix4 operator/(matrix4 A, float s);
matrix4 operator+(matrix4 A, matrix4 B);
matrix4 operator-(matrix4 A, matrix4 B);
matrix4 operator*(matrix4 A, matrix4 B);

std::ostream& operator<<(std::ostream& os, const matrix4& _matrix4);