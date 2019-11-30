#include "MainWindow.h"
#include <qdebug.h>
#include <qregexp.h>
#include <QRegExpValidator>

MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	this->setWindowTitle(QStringLiteral("���׼�����"));
	this->setWindowIcon(QIcon(":/icon.jpg"));
	this->setFixedSize(this->width(), this->height());//������ߴ�̶�
	ui.pushButton_equal->setStyleSheet("QPushButton{ border:0px;}");//Ϊ�����۽�=��ť��������

	//����˳���ť���˳�����
	connect(ui.pushButton_exit, &QPushButton::clicked, this, &QWidget::close);
	//������ð�ť��������ݣ����¼���
	connect(ui.pushButton_reset, &QPushButton::clicked, this, &MainWindow::Reset);

	//���������д���
	QRegExp regExp("^[0-9]+\.{0,1}[0-9]{0,2}$");//ֻ��������������С��
	QValidator *validator = new QRegExpValidator(regExp, this);//��֤��
	ui.lineEdit_a->setPlaceholderText(QStringLiteral("����"));//����������ݽ�����ʾ
	ui.lineEdit_a->setClearButtonEnabled(1);
	ui.lineEdit_a->setValidator(validator);//����������ݽ�������
	connect(ui.lineEdit_a, &QLineEdit::textChanged, this, &MainWindow::GetNumA);
	ui.lineEdit_b->setPlaceholderText(QStringLiteral("����"));
	ui.lineEdit_b->setClearButtonEnabled(1);
	ui.lineEdit_b->setValidator(validator);
	connect(ui.lineEdit_b, &QLineEdit::textChanged, this, &MainWindow::GetNumB);
	ui.lineEdit_c->setReadOnly(1);//���������Ϊֻ��ģʽ
	

	connect(ui.radioButton_a, &QRadioButton::clicked, this, &MainWindow::InitCalculateA);//����ӷ���ť��ʵ�ּӷ�����
	connect(ui.radioButton_b, &QRadioButton::clicked, this, &MainWindow::InitCalculateS);//���������ť��ʵ�ּ�������
	connect(ui.radioButton_c, &QRadioButton::clicked, this, &MainWindow::InitCalculateM);//����˷���ť��ʵ�ֳ˷�����
	connect(ui.radioButton_d, &QRadioButton::clicked, this, &MainWindow::InitCalculateD);//���������ť��ʵ�ֳ�������
	//����ȺŰ�ť����ʾ���
	connect(ui.pushButton_equal, &QPushButton::clicked, this, &MainWindow::ShowRes);
}

void MainWindow::GetNumA()//��ȡ�û����������
{
	num_a = ui.lineEdit_a->text().toDouble();
}

void MainWindow::GetNumB()
{
	num_b = ui.lineEdit_b->text().toDouble();
}

void MainWindow::InitCalculateA()//��ʼ���Ӽ��˳��ļ��㷽��
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
		ui.lineEdit_c->setText(QStringLiteral("��������Ϊ0������������"));
	}
	delete cal;
	cal = NULL;
}

void MainWindow::ShowRes()//���������ʾ���
{
	QString display = QString::number(res);
	ui.lineEdit_c->setText(display);
}

void MainWindow::Reset()//���õ�ǰ����
{
	ui.lineEdit_a->clear();
	num_a = 0;
	ui.lineEdit_b->clear();
	num_b = 0;
	ui.lineEdit_c->clear();
	res = 0;
}
