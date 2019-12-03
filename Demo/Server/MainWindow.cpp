#include "MainWindow.h"
#include <qnetworkinterface.h>

MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowTitle(QStringLiteral("服务器"));
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

	//每当有客户端连接信号,服务器作出反应
	connect(server, &QTcpServer::newConnection, this, &MainWindow::NewConnectionSlot);
}


void MainWindow::NewConnectionSlot()
{
	currentClient = server->nextPendingConnection();//得到一个tcp连接
	tcpClientList.push_back(currentClient);//因为一个服务器可以对应多个客户端，所以都存储起来
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
