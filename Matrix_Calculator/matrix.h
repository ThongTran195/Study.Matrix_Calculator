#ifndef _MATRIX_HEADER_
#define _MATRIX_HEADER_

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <stdexcept>
using namespace std;



class Matrix
{
protected:

	int numRows;
	int numCols;
	double** entry;


	void allocation();
	void deallocation();

public:


	Matrix(const int& m, const int& n);
	Matrix(const int& m, const int& n, const int& val);
	Matrix(const Matrix& mat);


	virtual ~Matrix();

	int getrows()const;
	int getcols()const;
	double getentry(const int& i, const int& j)const;
	double& setentry(const int& i, const int& j, const int& val);


	void print(string name);
	void zeros();
	void matrixinput() const;

	bool isSquare() const;

	double operator() (const int& m, const int& n) const;
	double& operator() (const int& m, const int& n);

	Matrix& operator++ ();
	Matrix& operator= (const Matrix& mat);

	Matrix& operator+=(const Matrix& mat);
	Matrix& operator+=(const double& val);
	Matrix& operator*=(const double val);
	Matrix& operator*=(const Matrix& mat);

	friend Matrix operator +(const Matrix& mat1, const Matrix& mat2);
	friend Matrix operator -(const Matrix& mat1, const Matrix& mat2);
	friend Matrix operator *(const Matrix& mat1, const Matrix& mat2);
	friend Matrix operator *(const Matrix& mat, const double& alpha);


};



Matrix transpose(Matrix& mat);


void actionOne_Matrix();


#endif
