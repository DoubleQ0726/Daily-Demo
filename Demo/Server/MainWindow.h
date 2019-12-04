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
	void NewConnectionSlot();//服务器处理不同的信号
	void SClose();//客户端与服务器断开
	void DisConnect();//服务器主动与这个客户端断开连接
	void SReadData();//监听端口
	void SSendMessage();

private:
	Ui::MainWindowClass ui;
	QTcpServer *server;
	//在服务端编写时，需要同时定义服务器端变量和客户端变量
	QList<QTcpSocket *> tcpClientList;
	QTcpSocket *currentClient;
};
