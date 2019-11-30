#pragma once

#include <QObject>
#include <qvector.h>

class Calculate : public QObject
{
	Q_OBJECT

public:
	Calculate(QObject *parent);
	~Calculate();
	void InitNumber(double num1, double num2);

public slots:
	double Add();
	double Sub();
	double Mul();
	double Div();
private:
	double num_a;
	double num_b;
};
