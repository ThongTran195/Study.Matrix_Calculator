#include <iostream>
#include <cassert>
#include <cmath>
#include "vector.h"
#include "matrix.h"
#include "smatrix.h"

// complete all missing methods here
SquareMatrix::SquareMatrix(const int& s) : Matrix(s, s) {
	// Matrix(s,s): row = s; col = s; allocate();
	// initialize size
	size = s;
}

SquareMatrix::SquareMatrix(const int& s, const double& val) : Matrix(s, s, val) {
	size = s;
}

SquareMatrix::SquareMatrix(const Matrix& mat) : Matrix(mat.getrows(), mat.getcols())
{
	assert(mat.isSquare() == true);

	size = numRows;

	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			this->entry[i][j] = mat(i, j);
}

SquareMatrix::SquareMatrix(const SquareMatrix& mat) : SquareMatrix(mat.getSize())
{
	if (mat.isSquare() == false)
	{
		cout << "This matrix is not a square matrix" << endl;
	}
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			this->entry[i][j] = mat(i, j);
}

int SquareMatrix::getSize() const {
	return size;
}

SquareMatrix& SquareMatrix::operator=(const Matrix& mat)
{
	assert(mat.isSquare() == true);
	size = mat.getrows();

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			this->entry[i][j] = mat(i, j);
		}
	}
	return *this;
}

SquareMatrix& SquareMatrix::operator=(const SquareMatrix& mat)
{
	if (mat.isSquare() == false)
	{
		cout << "This matrix is not a square matrix" << endl;
	}
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			this->entry[i][j] = mat(i, j);
		}
	}
	return *this;
}

SquareMatrix::~SquareMatrix() {
	// do nothing
}

double SquareMatrix::det() const {
	int	size_h(size);	// size of submatrix Ah
	double	result(0.0);

	if (size_h == 1)
		result = entry[0][0];
	else
	{
		size_h = size - 1;
		for (int j = 0; j < size; ++j)
		{
			// form Ah with row 0 and col j removed from A
			SquareMatrix Ah(size_h);
			Ah.zeros();
			for (int ii = 0; ii < size_h; ++ii)
			{
				for (int jj = 0; jj < j; ++jj)
					Ah(ii, jj) = entry[ii + 1][jj];
				for (int jj = j; jj < size_h; ++jj)
					Ah(ii, jj) = entry[ii + 1][jj + 1];
			}
			// recursion
			result += pow(-1.0, j) * entry[0][j] * Ah.det();
		}	// endfor j
	}	// endif

	return result;
}

// cofactor matrix by removing row p and col q
SquareMatrix SquareMatrix::cofactor(const int& p, const int& q) const {
	assert(p > -1 && p < size);
	assert(q > -1 && q < size);

	Matrix temp(size - 1, size, 0.0);
	// remove row p
	for (int jj = 0; jj < temp.getcols(); ++jj)
	{
		for (int ii = 0; ii < p; ++ii)
			temp(ii, jj) = entry[ii][jj];
		for (int ii = p; ii < temp.getrows(); ++ii)
			temp(ii, jj) = entry[ii + 1][jj];
	}

	SquareMatrix co(size - 1, 0.0);

	// remove col q
	for (int ii = 0; ii < co.getSize(); ++ii)
	{
		for (int jj = 0; jj < q; ++jj)
			co(ii, jj) = temp(ii, jj);
		for (int jj = q; jj < co.getSize(); ++jj)
			co(ii, jj) = temp(ii, jj + 1);
	}

	return co;
}

SquareMatrix SquareMatrix::adjoint() const {
	SquareMatrix adj(size, 0.0);

	if (size == 1) {
		adj(0, 0) = 1;
		return adj;
	}

	// temp is used to store cofactors of A[][]
	int sign = 1;
	SquareMatrix temp(size - 1, 0.0);

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			// Get cofactor of A[i][j]
			temp = cofactor(i, j);

			// sign of adj[j][i] positive if sum of row
			// and column indexes is even.
			sign = ((i + j) % 2 == 0) ? 1 : -1;

			// get the

			// Interchanging rows and columns to get the
			// transpose of the cofactor matrix
			adj(j, i) = (sign)*temp.det();
		}
	}

	return adj;
}

SquareMatrix SquareMatrix::inverse() const {
	assert(fabs(det()) > 0.0);

	// Find adjoint
	SquareMatrix adj = adjoint();

	// Find Inverse using formula inverse(A) = adj(A)/det(A)
	SquareMatrix inv(size, 0.0);
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			inv(i, j) = adj(i, j) / det();

	return inv;
}
