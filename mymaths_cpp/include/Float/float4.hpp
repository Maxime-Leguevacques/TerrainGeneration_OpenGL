#pragma once

#include <iostream>

class matrix4;

class float4
{
public:
	// Constructors
	float4();
	~float4();
	float4(float x, float y, float z, float w);
	float4(float4 a, float4 b);
	float4(float number);

	// Variables
	float x, y, z, w;

	// Functions
	void print() const;
	void print(std::string name) const;

	// vector related
	float4 normalize() const;
	float length() const;
	float lengthSq() const;	// only used to compare for optimization
	float dist(float4 a, float4 b) const;
	static float dot(float4 a, float4 b);
	static float4 cross(float4 a, float4 b);
};

// operators

float4 operator+(float4 a, float b);
float4 operator-(float4 a, float b);
float4 operator*(float4 a, float b);
float4 operator/(float4 a, float b);
float4 operator+(float4 a, float4 b);
float4 operator-(float4 a, float4 b);
float4 operator*(float4 a, float4 b);
float4 operator*(matrix4 a, float4 b);

std::ostream& operator<<(std::ostream& os, const float4& float4);
