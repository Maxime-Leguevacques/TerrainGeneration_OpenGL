#pragma once

#include <iostream>



class complex
{
public:
	complex();
	~complex();

	complex(float a, float ib);		// a : real, ib : imaginary

	float a;
	float ib;
	float module;
	float teta;

	// Functions
	static float Module(complex z);
	void GetData();
};

// operators

complex operator+(complex z, float a);
complex operator-(complex z, float a);
complex operator*(complex z, float a);
complex operator/(complex z, float a);
complex operator+(complex z1, complex z2);
complex operator-(complex z1, complex z2);
complex operator*(complex z1, complex z2);
complex operator/(complex z1, complex z2);
