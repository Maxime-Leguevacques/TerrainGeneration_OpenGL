
#include <string>

#include "Matrix/matrixX.hpp"



matrixX::matrixX()
{

}

matrixX::~matrixX()
{
	//delete[] mat;
}

matrixX::matrixX(int row, int col)
{
	rows = row;
	columns = col;
	mat.resize(rows * columns);
	for (int i = 0; i < rows * columns; i++)
		mat[i] = 0;
}

matrixX::matrixX(int size) : matrixX::matrixX(size, size)
{

}



void matrixX::print() const
{
	// Check which number in the matrixX is the biggest in character size

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++)
			std::cout << " " << mat[i * columns + j];
		std::cout << "\n";
	}
}

void matrixX::print(std::string name) const
{
	std::cout << " matrixX " << name << " :" << std::endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++)
			std::cout << " " << mat[i * columns + j];
		std::cout << "\n";
	}
}


#pragma region Verifications

bool matrixX::checkIfSameSize(const matrixX& A, const matrixX& B)
{
	if (A.rows == B.rows && A.columns == B.columns)
		return true;
	else
		return false;
}

bool matrixX::checkIfMultiplyOk(const matrixX& A, const matrixX& B)
{
	if (A.columns == B.rows)
		return true;
	else
		return false;
}

bool matrixX::checkIfDiagonal()
{
	if (rows == columns) {
		bool isDiagonal = true;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				if (i == j)
					continue;
				else if (mat[i * rows + j] != 0)
					return false;
			}
		}
		return true;
	}
	else {
		return false;
	}
}

#pragma endregion Verifications

matrixX matrixX::transpose()
{
	// create old and new matrixX in double array
	std::vector<std::vector<float>> oldMatrix = std::vector<std::vector<float>>(rows);
	std::vector<std::vector<float>> TMatrix = std::vector<std::vector<float>>(columns);
	for (int i = 0; i < rows; i++)
		oldMatrix[i] = std::vector<float>(columns);
	for (int i = 0; i < columns; i++)
		TMatrix[i] = std::vector<float>(rows);

	// initialise oldMatrix to matrixX being transpose
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			oldMatrix[i][j] = mat[i * columns + j];

	// transpose matrixX
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			TMatrix[j][i] = oldMatrix[i][j];
		}
	}

	// create matrixX and assign TMatrix values to it
	matrixX transpose(columns, rows);
	for (int i = 0; i < transpose.rows; i++)
		for (int j = 0; j < transpose.columns; j++)
			transpose.mat[i * transpose.columns + j] = TMatrix[i][j];

	return transpose;
}

floatX matrixX::getDiagonal()
{
	if (!(rows == columns))
		return 0;

	floatX diag(rows);
	int k = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (i == j) {
				diag.float_X[k] = mat[i * rows + j];
				k++;
			}
		}
	}
	return diag;
}

float matrixX::trace()
{
	float sum = 0.f;
	if (rows == columns) {
		floatX diag(rows);
		diag = getDiagonal();
		for (int i = 0; i < diag.size; i++)
			sum += diag.float_X[i];
	}
	else {
		return 0;
	}

	return sum;
}

float matrixX::det2()
{
	return mat[0] * mat[3] - mat[1] * mat[2];
}

float matrixX::det3()
{
	float result = 0;
	result =
		mat[0] * (mat[4] * mat[8] - mat[7] * mat[5]) -
		mat[1] * (mat[3] * mat[8] - mat[6] * mat[5]) +
		mat[2] * (mat[3] * mat[7] - mat[6] * mat[4]);
	return result;
}

matrixX matrixX::GaussJordan()
{
	// create 2 matrices as double arrays to simplify calculus
	std::vector<std::vector<float>> oldMatrix = std::vector<std::vector<float>>(rows);
	std::vector<std::vector<float>> newMatrix = std::vector<std::vector<float>>(rows);

	// initialize the matrices
	for (int i = 0; i < rows; i++) {
		oldMatrix[i] = std::vector<float>(columns);
		newMatrix[i] = std::vector<float>(columns);
	}

	// set oldMatrix to the matrixX being used
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			oldMatrix[i][j] = mat[i * columns + j];


	bool makeMat = false;
	float pivot_nb = 0;

	// Gauss-Jordan Pivot
	for (int line = 0; line < rows; line++) {
		// find pivot number
		for (int i = 0; i < columns; i++) {
			if (oldMatrix[line][i] != 0) {
				if (i == columns && oldMatrix[line][i] == 0)
					makeMat = true;

				pivot_nb = oldMatrix[line][line];
				break;
			}
			else
				continue;
		}

		if (!makeMat) {
			// set current row pivot number to 1 and divide numbers in row by coef
			for (int j = line; j < columns; j++)
				newMatrix[line][j] = oldMatrix[line][j] / pivot_nb;

			// replace old matrixX line by newMatrix line
			for (int i = 0; i < columns; i++)
				oldMatrix[line][i] = newMatrix[line][i];

			// substract remaining rows to have number in column = 0
			int nbModifiedRows = 0;
			for (int i = line + 1; i < rows; i++) {
				for (int k = 0; k < columns; k++)
					newMatrix[i][k] = oldMatrix[i][k] - (oldMatrix[line][k] * oldMatrix[i][line]);
		
				nbModifiedRows++;
			}

			if (nbModifiedRows < rows - 1) {
				for (int i = 0; i < rows - nbModifiedRows; i++) {
					for (int k = 0; k < columns; k++)
						newMatrix[i][k] = oldMatrix[i][k] - (oldMatrix[line][k] * oldMatrix[i][line]);

					nbModifiedRows++;
				}
			}

			// set oldMatrix as newMatrix
			oldMatrix = newMatrix;
		}
	}

	matrixX GJmat(rows, columns);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (newMatrix[i][j] == -0)
				newMatrix[i][j] = 0;
			GJmat.mat[i * columns + j] = newMatrix[i][j];
		}
	}

	return GJmat;
}


// TRS

matrixX matrixX::GetTranslationMatrix(float3 position)
{
	matrixX mat(4);
	mat.mat = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		position.x, position.y, position.z, 1
	};
	return mat;
}

matrixX matrixX::GetRotationMatrix(float3 anglesRad)
{
	matrixX rotationX(4);
	rotationX.mat = {
		1, 0, 0, 0,
		0, cos(anglesRad.x), sin(anglesRad.x), 0,
		0, -sin(anglesRad.x), cos(anglesRad.x), 0,
		0, 0, 0, 1
	};
	matrixX rotationY(4);
	rotationY.mat = {
		cos(anglesRad.y), 0, -sin(anglesRad.y), 0,
		0, 1, 0, 0,
		sin(anglesRad.y), 0, cos(anglesRad.y), 0,
		0, 0, 0, 1
	};
	matrixX rotationZ(4);
	rotationZ.mat = {
		cos(anglesRad.z), sin(anglesRad.z), 0, 0,
		-sin(anglesRad.z), cos(anglesRad.z), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	matrixX rotationMat = rotationZ * rotationY * rotationX;
	return rotationMat;
}

matrixX matrixX::GetScaleMatrix(float3 scale)
{
	matrixX scaleMat(4);
	scaleMat.mat = {
		scale.x, 0, 0, 0,
		0, scale.y, 0, 0,
		0, 0, scale.z, 0,
		0, 0, 0, 1
	};
	return scaleMat;
}

matrixX matrixX::Get_TRS_Matrix(float3 position, float3 rotaionAngle, float3 scale)
{
	matrixX trs(4);
	trs = matrixX::GetTranslationMatrix(position) * matrixX::GetRotationMatrix(rotaionAngle) * matrixX::GetScaleMatrix(scale);
	return trs;
}




#pragma region Operators

matrixX operator+(matrixX A, float n)
{
	for (int i = 0; i < A.rows; i++) {
		for (int j = 0; j < A.columns; j++)
			A.mat[i * A.columns + j] += n;
		return A;
	}
}
matrixX operator-(matrixX A, float n)
{
	for (int i = 0; i < A.rows; i++)
		for (int j = 0; j < A.columns; j++)
			A.mat[i * A.columns + j] -= n;

	return A;
}
matrixX operator*(matrixX A, float s)
{
	for (int i = 0; i < A.rows; i++) {
		for (int j = 0; j < A.columns; j++) {
			A.mat[i * A.columns + j] *= s;
			if (A.mat[i * A.columns + j] == -0)		// avoid getting -0 as a result
				A.mat[i * A.columns + j] = 0;
		}
	}

	return A;
}
matrixX operator/(matrixX A, float s)
{
	return A * (1.0f / s);
}

matrixX operator+(matrixX A, matrixX B)
{
	if (!matrixX::checkIfSameSize(A, B)) {
		std::cout << "A and B can't be added.\n";
		return 0;
	}
	matrixX C(A.rows, A.columns);

	for (int i = 0; i < A.rows; i++)
		for (int j = 0; j < A.columns; j++)
			C.mat[i * C.columns + j] = A.mat[i * A.columns + j] + B.mat[i * B.rows + j];

	return C;
}
matrixX operator-(matrixX A, matrixX B)
{
	if (!matrixX::checkIfSameSize(A, B)) {
		std::cout << "A and B can't be added.\n";
		return 0;
	}
	matrixX C(A.rows, A.columns);

	for (int i = 0; i < C.rows; i++)
		for (int j = 0; j < C.columns; j++)
			C.mat[i * C.columns + j] = A.mat[i * A.columns + j] - B.mat[i * B.rows + j];

	return C;
}
matrixX operator*(matrixX A, matrixX B)
{
	if (!matrixX::checkIfMultiplyOk(A, B)) {
		std::cout << "can't be multiplied.\n";
		return 0;
	}

	//create 2 matrices using std::vector to do double array to simplify calculus
	std::vector<std::vector<float>> AA = std::vector<std::vector<float>>(A.rows);
	std::vector<std::vector<float>> BB = std::vector<std::vector<float>>(B.rows);

	// columns, now do rows
	for (int i = 0; i < A.rows; i++)
		AA[i] = std::vector<float>(A.columns);

	for (int i = 0; i < B.rows; i++)
		BB[i] = std::vector<float>(B.columns);

	// initialise AA and BB matrices to A and B
	for (int i = 0; i < A.rows; i++)
		for (int j = 0; j < A.columns; j++)
			AA[i][j] = A.mat[i * A.columns + j];

	for (int i = 0; i < B.rows; i++)
		for (int j = 0; j < B.columns; j++)
			BB[i][j] = B.mat[i * B.columns + j];

	matrixX C(A.rows, B.columns);

	for (int i = 0; i < C.rows; i++) {
		for (int j = 0; j < C.columns; j++) {

			float result = 0;

			for (int k = 0; k < A.columns; k++) {
				result = result + (AA[i][k] * BB[k][j]);
			}

			C.mat[i * C.columns + j] = result;
		}
	}
	return C;
}

std::ostream& operator<<(std::ostream& os, const matrixX& matrixX)
{
	for (int i = 0; i < matrixX.rows; i++) {
		for (int j = 0; j < matrixX.columns; j++)
			os << " " << matrixX.mat[i * matrixX.columns + j];
		os << "\n";
	}
	return os;
}

#pragma endregion Operators