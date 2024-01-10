#pragma once

#include <iostream>
#include <vector>

#include "Float/float2.hpp"



class matrix2 
{
public:
	// Constructors
	matrix2();
	~matrix2();
	matrix2(
		float a, float b,
		float c, float d
	);

	// Variables
	float data[2][2];

	// Functions
	void print() const;

	matrix2 Transpose();
	float2 Diagonal();
	float Trace();
	float Determinant();
	static matrix2 Rotate(float angle);
	//matrix2 GaussJordan();
};

matrix2 operator+(matrix2 A, float n);
matrix2 operator-(matrix2 A, float n);
matrix2 operator*(matrix2 A, float s);
matrix2 operator/(matrix2 A, float s);
float2 operator*(matrix2 a, float2 b);
matrix2 operator+(matrix2 A, matrix2 B);
matrix2 operator-(matrix2 A, matrix2 B);
matrix2 operator*(matrix2 A, matrix2 B);

std::ostream& operator<<(std::ostream& os, const matrix2& _matrix2);
