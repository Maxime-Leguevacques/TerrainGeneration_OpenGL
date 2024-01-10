
#include "Float/floatX.hpp"



floatX::floatX()
{

}

floatX::~floatX()
{

}

floatX::floatX(int fsize)
{
	size = fsize;
	float_X.resize(fsize);
	for (int i = 0; i < size; i++)
		float_X[i] = 0;
}


void floatX::print() const
{
	std::cout << "{ ";
	for (int i = 0; i < size; i++) {
		std::cout << float_X[i];
		if (i == size - 1) 
			std::cout << " }\n";
		else
			std::cout << " ; ";
	}
}

void floatX::print(std::string name) const
{
	std::cout << "float" << size << " " << std::string(name) << " :\n{ ";
	for (int i = 0; i < size; i++) {
		std::cout << float_X[i];
		if (i == size - 1)
			std::cout << " }\n";
		else
			std::cout << " ; ";
	}
}


#pragma region Vector related 

floatX floatX::normalize(floatX a)
{
	return a / length(a);
}

float floatX::length(floatX a)
{
	float length = 0;
	std::vector<float> table = a.float_X;

	for (int i = 0; i < table.size(); i++)
		table[i] = table[i] * table[i];

	for (int i = 0; i < table.size(); i++)
		length += table[i];

	return sqrt(length);
}

float floatX::lengthSq(floatX a)
{
	float lengthSq = 0;
	std::vector<float> table = a.float_X;

	for (int i = 0; i < table.size(); i++)
		table[i] = table[i] * table[i];

	for (int i = 0; i < table.size(); i++)
		lengthSq += table[i];

	return lengthSq;
}

float floatX::dist(floatX a, floatX b)
{
	return length(a - b);
}

float floatX::dot(floatX a, floatX b)
{
	if (a.size != b.size) {
		std::cout << "Can't calculate dot product between different size vectors.\n";
		return 0;
	}
	float result = 0;
	floatX table(a.size);
	std::vector<float> table_a = a.float_X;
	std::vector<float> table_b = b.float_X;

	for (int i = 0; i < table.size; i++) {
		table.float_X[i] = table_a[i] * table_b[i];
	}
	for (int i = 0; i < table.size; i++)
		result += table.float_X[i];

	return result;
}

floatX floatX::cross(floatX a, floatX b)
{
	floatX newA(a.size + 2);
	floatX newB(b.size + 2);
	newA = newA + a;
	newB = newB + b;
	newA.float_X[newA.size - 2] = a.float_X[0];
	newA.float_X[newA.size - 1] = a.float_X[1];
	newB.float_X[newB.size - 2] = b.float_X[0];
	newB.float_X[newB.size - 1] = b.float_X[1];
	floatX c(a.size);
	for (int i = 0; i < a.size; i++)
		c.float_X[i] = (newA.float_X[i + 1] * newB.float_X[i + 2]) - (newA.float_X[i + 2] * newB.float_X[i + 1]);
	
	return c;
}

#pragma endregion Vector related


// operators

floatX operator+(floatX a, float n)
{
	floatX temp(a.size);
	for (int i = 0; i < temp.size; i++)
		temp.float_X[i] = a.float_X[i] + n;
	return temp;
}
floatX operator-(floatX a, float n)
{
	floatX temp(a.size);
	for (int i = 0; i < temp.size; i++)
		temp.float_X[i] = a.float_X[i] - n;
	return temp;
}
floatX operator*(floatX a, float s)
{
	floatX temp(a.size);
	for (int i = 0; i < temp.size; i++)
		temp.float_X[i] = a.float_X[i] * s;
	return temp;
}
floatX operator/(floatX a, float n)
{
	floatX temp(a.size);
	for (int i = 0; i < temp.size; i++)
		temp.float_X[i] = a.float_X[i] / n;
	return temp;
}
floatX operator+(floatX a, floatX b)
{
	float size_AA = a.size;
	float size_BB = b.size;

	// Check if a or b is bigger than the other to set the vector's size to the biggest
	if (a.size < b.size) {
		size_AA = b.size;
	}
	else if (a.size > b.size) {
		size_BB = a.size;
	}
	else {
		size_AA = size_BB = a.size; 
	}

	// Make two new vectors init to 0 and add a and b
	floatX AA(size_AA);
	floatX BB(size_BB);

	for (int i = 0; i < a.size; i++)
		AA.float_X[i] = a.float_X[i];
	for (int i = 0; i < b.size; i++)
		BB.float_X[i] = b.float_X[i];

	floatX temp(size_AA);
	for (int i = 0; i < temp.size; i++) {
		temp.float_X[i] = AA.float_X[i] + BB.float_X[i];
	}

	return temp;
}
floatX operator-(floatX a, floatX b)
{
	float size_AA = a.size;
	float size_BB = b.size;

	// Check if a or b is bigger than the other to set the vector's size to the biggest
	if (a.size < b.size) {
		size_AA = b.size;
	}
	else if (a.size > b.size) {
		size_BB = a.size;
	}
	else {
		size_AA = size_BB = a.size;
	}

	// Make two new vectors init to 0 and add a and b
	floatX AA(size_AA);
	floatX BB(size_BB);

	for (int i = 0; i < a.size; i++)
		AA.float_X[i] = a.float_X[i];
	for (int i = 0; i < b.size; i++)
		BB.float_X[i] = b.float_X[i];

	floatX temp(size_AA);
	for (int i = 0; i < temp.size; i++) {
		temp.float_X[i] = AA.float_X[i] - BB.float_X[i];
	}

	return temp;
}

std::ostream& operator<<(std::ostream& os, const floatX& f)
{
	os << "{ ";
	for (int i = 0; i < f.size; i++) {
		os << f.float_X[i];
		if (i == f.size - 1)
			os << " }\n";
		else
			os << " ; ";
	}
	return os;
}