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
	void NewConnectionSlot();//����������ͬ���ź�
	void SClose();//�ͻ�����������Ͽ�
	void DisConnect();//����������������ͻ��˶Ͽ�����
	void SReadData();//�����˿�
	void SSendMessage();

private:
	Ui::MainWindowClass ui;
	QTcpServer *server;
	//�ڷ���˱�дʱ����Ҫͬʱ����������˱����Ϳͻ��˱���
	QList<QTcpSocket *> tcpClientList;
	QTcpSocket *currentClient;
};
