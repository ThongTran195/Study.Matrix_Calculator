#include <iostream>
#include "matrix.h"
#include <cassert>
#include "smatrix.h"

using namespace std;


void Matrix::allocation()
{
	entry = new double* [numRows];
	for (int i = 0; i < numRows; ++i)
		entry[i] = new double[numCols];
}

void Matrix::deallocation()
{
	for (int i = 0; i < numRows; ++i)
		delete[] entry[i];
	delete[] entry;

}


Matrix::Matrix(const int& m, const int& n)
{
	numRows = m;
	numCols = n;

	allocation();
	for (int i = 0; i < numRows; ++i)
		for (int j = 0; j < numCols; ++j)
			entry[i][j] = 0;
}

Matrix::Matrix(const int& m, const int& n, const int& val) :Matrix(m, n)
{
	for (int i = 0; i < numRows; ++i)
		for (int j = 0; j < numCols; ++j)
			entry[i][j] = val;
}

Matrix::Matrix(const Matrix& mat)
{
	this->numCols = mat.getcols();
	this->numRows = mat.getrows();

	allocation();

	for (int i = 0; i < this->numCols; ++i)
		for (int j = 0; j < this->numRows; ++j)
			this->entry[i][j] = mat.entry[i][j];
}

void Matrix::print(string name)
{
	for (int i = 0; i < numRows; ++i)
	{
		for (int j = 0; j < numCols; ++j)
		{
			cout << " " << entry[i][j] << ", ";
		}
		cout << endl;
	}
	cout << endl;
}


void Matrix::matrixinput() const
{
	for (int i = 0; i < numRows; ++i)
	{
		for (int j = 0; j < numCols; ++j)
		{
			cout << "\ns[" << i << "][" << j << "]=  ";
			cin >> entry[i][j];
		}
	}
}

bool Matrix::isSquare() const
{
	if (numRows == numCols)
		return true;
	return false;

}

double Matrix::operator()(const int& m, const int& n) const
{
	return entry[m][n];
}

double& Matrix::operator()(const int& m, const int& n)
{
	return entry[m][n];
}

void Matrix::zeros()
{
	for (int i = 0; i < numRows; ++i)
	{
		for (int j = 0; j < numCols; ++j)
		{
			entry[i][j] = 0;
		}
	}
}


Matrix& Matrix::operator++()
{
	for (int i = 0; i < numRows; ++i)
		for (int j = 0; j < numCols; ++j)
			++entry[i][j];
	return *this;

}

Matrix& Matrix::operator=(const Matrix& mat)
{
	numRows = mat.getrows();
	numCols = mat.getcols();
	for (int i = 0; i < numRows; ++i)
		for (int j = 0; j < numCols; ++j)
			this->entry[i][j] = mat.entry[i][j];
	return *this;
}

Matrix& Matrix::operator+=(const Matrix& mat)
{
	assert(mat.numRows == this->numRows);
	assert(mat.numCols == this->numCols);
	for (int i = 0; i < this->numRows; i++) {
		for (int j = 0; j < this->numCols; j++) {
			this->entry[i][j] += mat.entry[i][j];
		}
	}
	return *this;
}
Matrix& Matrix::operator+=(const double& val) {
	for (int i = 0; i < this->numRows; i++) {
		for (int j = 0; j < this->numCols; j++) {
			this->entry[i][j] += val;
		}
	}
	return *this;
}
Matrix& Matrix::operator*=(const double val) {
	for (int i = 0; i < this->numRows; i++) {
		for (int j = 0; j < this->numRows; j++) {
			this->entry[i][j] *= val;
		}
	}
	return *this;
}
Matrix& Matrix::operator*=(const Matrix& mat) {
	if (numCols != mat.getrows())
	{
		cout << "invalid sizes";
		assert(numCols == mat.getrows());
	}
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < mat.getcols(); j++)
		{
			double sum = 0.0;
			for (int k = 0; k < numCols; k++)
			{
				sum += entry[i][k] * mat.getentry(k, j);
			}
			this->setentry(i, j, sum);
		}
	}
	return *this;
}


Matrix operator+(const Matrix& mat1, const Matrix& mat2)
{
	Matrix result(mat1.getrows(), mat1.getcols());
	for (int i = 0; i < mat1.getrows(); ++i) {
		for (int j = 0; j < mat1.getcols(); ++j) {
			result.entry[i][j] = mat1.entry[i][j] + mat2.entry[i][j];
		}
	}
	return result;

}

Matrix operator-(const Matrix& mat1, const Matrix& mat2)
{
	Matrix result(mat1.getrows(), mat1.getcols());
	for (int i = 0; i < mat1.getrows(); ++i) {
		for (int j = 0; j < mat1.getcols(); ++j) {
			result.entry[i][j] = mat1.entry[i][j] - mat2.entry[i][j];
		}
	}
	return result;
}

Matrix operator*(const Matrix& mat1, const Matrix& mat2)
{
	Matrix result(mat1.getrows(), mat2.getcols());

	// Perform matrix multiplication
	for (int i = 0; i < mat1.getrows(); ++i) {
		for (int j = 0; j < mat2.getcols(); ++j) {
			for (int k = 0; k < mat1.getcols(); ++k) {
				result.entry[i][j] += mat1.entry[i][k] * mat2.entry[k][j];
			}
		}
	}
	return result;
}

Matrix operator*(const Matrix& mat, const double& alpha)
{
	Matrix result(mat.getrows(), mat.getcols());
	for (int i = 0; i < mat.getrows(); ++i) {
		for (int j = 0; j < mat.getcols(); ++j) {
			result.entry[i][j] = alpha * mat.entry[i][j];
		}
	}
	return result;
}






Matrix::~Matrix()
{

}

int  Matrix::getrows() const
{
	return numRows;
}

int Matrix::getcols() const
{
	return numCols;
}

double Matrix::getentry(const int& i, const int& j)const
{
	return entry[i][j];
}

double& Matrix::setentry(const int& i, const int& j, const int& val)
{
	return entry[i][j] = val;
}



Matrix transpose(Matrix& mat)
{
	Matrix TRANS(mat.getrows(), mat.getcols());
	for (int i = 0; i < mat.getrows(); ++i)
		for (int j = 0; j < mat.getcols(); ++j)
			TRANS.setentry(i, j, mat.getentry(j, i));
	return TRANS;
}






void actionOne_Matrix()
{
	Matrix* matrices[4] = { nullptr, nullptr, nullptr, nullptr };
	bool initialized[4] = { false, false, false, false };

	SquareMatrix* matrices_square[4] = { nullptr, nullptr, nullptr, nullptr };
	bool initialized_square[4] = { false, false, false, false };

	system("cls");
	int matrix_option_choice;
	do {
		cout << "\nMatrix Calculation Menu:\n";
		cout << "1. Input/Update a Matrix\n";
		cout << "2. Add Matrices\n";
		cout << "3. Subtract Matrices\n";
		cout << "4. Multiply Matrices\n";
		cout << "5. Scalar product\n";
		cout << "6. Find Determinants of Matrix\n";
		cout << "7. Find inverse Matrix\n";
		cout << "8. Exit to main menu\n";
		cout << "Enter your choice: ";
		cin >> matrix_option_choice;

		switch (matrix_option_choice)
		{
		case 1:
		{
			int matrixIndex, rows, cols;
			cout << "Select matrix to input/update (1=A, 2=B, 3=C, 4=D): ";
			cin >> matrixIndex;
			if (matrixIndex < 1 || matrixIndex > 4) {
				std::cout << "Invalid matrix selection.\n";
				break;
			}
			cout << "Enter rows for the matrix: ";
			cin >> rows;
			cout << "Enter columns for the matrix: ";
			cin >> cols;
			if (rows == cols)
			{
				delete matrices[matrixIndex - 1];
				delete matrices_square[matrixIndex - 1];

				matrices[matrixIndex - 1] = new Matrix(rows, cols);
				matrices[matrixIndex - 1]->matrixinput();
				matrices_square[matrixIndex - 1] = new SquareMatrix(rows);
				Matrix* mat1 = matrices[matrixIndex - 1];
				SquareMatrix* mat2 = matrices_square[matrixIndex - 1];
				*mat2 = *mat1;

				initialized[matrixIndex - 1] = true;
				initialized_square[matrixIndex - 1] = true;

				system("cls");
				cout << "The submit Matrix is: " << endl;

				matrices[matrixIndex - 1]->print(" Matrix ");

				cout << "This is a Square Matrix" << endl;
				break;
			}
			else
			{
				delete matrices[matrixIndex - 1];
				matrices[matrixIndex - 1] = new Matrix(rows, cols);
				matrices[matrixIndex - 1]->matrixinput();
				initialized[matrixIndex - 1] = true;
				system("cls");
				cout << "The submit Matrix is: " << endl;
				matrices[matrixIndex - 1]->print(" Matrix ");

				cout << "This is not a Square Matrix" << endl;
				break;
			}
		}
		case 2:
		case 3:
		{
			int matrix1, matrix2;
			cout << "Select two matrices (1=A, 2=B, 3=C, 4=D): " << endl;
			cout << "First matrix" << endl;
			cin >> matrix1;
			cout << "Second matrix" << endl;
			cin >> matrix2;

			if (matrix1 < 1 || matrix1 > 4 || matrix2 < 1 || matrix2 > 4 ||
				!initialized[matrix1 - 1] || !initialized[matrix2 - 1]) {
				cout << "Invalid or uninitialized matrix selection.\n";
				break;
			}

			try
			{
				Matrix* mat1 = matrices[matrix1 - 1];
				Matrix* mat2 = matrices[matrix2 - 1];
				if (mat1->getcols() == mat2->getcols() && mat2->getrows() == mat1->getrows())
				{
					switch (matrix_option_choice) {
					case 2: // Addition
					{
						system("cls");
						Matrix sum = *mat1 + *mat2;
						cout << "Sum of matrices: " << endl;
						sum.print("Sum of matrices:");
						break;
					}
					case 3: // Subtraction
					{
						system("cls");
						Matrix diff = *mat1 - *mat2;
						cout << "Subtraction of matrices: " << endl;
						diff.print("Difference of matrices: ");
						break;
					}
					}
				}
				else
				{
					cout << "Two matrix do not have the same number of columns and rows.\n";
					break;
				}
			}
			catch (const std::exception& e) {
				cout << "Error: " << e.what() << endl;
			}
			break;
		}
		case 4: // Multiplication
		{
			int matrix1, matrix2;
			cout << "Select two matrices (1=A, 2=B, 3=C, 4=D): " << endl;
			cout << "First matrix" << endl;
			cin >> matrix1;
			cout << "Second matrix" << endl;
			cin >> matrix2;

			if (matrix1 < 1 || matrix1 > 4 || matrix2 < 1 || matrix2 > 4 ||
				!initialized[matrix1 - 1] || !initialized[matrix2 - 1])
			{
				cout << "Invalid or uninitialized matrix selection.\n";
				break;
			}

			try
			{
				Matrix* mat1 = matrices[matrix1 - 1];
				Matrix* mat2 = matrices[matrix2 - 1];
				if (((mat1->getcols() == mat2->getrows()) || (mat1->getrows() == mat2->getcols())))
				{
					system("cls");
					Matrix product = *mat1 * *mat2;
					cout << "Product of matrices: " << endl;
					product.print("Product of matrices: ");
					break;
				}
				else
				{
					cout << "Two matrix do not have the the same number of columns or rows.\n";
					break;
				}

			}
			catch (const std::exception& e) {
				cout << "Error: " << e.what() << endl;
			}
			break;

		}
		case 5:
		{
			system("cls");
			int matrixIndex, scalar;
			cout << "Select a matrix for scalar multiplication (1=A, 2=B, 3=C, 4=D): ";
			cin >> matrixIndex;

			if (matrixIndex < 1 || matrixIndex > 4 || !initialized[matrixIndex - 1]) {
				cout << "Invalid or uninitialized matrix selection.\n";
				break;
			}

			cout << "Enter a scalar value: ";
			cin >> scalar;

			Matrix* mat = matrices[matrixIndex - 1];
			Matrix scalar_product = *mat * scalar;

			cout << "Result of scalar multiplication:\n";
			scalar_product.print("Result of scalar multiplication: ");
			break;
		}
		case 6:
		case 7:
		{
			int matrixIndex;
			cout << "Select a matrix for determinants or find inverse matrix (1=A, 2=B, 3=C, 4=D): ";
			cin >> matrixIndex;

			if (matrixIndex < 1 || matrixIndex > 4 || !initialized_square[matrixIndex - 1])
			{
				cout << "Invalid or uninitialized square matrix selection.\n";
				break;
			}
			try
			{
				SquareMatrix* mat = matrices_square[matrixIndex - 1];
				switch (matrix_option_choice)
				{
				case 6:
				{
					system("cls");
					double  det = mat->det();
					cout << " The determinants of matrix is " << det << endl;
					break;
				}
				case 7:
				{
					system("cls");
					SquareMatrix res = mat->inverse();
					cout << "The inverse matrix is: " << endl;
					res.print(" Inverse Matrix ");
					break;
				}
				}

			}
			catch (const std::exception& e) {
				cout << "Error: " << e.what() << endl;
			}
			break;
		}
		case 8:
			cout << "Back to main menu.\n" << endl;
			system("cls");
			break;

		default:
			cout << "Invalid choice. Please try again.\n";
		}
	} while (matrix_option_choice != 8);

	for (int i = 0; i < 4; ++i) {
		delete matrices[i];
		delete matrices_square[i];
	}
}

