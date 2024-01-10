#include "Float/float4.hpp"
#include "Matrix/matrix4.hpp"


float4::float4() 
{
	x = y = z = w = 0;
}

float4::~float4() { }

float4::float4(float _x, float _y, float _z, float _w)
{
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

float4::float4(float4 a, float4 b)
{
	x = b.x - a.x;
	y = b.y - a.y;
	z = b.z - a.z;
	w = b.w - a.w;
}

float4::float4(float number)
{
	x = y = z = w = number;
}


void float4::print() const
{
	std::cout << "{ " << x << " ; " << y << " ; " << z << " ; " << w << " }\n";
}



#pragma region Operators

float4 operator+(float4 a, float b)
{
	return { a.x + b, a.y + b, a.z + b, a.w + b };
}

float4 operator-(float4 a, float b)
{
	return { a.x - b, a.y - b, a.z - b, a.w - b };
}

float4 operator*(float4 a, float s)
{
	return { a.x * s, a.y * s, a.z * s, a.w * s };
}

float4 operator/(float4 a, float s)
{
	return { a.x / s, a.y / s, a.z / s, a.w / s };
}

float4 operator+(float4 a, float4 b)
{
	return { a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w };
}

float4 operator-(float4 a, float4 b)
{
	return { a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w };
}

float4 operator*(float4 a, float4 b)
{
	return { a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w };
}

float4 operator*(matrix4 a, float4 b)
{
	return {
		a.data[0][0] * b.x + a.data[0][1] * b.y + a.data[0][2] * b.z + a.data[0][3] * b.w,
		a.data[1][0] * b.x + a.data[1][1] * b.y + a.data[1][2] * b.z + a.data[1][3] * b.w,
		a.data[2][0] * b.x + a.data[2][1] * b.y + a.data[2][2] * b.z + a.data[2][3] * b.w,
		a.data[3][0] * b.x + a.data[3][1] * b.y + a.data[3][2] * b.z + a.data[3][3] * b.w
	};
}


std::ostream& operator<<(std::ostream& os, const float4& f)
{
	return os << "{ " << f.x << " ; " << f.y << " ; " << f.z <<  " ; " << f.w << " }";
}

#pragma endregion Operators