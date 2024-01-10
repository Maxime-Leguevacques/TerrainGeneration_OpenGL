#include "Complex/complex.hpp"
#include "formulas.hpp"



complex::complex()
{
	a = ib = 0;
}

complex::~complex()
{

}

complex::complex(float _a, float _ib)
{
	a = _a;
	ib = _ib;

	GetData();
}


float complex::Module(complex _z)
{
	return std::sqrt((_z.a) * (_z.a) + (_z.ib) * (_z.ib));
}

void complex::GetData()
{
	float m = Module(*this);
	float t;
	if ((a >= 0 && ib >= 0) || (a >= 0 && ib <= 0)) {
		t = RadToDeg(std::asin(ib / m));
	}
	else if ((a <= 0 && ib >= 0) || (a <= 0 && ib <= 0)) {
		t = RadToDeg(std::acos(a / m));
	}
	module = m;
	teta = t;
}


#pragma region Operators

complex operator+(complex z, float _a)
{
	return { z.a + _a, z.ib };
}

complex operator-(complex z, float _a)
{
	return { z.a - _a, z.ib };
}

complex operator*(complex z, float _a)
{
	return { z.a * _a, z.ib * _a };
}

complex operator/(complex z, float _a)
{
	return { z.a / _a, z.ib / _a };
}

complex operator+(complex z1, complex z2)
{
	return { z1.a + z2.a, z1.ib + z2.ib };
}

complex operator-(complex z1, complex z2)
{
	return { z1.a - z2.a, z1.ib - z2.ib };
}

complex operator*(complex z1, complex z2)
{
	return { (z1.a * z2.a) - (z1.ib * z2.ib), (z1.a * z2.ib) + (z1.ib * z2.a) };
}

complex operator/(complex z1, complex z2)
{
	return { ((z1.a * z2.a) + (z1.ib * z2.ib)) / ((z2.a * z2.a) + (z2.ib * z2.ib)), ((-z1.a * z2.ib) + (z1.ib * z2.a)) / ((z2.a * z2.a) + (z2.ib * z2.ib)) };
}

#pragma endregion Operators