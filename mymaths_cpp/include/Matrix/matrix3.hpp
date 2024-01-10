#pragma once

#include <iostream>
#include <vector>

#include "Float/float3.hpp"


class matrix3
{
public:
	// Constructors
	matrix3();
	~matrix3();
	matrix3(
		float a, float b, float c,
		float d, float e, float f,
		float g, float h, float i
	);

	// Variables
	float data[3][3];

	// Functions
	void print() const;

	matrix3 Transpose();
	float3 Diagonal();
	float Trace();
	float Determinant();
	static matrix3 RotateX(float angleRad);
	static matrix3 RotateY(float angleRad);
	static matrix3 RotateZ(float angleRad);
};

matrix3 operator+(matrix3 A, float n);
matrix3 operator-(matrix3 A, float n);
matrix3 operator*(matrix3 A, float s);
matrix3 operator/(matrix3 A, float s);
matrix3 operator+(matrix3 A, matrix3 B);
matrix3 operator-(matrix3 A, matrix3 B);
matrix3 operator*(matrix3 A, matrix3 B);

std::ostream& operator<<(std::ostream& os, const matrix3& _matrix3);
