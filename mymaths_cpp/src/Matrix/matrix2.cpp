#include "Matrix/matrix2.hpp"

#include "Float/float2.hpp"

#include <iomanip>



matrix2::matrix2()
{
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			data[i][j] = 0;
}

matrix2::~matrix2() { }

matrix2::matrix2(
	float a, float b, 
	float c, float d
)
{
	data[0][0] = a;
	data[0][1] = b;
	data[1][0] = c;
	data[1][1] = d;
}

void matrix2::print() const
{
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++)
			std::cout << data[i][j] << std::setw(4);
		std::cout << "\n";
	}
	std::cout << "\n";
}

matrix2 matrix2::Transpose()
{
	matrix2 Transpose;

	for (int i = 0; i < 2; i++) {
		// assign float2 as new column of matrix
		float temp[2];
		for (int j = 0; j < 2; j++) {
			temp[j] = data[i][j];
		}
		// set the temp float2 to the correct lign of the tranposed matrix
		for (int k = 0; k < 2; k++) {
			Transpose.data[k][i] = temp[k];
		}
	}
	return Transpose;
}

float2 matrix2::Diagonal()
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
	float2 diagonal(temp[0], temp[1]);
	return diagonal;
}

float matrix2::Trace()
{
	float2 temp = this->Diagonal();
	float trace = temp.x + temp.y;
	return trace;
}

float matrix2::Determinant()
{
	float result =
		data[0][0] * data[1][1] -
		data[1][0] * data[0][1];
	return result;
}

matrix2 matrix2::Rotate(float angleRad)
{
	matrix2 temp(
		cos(angleRad), sin(angleRad),
		-sin(angleRad), cos(angleRad)
	);
	return temp;
}



#pragma region Operators

matrix2 operator+(matrix2 A, float n)
{
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			A.data[i][j] += n;
	return A;
}

matrix2 operator-(matrix2 A, float n)
{
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			A.data[i][j] -= n;
	return A;
}

matrix2 operator*(matrix2 A, float n)
{
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			A.data[i][j] *= n;
	return A;
}

matrix2 operator/(matrix2 A, float s)
{
	return A * (1.0f / s);
}

matrix2 operator+(matrix2 A, matrix2 B)
{
	matrix2 temp;
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			temp.data[i][j] = A.data[i][j] + B.data[i][j];
	return temp;
}

matrix2 operator-(matrix2 A, matrix2 B)
{
	matrix2 temp;
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			temp.data[i][j] = A.data[i][j] - B.data[i][j];
	return temp;
}

matrix2 operator*(matrix2 A, matrix2 B)
{
	matrix2 temp;

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			for (int k = 0; k < 2; k++)
				temp.data[i][j] += A.data[i][k] * B.data[k][j];
	return temp;
}


std::ostream& operator<<(std::ostream& os, const matrix2& _matrix2)
{
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++)
			os << _matrix2.data[i][j] << " ";
		os << "\n";
	}
	return os;
}

#pragma endregion Operators