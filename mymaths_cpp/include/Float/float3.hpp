#pragma once

#include <iostream>

class matrix3;

class float3
{
public:
	float3();
	~float3();
	float3(float _x, float _y, float _z);
	float3(float3 a, float3 b);

	float x;
	float y;
	float z;

	//functions
	void print() const;
	void print(std::string name) const;


	// vector related
	float3 normalize() const;
	float length() const;
	float lengthSq() const;	// only used to compare for optimization
	float dist(float3 a, float3 b) const;
	float3 rotate(float XangleRad, float YangleRad, float ZangleRad) const;
	static float dot(float3 a, float3 b);
	static float3 cross(float3 a, float3 b);
	float3 scaleMatrix3(float sx, float sy, float sz) const;

	// point related
	static float3 isobaryCenterTriangle(float3 a, float3 b, float3 c);
	static float3 circumcenterTriangle(float3 a, float3 b, float3 c);
};

// operators

float3 operator+(float3 a, float b);
float3 operator-(float3 a, float b);
float3 operator*(float3 a, float b);
float3 operator/(float3 a, float b);
float3 operator+(float3 a, float3 b);
float3 operator-(float3 a, float3 b);
float3 operator*(float3 a, float3 b);
float3 operator*(matrix3 a, float3 b);

std::ostream& operator<<(std::ostream& os, const float3& float3);
