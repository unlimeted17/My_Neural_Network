#include "Matrix.h"
#include <cstdlib>
#include <iostream>

Matrix::Matrix() : row(3), col(3)
{

}
Matrix::~Matrix()
{ 
	if (matrix != nullptr) {
		for (int i = 0; i < this->row; ++i)
			delete[] matrix[i];
		delete[] matrix;
	}
	if (bios != nullptr)
		delete[] bios;
}

void Matrix::Init(int row, int col)
{
	
	this->row = row; this->col = col;
	bios = new double[row];
	matrix = new double* [row];
	for (int i = 0; i < row; ++i)
		matrix[i] = new double[col];

	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			//matrix[i][j] = ((rand() % 100)) * 0.03 / (row + 35);;
			matrix[i][j] = RAND_WEIGHT;
		}
	}

	for (int i = 0; i < row; ++i) {
		bios[i] = RAND_WEIGHT;
	}
	

}
void Matrix::Print() {
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			std::cout << matrix[i][j] << " ";
		}
		std::cout << "\n";
	}
}
