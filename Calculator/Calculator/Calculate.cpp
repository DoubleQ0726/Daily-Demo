#include "Calculate.h"
#include <qdebug.h>

Calculate::Calculate(QObject *parent)
	: QObject(parent)
{
}

Calculate::~Calculate()
{
}

void Calculate::InitNumber(double num1, double num2)
{
	num_a = num1;
	num_b = num2;
}

double Calculate::Sub()
{
	double sum = num_a - num_b;
	return sum;
}

double Calculate::Mul()
{
	double sum = num_a * num_b;
	return sum;
}

double Calculate::Div()
{
	if (num_b == 0)
	{
		return INT_MAX;
	}
	else
	{
		double sum = num_a / num_b;
		return sum;
	}
}


double Calculate::Add()
{
	double sum = num_a + num_b;
	return sum;
}
