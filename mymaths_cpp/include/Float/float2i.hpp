#pragma once

#include <iostream>

class matrix2;

class float2i
{
public:
	float2i();
	~float2i();
	float2i(int x, int y);
	float2i(float2i a, float2i b);

	int x;
	int y;

	//functions
	void print() const;
	void print(std::string name) const;


	// vector related
	float2i normalize() const;
	float length() const;
	float lengthSq() const;	// only used to compare for optimization
	float dist(float2i a, float2i b) const;
	float2i rotate(float angle) const;
	static float dot(float2i a, float2i b);
	float2i scaleMatrix2(float sx, float sy) const;

	// point related
	static float2i isobaryCenterTriangle(float2i a, float2i b, float2i c);
	static float2i circumcenterTriangle(float2i a, float2i b, float2i c);
};

// operators
float2i operator+(float2i a, float b);
float2i operator-(float2i a, float b);
float2i operator*(float2i a, float b);
float2i operator/(float2i a, float b);
float2i operator+(float2i a, float2i b);
float2i operator-(float2i a, float2i b);
float2i operator*(float2i a, float2i b);
float2i operator*(matrix2 a, float2i b);

std::ostream& operator<<(std::ostream& os, const float2i& float2i);
