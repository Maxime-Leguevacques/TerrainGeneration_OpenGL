#define _USE_MATH_DEFINES

#include "Matrix/matrix4.hpp"

#include "Float/float3.hpp"
#include "Float/float4.hpp"
#include "Matrix/matrix3.hpp"
#include "formulas.hpp"

#include <iomanip>


matrix4::matrix4()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			data[i][j] = 0;
}

matrix4::~matrix4() { }

matrix4::matrix4(
	float a, float b, float c, float d,
	float e, float f, float g, float h,
	float i, float j, float k, float l,
	float m, float n, float o, float p
)
{
	data[0][0] = a;data[0][1] = b;data[0][2] = c;data[0][3] = d;
	data[1][0] = e;data[1][1] = f;data[1][2] = g;data[1][3] = h;
	data[2][0] = i;data[2][1] = j;data[2][2] = k;data[2][3] = l;
	data[3][0] = m;data[3][1] = n;data[3][2] = o;data[3][3] = p;
}

matrix4::matrix4(float value)
{
	data[0][0] = value; data[0][1] = 0;		data[0][2] = 0;		data[0][3] = 0;
	data[1][0] = 0;		data[1][1] = value; data[1][2] = 0;		data[1][3] = 0;
	data[2][0] = 0;		data[2][1] = 0;		data[2][2] = value; data[2][3] = 0;
	data[3][0] = 0;		data[3][1] = 0;		data[3][2] = 0;		data[3][3] = value;

	elements[0] = data[0][0]; elements[1] = data[0][1]; elements[2] = data[0][2]; elements[3] = data[0][3];
	elements[4] = data[1][0];elements[5] = data[1][1];elements[6] = data[1][2];elements[7] = data[1][3];
	elements[8] = data[2][0];elements[9] = data[2][1];elements[10] = data[2][2];elements[11] = data[2][3];
	elements[12] = data[3][0];elements[13] = data[3][1];elements[14] = data[3][2];elements[15] = data[3][3];
}

void matrix4::print() const
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			std::cout << data[i][j] << std::setw(6);
		std::cout << "\n";
	}
	std::cout << "\n";
}

matrix4 matrix4::Transpose()
{
	matrix4 Transpose;

	for (int i = 0; i < 4; i++) {
		// assign float4 as new column of matrix
		float temp[4];
		for (int j = 0; j < 4; j++) {
			temp[j] = data[i][j];
		}
		// set the temp float4 to the correct lign of the tranposed matrix
		for (int k = 0; k < 4; k++) {
			Transpose.data[k][i] = temp[k];
		}
	}
	return Transpose;
}

float4 matrix4::Diagonal()
{
	float temp[4];
	int k = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j) {
				temp[k] = data[i][j];
				k++;
			}
		}
	}
	float4 diagonal(temp[0], temp[1], temp[2], temp[3]);
	return diagonal;
}

float matrix4::Trace()
{
	float4 temp = this->Diagonal();
	float trace = temp.x + temp.y + temp.z + temp.w;
	return trace;
}

float matrix4::Determinant()
{
	float result = 0;

	matrix3 mat1(
		data[1][1], data[1][2], data[1][3],
		data[2][1], data[2][2], data[2][3],
		data[3][1], data[3][2], data[3][3]
	);

	matrix3 mat2(
		data[1][0], data[1][2], data[1][3],
		data[2][0], data[2][2], data[2][3],
		data[3][0], data[3][2], data[3][3]
	);

	matrix3 mat3(
		data[1][0], data[1][1], data[1][3],
		data[2][0], data[2][1], data[2][3],
		data[3][0], data[3][1], data[3][3]
	);

	matrix3 mat4(
		data[1][0], data[1][1], data[1][2],
		data[2][0], data[2][1], data[2][2],
		data[3][0], data[3][1], data[3][2]
	);

	result = data[0][0] * mat1.Determinant() + data[0][1] * mat2.Determinant() + data[0][2] * mat3.Determinant() + data[0][3] * mat4.Determinant();

	return result;
}

matrix4 matrix4::Translate(float3 t)
{
	matrix4 translate(
		1, 0, 0, t.x,
		0, 1, 0, t.y,
		0, 0, 1, t.z,
		0, 0, 0, 1
	);

	translate.Inverse();

	Inverse();

	return (*this) * translate;
}

matrix4 matrix4::Translate(matrix4 _mat4, float3 t)
{
	matrix4 translate(
		1, 0, 0, t.x,
		0, 1, 0, t.y,
		0, 0, 1, t.z,
		0, 0, 0, 1
	);

	translate.Inverse();

	_mat4.Inverse();

	return _mat4 * translate;
}

void matrix4::Inverse()
{
	matrix4 temp;

	temp.data[0][0] = data[0][0];	temp.data[0][1] = data[1][0];	temp.data[0][2] = data[2][0];	temp.data[0][3] = data[3][0];

	temp.data[1][0] = data[0][1];	temp.data[1][1] = data[1][1];	temp.data[1][2] = data[2][1];	temp.data[1][3] = data[3][1];

	temp.data[2][0] = data[0][2];	temp.data[2][1] = data[1][2];	temp.data[2][2] = data[2][2];	temp.data[2][3] = data[3][2];

	temp.data[3][0] = data[0][3];	temp.data[3][1] = data[1][3];	temp.data[3][2] = data[2][3];	temp.data[3][3] = data[3][3];
	
	*this = temp;
}

matrix4 matrix4::Rotate(float3 XYZrad)
{
	matrix4 rotateX(
		1, 0, 0, 0,
		0, cos(XYZrad.x), -sin(XYZrad.x), 0,
		0, sin(XYZrad.x), cos(XYZrad.x), 0,
		0, 0, 0, 1
	);
	matrix4 rotateY(
		cos(XYZrad.y), 0, sin(XYZrad.y), 0,
		0, 1, 0, 0,
		-sin(XYZrad.y), 0, cos(XYZrad.y), 0,
		0, 0, 0, 1
	);
	matrix4 rotateZ(
		cos(XYZrad.z), -sin(XYZrad.z), 0, 0,
		sin(XYZrad.z), cos(XYZrad.z), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);
	matrix4 rotate = rotateX * rotateY * rotateZ;
	return (*this) * rotate;
}


matrix4 matrix4::Scale(float3 s)
{
	matrix4 scale(
		s.x, 0, 0, 0,
		0, s.y, 0, 0,
		0, 0, s.z, 0,
		0, 0, 0, 1
	);
	return (*this) * scale;
}

matrix4 matrix4::TRS(float3 translate, float3 rotate, float3 scale)
{
	return Translate(translate) * Rotate(rotate) * Scale(scale);
}

matrix4 matrix4::Projection(float fov, float aspectRatio, float zNear, float zFar)
{
	float f = std::tan(fov / 2.0f);
	float matData00 = 1 / (f * aspectRatio);
	float matData22 = (-zNear - zFar) / (zNear - zFar);
	float matData23 = (2 * zFar * zNear) / (zNear - zFar);

	matrix4 temp(
		matData00, 0, 0, 0,
		0, 1 / f, 0, 0,
		0, 0, matData22, matData23,
		0, 0, 1, 0
	);
	return temp;
}

matrix4 matrix4::LookAt(float3 cameraPos, float3 targetPos, float3 up)
{
	float3 Up = up.normalize();

	float3 Z = (cameraPos - targetPos).normalize();
	float3 X = float3::cross(Up, Z).normalize();
	float3 Y = float3::cross(Z, X);

	matrix4 temp(
		X.x, X.y, X.z, 0,
		Y.x, Y.y, Y.z, 0,
		Z.x, Z.y, Z.z, 0,
		0, 0, 0, 1
	);
	temp = temp.Translate(cameraPos * -1);

	return temp;


	return temp;
}



#pragma region Operators

matrix4 operator+(matrix4 A, float n)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			A.data[i][j] += n;
	return A;
}

matrix4 operator-(matrix4 A, float n)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			A.data[i][j] -= n;
	return A;
}

matrix4 operator*(matrix4 A, float n)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			A.data[i][j] *= n;
	return A;
}

matrix4 operator/(matrix4 A, float s)
{
	return A * (1.0f / s);
}

matrix4 operator+(matrix4 A, matrix4 B)
{
	matrix4 temp;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			temp.data[i][j] = A.data[i][j] + B.data[i][j];
	return temp;
}

matrix4 operator-(matrix4 A, matrix4 B)
{
	matrix4 temp;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			temp.data[i][j] = A.data[i][j] - B.data[i][j];
	return temp;
}

matrix4 operator*(matrix4 A, matrix4 B)
{
	matrix4 temp;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			for (int k = 0; k < 4; k++)
				temp.data[i][j] += A.data[i][k] * B.data[k][j];
	return temp;
}


std::ostream& operator<<(std::ostream& os, const matrix4& _matrix4)
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			os << _matrix4.data[i][j] << " ";
		os << "\n";
	}
	return os;
}

#pragma endregion Operators