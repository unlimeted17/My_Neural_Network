#pragma once
#include "Matrix.h"
#include "ActivateFunction.h"

struct Layer
{
	Matrix matrix;
	double* values;
	double* Error;
};

class NetWork
{
public:
	NetWork();
	~NetWork();
	int Init();
	void Multi_T(double *error, int Number_L);
	void WeightsUpdater(double lr, int Number_L);
	void FeedForward();
	void BackPropogation();
	int Work();
private:
	int CountInputVector = 0;
	double* inputVector = nullptr;
	double* ErrorVector = nullptr;
	int Layers;
	Layer* layers = nullptr;
	int CountNeurons;
//	double *Wieghts;
	Matrix *matrix;
	ActivateFunction actFunc;
	double* Outvector = nullptr;


};

