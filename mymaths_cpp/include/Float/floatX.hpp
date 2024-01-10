#pragma once

#include <iostream>
#include <vector>

class floatX
{
public:
	floatX();
	~floatX();
	floatX(int fsize);


	//variables 
	int size;		// size of the vector (mathematical vector)

	std::vector<float> float_X;

	// functions
	void print() const;
	void print(std::string name) const;

	// vector related functions
	static floatX normalize(floatX a);
	static float length(floatX a);
	static float lengthSq(floatX a);	// only used to compare for optimization
	static float dist(floatX a, floatX b);
	static float dot(floatX a, floatX b);
	static floatX cross(floatX a, floatX b);
};

floatX operator+(floatX a, float n);
floatX operator-(floatX a, float n);
floatX operator*(floatX a, float s);
floatX operator/(floatX a, float s);
floatX operator+(floatX a, floatX b);
floatX operator-(floatX a, floatX b);

std::ostream& operator<<(std::ostream& os, const floatX& floatX);
