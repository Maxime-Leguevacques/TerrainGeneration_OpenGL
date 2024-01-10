#include "Matrix/matrix3.hpp"

#include "Float/float3.hpp"

#include <iomanip>


matrix3::matrix3()
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			data[i][j] = 0;
}

matrix3::~matrix3() { }

matrix3::matrix3(
	float a, float b, float c,
	float d, float e, float f,
	float g, float h, float i
)
{
	data[0][0] = a;
	data[0][1] = b;
	data[0][2] = c;
	data[1][0] = d;
	data[1][1] = e;
	data[1][2] = f;
	data[2][0] = g;
	data[2][1] = h;
	data[2][2] = i;
}


void matrix3::print() const
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
			std::cout << data[i][j] << std::setw(6);
		std::cout << "\n";
	}
	std::cout << "\n";
}

matrix3 matrix3::Transpose()
{
	matrix3 Transpose;

	for (int i = 0; i < 3; i++) {
		// assign float3 as new column of matrix
		float temp[3];
		for (int j = 0; j < 3; j++) {
			temp[j] = data[i][j];
		}
		// set the temp float3 to the correct lign of the tranposed matrix
		for (int k = 0; k < 3; k++) {
			Transpose.data[k][i] = temp[k];
		}
	}
	return Transpose;
}

float3 matrix3::Diagonal()
{
	float temp[3];
	int k = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (i == j) {
				temp[k] = data[i][j];
				k++;
			}
		}
	}
	float3 diagonal(temp[0], temp[1], temp[2]);
	return diagonal;
}

float matrix3::Trace()
{
	float3 temp = this->Diagonal();
	float trace = temp.x + temp.y + temp.z;
	return trace;
}

float matrix3::Determinant()
{
	float result =
		data[0][0] * (data[1][1] * data[2][2] - data[2][1] * data[1][2]) -
		data[0][1] * (data[1][0] * data[2][2] - data[2][0] * data[1][2]) +
		data[0][2] * (data[1][0] * data[2][1] - data[2][0] * data[1][1]);
	return result;
}

matrix3 matrix3::RotateX(float angleRad)
{
	matrix3 temp(
		1, 0, 0,
		0, cos(angleRad), -sin(angleRad),
		0, sin(angleRad), cos(angleRad)
	);
	return temp;
}

matrix3 matrix3::RotateY(float angleRad)
{
	matrix3 temp(
		cos(angleRad), 0, sin(angleRad),
		0, 1, 0,
		-sin(angleRad), 0, cos(angleRad)
	);
	return temp;
}

matrix3 matrix3::RotateZ(float angleRad)
{
	matrix3 temp(
		cos(angleRad), -sin(angleRad), 0,
		-sin(angleRad), cos(angleRad), 0,
		0, 0, 1
	);
	return temp;
}



#pragma region Operators

matrix3 operator+(matrix3 A, float n)
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			A.data[i][j] += n;
	return A;
}

matrix3 operator-(matrix3 A, float n)
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			A.data[i][j] -= n;
	return A;
}

matrix3 operator*(matrix3 A, float n)
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			A.data[i][j] *= n;
	return A;
}

matrix3 operator/(matrix3 A, float s)
{
	return A * (1.0f / s);
}

matrix3 operator+(matrix3 A, matrix3 B)
{
	matrix3 temp;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			temp.data[i][j] = A.data[i][j] + B.data[i][j];
	return temp;
}

matrix3 operator-(matrix3 A, matrix3 B)
{
	matrix3 temp;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			temp.data[i][j] = A.data[i][j] - B.data[i][j];
	return temp;
}

matrix3 operator*(matrix3 A, matrix3 B)
{
	matrix3 temp;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
				temp.data[i][j] += A.data[i][k] * B.data[k][j];
	return temp;
}


std::ostream& operator<<(std::ostream& os, const matrix3& _matrix3)
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
			os << _matrix3.data[i][j] << " ";
		os << "\n";
	}
	return os;
}

#pragma endregion Operators