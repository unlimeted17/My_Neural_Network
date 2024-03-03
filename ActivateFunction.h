#pragma once

#include "ActivateFunction.h"

enum activateFunc { sigmoid = 1, ReLU, thx };
class ActivateFunction
{
public:
	ActivateFunction();
	~ActivateFunction();
	void set();
	void use(double* value, int n);
	void useDer(double* value, int n);
	double useDer(double value);
private:
	activateFunc actFunc;
};

