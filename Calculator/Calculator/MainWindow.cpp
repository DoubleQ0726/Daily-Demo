#include "MainWindow.h"
#include <qdebug.h>
#include <qregexp.h>
#include <QRegExpValidator>

MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	this->setWindowTitle(QStringLiteral("简易计算器"));
	this->setWindowIcon(QIcon(":/icon.jpg"));
	this->setFixedSize(this->width(), this->height());//将界面尺寸固定
	ui.pushButton_equal->setStyleSheet("QPushButton{ border:0px;}");//为了美观将=按钮进行隐藏

	//点击退出按钮，退出程序
	connect(ui.pushButton_exit, &QPushButton::clicked, this, &QWidget::close);
	//点击重置按钮，清空数据，重新计算
	connect(ui.pushButton_reset, &QPushButton::clicked, this, &MainWindow::Reset);

	//对输入框进行处理
	QRegExp regExp("^[0-9]+\.{0,1}[0-9]{0,2}$");//只能输入整数或者小数
	QValidator *validator = new QRegExpValidator(regExp, this);//验证器
	ui.lineEdit_a->setPlaceholderText(QStringLiteral("数字"));//对输入的内容进行提示
	ui.lineEdit_a->setClearButtonEnabled(1);
	ui.lineEdit_a->setValidator(validator);//对输入的内容进行限制
	connect(ui.lineEdit_a, &QLineEdit::textChanged, this, &MainWindow::GetNumA);
	ui.lineEdit_b->setPlaceholderText(QStringLiteral("数字"));
	ui.lineEdit_b->setClearButtonEnabled(1);
	ui.lineEdit_b->setValidator(validator);
	connect(ui.lineEdit_b, &QLineEdit::textChanged, this, &MainWindow::GetNumB);
	ui.lineEdit_c->setReadOnly(1);//将输出框设为只读模式
	

	connect(ui.radioButton_a, &QRadioButton::clicked, this, &MainWindow::InitCalculateA);//点击加法按钮，实现加法运算
	connect(ui.radioButton_b, &QRadioButton::clicked, this, &MainWindow::InitCalculateS);//点击减法按钮，实现减法运算
	connect(ui.radioButton_c, &QRadioButton::clicked, this, &MainWindow::InitCalculateM);//点击乘法按钮，实现乘法运算
	connect(ui.radioButton_d, &QRadioButton::clicked, this, &MainWindow::InitCalculateD);//点击除法按钮，实现除法运算
	//点击等号按钮，显示结果
	connect(ui.pushButton_equal, &QPushButton::clicked, this, &MainWindow::ShowRes);
}

void MainWindow::GetNumA()//获取用户输入的数据
{
	num_a = ui.lineEdit_a->text().toDouble();
}

void MainWindow::GetNumB()
{
	num_b = ui.lineEdit_b->text().toDouble();
}

void MainWindow::InitCalculateA()//初始化加减乘除的计算方法
{
	cal = new Calculate(this);
	cal->InitNumber(num_a, num_b);
	res = cal->Add();
	delete cal;
	cal = NULL;
}

void MainWindow::InitCalculateS()
{
	cal = new Calculate(this);
	cal->InitNumber(num_a, num_b);
	res = cal->Sub();
	delete cal;
	cal = NULL;
}

void MainWindow::InitCalculateM()
{
	cal = new Calculate(this);
	cal->InitNumber(num_a, num_b);
	res = cal->Mul();
	delete cal;
	cal = NULL;
}

void MainWindow::InitCalculateD()
{
	cal = new Calculate(this);
	cal->InitNumber(num_a, num_b);
	res = cal->Div();
	if (res == INT_MAX)
	{
		ui.lineEdit_c->setText(QStringLiteral("除数不能为0，请重新输入"));
	}
	delete cal;
	cal = NULL;
}

void MainWindow::ShowRes()//在输出框显示结果
{
	QString display = QString::number(res);
	ui.lineEdit_c->setText(display);
}

void MainWindow::Reset()//重置当前计算
{
	ui.lineEdit_a->clear();
	num_a = 0;
	ui.lineEdit_b->clear();
	num_b = 0;
	ui.lineEdit_c->clear();
	res = 0;
}
