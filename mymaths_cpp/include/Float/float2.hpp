#pragma once

#include <iostream>

class matrix2;

class float2
{
public:
	float2();
	~float2();
	float2(float _x, float _y);
	float2(float2 a, float2 b);

	float x;
	float y;

	//functions
	void print() const;
	void print(std::string name) const;


	// vector related
	float2 normalize() const;
	float length() const;
	float lengthSq() const;	// only used to compare for optimization
	float dist(float2 a, float2 b) const;
	float2 rotate(float angle) const;
	static float dot(float2 a, float2 b);
	float2 scaleMatrix2(float sx, float sy) const ;

	// point related
	static float2 isobaryCenterTriangle(float2 a, float2 b, float2 c);
	static float2 circumcenterTriangle(float2 a, float2 b, float2 c);
};

// operators
float2 operator+(float2 a, float b);
float2 operator-(float2 a, float b);
float2 operator*(float2 a, float b);
float2 operator/(float2 a, float b);
float2 operator+(float2 a, float2 b);
float2 operator-(float2 a, float2 b);
float2 operator*(matrix2 a, float2 b);

std::ostream& operator<<(std::ostream& os, const float2& float2);
