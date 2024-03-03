#pragma once

#include <stdlib.h>

#define LEARN_RATE 0.2 /* Коэффициент обучения */
#define RAND_WEIGHT ( ((double)rand() / (double)RAND_MAX) - 0.5)
#define getSRand() ((double)rand() / (double)RAND_MAX)

#define getRand(x) (int)((x) * getSRand())
#define sqr(x) ((x) * (x))


class Matrix
{
public:
	Matrix();
	~Matrix();
	void Init(int row, int col);
	void Print();
	double** matrix = nullptr;
	double* bios = nullptr;
	int row; int col;
private:

	
};

