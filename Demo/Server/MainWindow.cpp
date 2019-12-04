#pragma execution_character_set("utf-8")
#include "MainWindow.h"
#include <qnetworkinterface.h>
#include <qmessagebox.h>

MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowTitle("服务器");
	ui.pushButton_send->setEnabled(false);
	//TCP服务器
	server = new QTcpServer(this);
	bool status = server->listen(QHostAddress::Any, ui.lineEdit_port->text().toInt());//监听所有的ip
	if (status)
	{
		ui.pushButton_send->setEnabled(true);
	}
	currentClient = new QTcpSocket(this);
	QList<QHostAddress> IPaddress = QNetworkInterface::allAddresses();
	for (size_t i = 0; i < IPaddress.size(); i++)
	{
		if (IPaddress.at(i) != QHostAddress::LocalHost && IPaddress.at(i).toIPv4Address())//找到ipv4地址
		{
			ui.lineEdit_ip->setText(IPaddress.at(i).toString());
		}
	}

	//每当有客户端的信号时,服务器作出相应的反应
	connect(server, &QTcpServer::newConnection, this, &MainWindow::NewConnectionSlot);
	//点击发送按钮，向客户端发送消息
	connect(ui.pushButton_send, &QPushButton::clicked, this, &MainWindow::SSendMessage);
	//点击断开按钮，主动与客户端断开连接
	connect(ui.pushButton_dis, &QPushButton::clicked, this, &MainWindow::DisConnect);
}


void MainWindow::NewConnectionSlot()
{
	currentClient = server->nextPendingConnection();//得到一个tcp连接
	tcpClientList.push_back(currentClient);//因为一个服务器可以对应多个客户端，所以都存储起来
	//如果套接字处于连接状态，则用peerAddress()返回已连接的对方的地址
	ui.comboBox->addItem(tr("%1:%2").arg(currentClient->peerAddress().toString().split("::ffff:")[1]).arg(currentClient->peerPort()));
	connect(currentClient, &QTcpSocket::readyRead, this, &MainWindow::SReadData);
	connect(currentClient, &QTcpSocket::disconnected, this, &MainWindow::SClose);
}

void MainWindow::SClose()
{
	for (size_t i = 0; i < tcpClientList.size(); i++)
	{
		if (tcpClientList[i]->state() == QAbstractSocket::UnconnectedState || tcpClientList[i]->waitForDisconnected(1000))
		{
			QMessageBox::information(this, "提示", "与客户端断开连接");
			ui.comboBox->removeItem(ui.comboBox->findText(tr("%1:%2").arg(tcpClientList[i]->peerAddress().toString().split("::ffff:")[1]).arg(tcpClientList[i]->peerPort())));
			tcpClientList[i]->destroyed();
			tcpClientList.removeAt(i);//成功断开就从所有已连接的客户端移除这个
		}
	}
}

//主动和客户端断开连接
void MainWindow::DisConnect()
{
	currentClient->disconnectFromHost();
	currentClient->close();
	currentClient = NULL;
}

void MainWindow::SReadData()
{
	for (size_t i = 0; i < tcpClientList.size(); i++)
	{
		QByteArray buffer = tcpClientList[i]->readAll();
		if (buffer.isEmpty())
		{
			continue;
		}
		//判断发送此次消息的客户端和上一个客户端是不是用一个
		static QString IP, IP_Pre;
		qDebug() << tcpClientList[i]->peerPort() << endl;
		IP = tr("[%1:%2]:").arg(tcpClientList[i]->peerAddress().toString().split("::ffff:")[1]).arg(tcpClientList[i]->peerPort());
		if (IP != IP_Pre)
		{
			ui.textEdit_com->append(IP);//显示发送消息的客户端信息
		}
		ui.textEdit_com->append(buffer);//显示消息内容
		IP_Pre = IP;
	}
}

void MainWindow::SSendMessage()
{
	QString data = ui.textEdit_send->toPlainText();
	ui.textEdit_send->clear();
	if (!data.isEmpty())
	{
		//向指定的连接发送消息
		
		QString clientIP = ui.comboBox->currentText().split(":")[0];
		unsigned int clientPort = ui.comboBox->currentText().split(":")[1].toInt();
		for (size_t i = 0; i < tcpClientList.size(); i++)
		{
			if (tcpClientList[i]->peerAddress().toString().split("::ffff:")[1] == clientIP && tcpClientList[i]->peerPort() == clientPort)
			{
				ui.textEdit_com->append(data);
				tcpClientList[i]->write(data.toUtf8());
				break;
			}
		}
	}
}

