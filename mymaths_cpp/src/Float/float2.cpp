
#include "Float/float2.hpp"
#include "Matrix/matrix2.hpp"



float2::float2()
{
	x = y = 0;
}

float2::~float2()
{

}

float2::float2(float _x, float _y)
{
	x = _x;
	y = _y;
}

float2::float2(float2 a, float2 b)
{
	x = b.x - a.x;
	y = b.y - a.y;
}


void float2::print() const
{
	std::cout << "{ " << this->x << " ; " << this->y << " }\n";
}

void float2::print(std::string name) const
{
	std::cout << std::string(name) << " : { " << this->x << " ; " << this->y << " }\n";
}


float2 float2::normalize() const
{
	float2 temp = { x, y };
	float l = temp.length();
	return float2(x / l, y / l);	// temp / l
}

float float2::length() const
{
	return sqrtf(x * x + y * y);
}

float float2::lengthSq() const
{
	return (x * x) + (y * y);
}

float float2::dist(float2 a, float2 b) const
{
	return (b - a).length();
}

/* rotate vector with angle in radians */
float2 float2::rotate(float angle) const
{
	//matrix2 r(2);
	//r.mat = { cosf(angle), -sinf(angle), sinf(angle), cosf(angle) };
	matrix2 r = matrix2::Rotate(angle);
	float2 vec = { x, y };
	float2 temp = r * vec;
	return temp;
}

float float2::dot(float2 a, float2 b)
{
	return a.x * b.x + a.y * b.y;
}

float2 float2::scaleMatrix2(float sx, float sy) const
{
	matrix2 scaleMat2(
		sx, 0,
		0, sy
	);
	float2 vec = { x, y };
	float2 temp = scaleMat2 * vec;
	return temp;
}

/* returns center gravity point of triangle abc */
float2 float2::isobaryCenterTriangle(float2 a, float2 b, float2 c)
{
	float Xi = (1.f / 3.f) * (a.x + b.x + c.x);
	float Yi = (1.f / 3.f) * (a.y + b.y + c.y);
	return { Xi, Yi };
}

/* returns center point of circle going through all corners of triangle abc*/
float2 float2::circumcenterTriangle(float2 a, float2 b, float2 c)
{
	float D = 2.f * ( (a.x * (b.y - c.y)) + (b.x * (c.y - a.y)) + (c.x * (a.y - b.y)) );

	float x = 1.f / D * (
		(a.x * a.x + (a.y * a.y)) * (b.y - c.y) +
		(b.x * b.x + (b.y * b.y)) * (c.y - a.y) +
		(c.x * c.x + (c.y * c.y)) * (a.y - b.y)
		);
	float y = 1.f / D * (
		(a.x * a.x + (a.y * a.y)) * (c.x - b.x) +
		(b.x * b.x + (b.y * b.y)) * (a.x - c.x) +
		(c.x * c.x + (c.y * c.y)) * (b.x - a.x)
		);
	return { x, y };
}


#pragma region Operators

float2 operator+(float2 a, float b)
{
	return { a.x + b, a.y + b };
}

float2 operator-(float2 a, float b)
{
	return { a.x - b, a.y - b };
}

float2 operator*(float2 a, float s)
{
	return { a.x * s, a.y * s };
}

float2 operator/(float2 a, float s)
{
	return { a.x / s, a.y / s };
}

float2 operator+(float2 a, float2 b)
{
	return { a.x + b.x, a.y + b.y };
}

float2 operator-(float2 a, float2 b)
{
	return { a.x - b.x, a.y - b.y };
}

float2 operator*(float2 a, float2 b)
{
	return { a.x * b.x, a.y * b.y };
}

float2 operator*(matrix2 a, float2 b)
{
	return {
		a.data[0][0] * b.x + a.data[0][1] * b.y,
		a.data[1][0] * b.x + a.data[1][1] * b.y
	};
}


std::ostream& operator<<(std::ostream& os, const float2& f)
{
	return os << "{ " << f.x << " ; " << f.y << " }";
}

#pragma endregion Operators
