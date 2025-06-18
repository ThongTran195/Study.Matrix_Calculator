#ifndef _SQUARE_MATRIX_
#define _SQUARE_MATRIX_

#include "matrix.h"

class SquareMatrix : public Matrix {
protected:
	int size;

public:

	SquareMatrix(const int& s);
	SquareMatrix(const int& s, const double& val);
	SquareMatrix(const Matrix& mat);
	SquareMatrix(const SquareMatrix& mat);
	virtual ~SquareMatrix();


	int getSize() const;
	SquareMatrix& operator=(const Matrix& mat);
	SquareMatrix& operator=(const SquareMatrix& mat);


	double det() const;
	SquareMatrix inverse() const;


	SquareMatrix cofactor(const int& p, const int& q) const;
	SquareMatrix adjoint() const;
};



#endif
