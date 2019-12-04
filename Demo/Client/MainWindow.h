#pragma once

#include <QtWidgets/QWidget>
#include "ui_MainWindow.h"
#include <qtcpsocket.h>
#include <qmessagebox.h>

class MainWindow : public QWidget
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();

public slots:
	void Connect();//����
	void Close();//�Ͽ�
	void ReadError(QAbstractSocket::SocketError);
	void ReadData();
	void SendMessage();



private:
	Ui::MainWindowClass ui;
	QTcpSocket * client;
};
