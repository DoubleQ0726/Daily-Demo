#pragma once

#include <QtWidgets/QWidget>
#include "ui_MainWindow.h"
#include "Calculate.h"


class MainWindow : public QWidget
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);

public slots:
	void GetNumA();
	void GetNumB();
	void InitCalculateA();
	void InitCalculateS();
	void InitCalculateM();
	void InitCalculateD();
	void ShowRes();
	void Reset();

private:
	Ui::MainWindowClass ui;
	double num_a;
	double num_b;
	double res;
	Calculate * cal;
};
