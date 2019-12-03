#pragma once

#include <QtWidgets/QWidget>
#include "ui_MainWindow.h"
#include <qtcpsocket.h>
#include <qtcpserver.h>

class MainWindow : public QWidget
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);

public slots:
	void NewConnectionSlot();//监听端口
	void SClose();//断开
	void SReadData();
	void SSendMessage();

private:
	Ui::MainWindowClass ui;
	QTcpServer *server;
	//在服务端编写时，需要同时定义服务器端变量和客户端变量
	QList<QTcpSocket *> tcpClientList;
	QTcpSocket *currentClient;
};
