#include "MainWindow.h"
#include <qnetworkinterface.h>

MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowTitle(QStringLiteral("������"));
	server = new QTcpServer(this);
	currentClient = new QTcpSocket(this);
	QList<QHostAddress> IPaddress = QNetworkInterface::allAddresses();
	for (size_t i = 0; i < IPaddress.size(); i++)
	{
		if (IPaddress.at(i) != QHostAddress::LocalHost && IPaddress.at(i).toIPv4Address())
		{
			ui.lineEdit_ip->setText(IPaddress.at(i).toString());
		}
	}

	//ÿ���пͻ��������ź�,������������Ӧ
	connect(server, &QTcpServer::newConnection, this, &MainWindow::NewConnectionSlot);
}


void MainWindow::NewConnectionSlot()
{
	currentClient = server->nextPendingConnection();//�õ�һ��tcp����
	tcpClientList.push_back(currentClient);//��Ϊһ�����������Զ�Ӧ����ͻ��ˣ����Զ��洢����
	ui.comboBox->addItem(tr("%1, %2").arg(currentClient->peerAddress().toString().split("::ffff:")[1]).arg(currentClient->peerPort()));
}

void MainWindow::SClose()
{
}

void MainWindow::SReadData()
{
}

void MainWindow::SSendMessage()
{
}
