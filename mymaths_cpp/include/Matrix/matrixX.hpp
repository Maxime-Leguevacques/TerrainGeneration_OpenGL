#pragma once

#include <iostream>
#include <vector>

#include "Float/float2.hpp"
#include "Float/float3.hpp"
#include "Float/floatX.hpp"

class matrixX
{
public:
	// constructors
	matrixX();
	~matrixX();
	matrixX(int row, int col);
	matrixX(int size);


	// variables
	int rows;
	int columns;

	std::vector<float> mat;


	// functions
	void print() const;
	void print(std::string name) const;

	static bool checkIfSameSize(const matrixX& A, const matrixX& B);
	static bool checkIfMultiplyOk(const matrixX& A, const matrixX& B);
	bool checkIfDiagonal();

	matrixX transpose();
	floatX getDiagonal();
	float trace();
	float det2();
	float det3();
	matrixX GaussJordan();

	// TRS
	static matrixX GetTranslationMatrix(float3 position);
	static matrixX GetRotationMatrix(float3 anglesRad);
	static matrixX GetScaleMatrix(float3 scale);
	static matrixX Get_TRS_Matrix(float3 position, float3 rotaionAngle, float3 scale);
};

matrixX operator+(matrixX A, float n);
matrixX operator-(matrixX A, float n);
matrixX operator*(matrixX A, float s);
matrixX operator/(matrixX A, float s);
matrixX operator+(matrixX A, matrixX B);
matrixX operator-(matrixX A, matrixX B);
matrixX operator*(matrixX A, matrixX B);

std::ostream& operator<<(std::ostream& os, const matrixX& matrixX);


