
#include "Float/float2i.hpp"
#include "Matrix/matrix2.hpp"



float2i::float2i()
{

}

float2i::~float2i()
{

}

float2i::float2i(int a, int b)
{
	x = a;
	y = b;
}

float2i::float2i(float2i _a, float2i _b)
{
	x = _b.x - _a.x;
	y = _b.y - _a.y;
}


void float2i::print() const
{
	std::cout << "{ " << this->x << " ; " << this->y << " }\n";
}

void float2i::print(std::string _name) const
{
	std::cout << std::string(_name) << " : { " << this->x << " ; " << this->y << " }\n";
}


float2i float2i::normalize() const
{
	float2i temp = { x, y };
	float l = temp.length();
	return float2i((int)(x / l), (int)(y / l));	// temp / l
}

float float2i::length() const
{
	return sqrtf(x * x + y * y);
}

float float2i::lengthSq() const
{
	return (x * x) + (y * y);
}

float float2i::dist(float2i _a, float2i _b) const
{
	return (_b - _a).length();
}

/* rotate vector with angle in radians */
float2i float2i::rotate(float _angle) const
{
	//matrix2 r(2);
	//r.mat = { cosf(_angle), -sinf(_angle), sinf(_angle), cosf(_angle) };
	matrix2 r = matrix2::Rotate(_angle);
	float2i vec = { x, y };
	float2i temp = r * vec;
	return temp;
}

float float2i::dot(float2i _a, float2i _b)
{
	return _a.x * _b.x + _a.y * _b.y;
}

float2i float2i::scaleMatrix2(float _sx, float _sy) const
{
	matrix2 scaleMat2(
		_sx, 0,
		0, _sy
	);
	float2i vec = { x, y };
	float2i temp = scaleMat2 * vec;
	return temp;
}

/* returns center gravity point of triangle abc */
float2i float2i::isobaryCenterTriangle(float2i _a, float2i _b, float2i _c)
{
	float Xi = (1.f / 3.f) * (_a.x + _b.x + _c.x);
	float Yi = (1.f / 3.f) * (_a.y + _b.y + _c.y);
	return { (int)Xi, (int)Yi };
}

/* returns center point of circle going through all corners of triangle abc*/
float2i float2i::circumcenterTriangle(float2i _a, float2i _b, float2i _c)
{
	float D = 2.f * ((_a.x * (_b.y - _c.y)) + (_b.x * (_c.y - _a.y)) + (_c.x * (_a.y - _b.y)));

	float x = 1.f / D * (
		(_a.x * _a.x + (_a.y * _a.y)) * (_b.y - _c.y) +
		(_b.x * _b.x + (_b.y * _b.y)) * (_c.y - _a.y) +
		(_c.x * _c.x + (_c.y * _c.y)) * (_a.y - _b.y)
		);
	float y = 1.f / D * (
		(_a.x * _a.x + (_a.y * _a.y)) * (_c.x - _b.x) +
		(_b.x * _b.x + (_b.y * _b.y)) * (_a.x - _c.x) +
		(_c.x * _c.x + (_c.y * _c.y)) * (_b.x - _a.x)
		);
	return { (int)x, (int)y };
}


// Operators

float2i operator+(float2i _a, float _b)
{
	return { (int)(_a.x + _b), (int)(_a.y + _b) };
}

float2i operator-(float2i _a, float _b)
{
	return { (int)(_a.x - _b), (int)(_a.y - _b) };
}

float2i operator*(float2i _a, float _s)
{
	return { (int)(_a.x * _s), (int)(_a.y * _s) };
}

float2i operator/(float2i _a, float _s)
{
	return { (int)(_a.x / _s), (int)(_a.y / _s) };
}

float2i operator+(float2i _a, float2i _b)
{
	return { (int)(_a.x + _b.x), (int)_a.y + _b.y };
}

float2i operator-(float2i _a, float2i _b)
{
	return { (int)(_a.x - _b.x), (int)(_a.y - _b.y) };
}

float2i operator*(float2i _a, float2i _b)
{
	return { (int)(_a.x * _b.x), (int)(_a.y * _b.y) };
}

float2i operator*(matrix2 _a, float2i _b)
{
	return {
		(int)(_a.data[0][0] * _b.x + _a.data[0][1] * _b.y),
		(int)(_a.data[1][0] * _b.x + _a.data[1][1] * _b.y)
	};
}

std::ostream& operator<<(std::ostream& os, const float2i& f)
{
	return os << "{ " << f.x << " ; " << f.y << " }";
}