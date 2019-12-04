#pragma execution_character_set("utf-8")
#include "MainWindow.h"
#include <qnetworkinterface.h>
#include <qmessagebox.h>

MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowTitle("������");
	ui.pushButton_send->setEnabled(false);
	//TCP������
	server = new QTcpServer(this);
	bool status = server->listen(QHostAddress::Any, ui.lineEdit_port->text().toInt());//�������е�ip
	if (status)
	{
		ui.pushButton_send->setEnabled(true);
	}
	currentClient = new QTcpSocket(this);
	QList<QHostAddress> IPaddress = QNetworkInterface::allAddresses();
	for (size_t i = 0; i < IPaddress.size(); i++)
	{
		if (IPaddress.at(i) != QHostAddress::LocalHost && IPaddress.at(i).toIPv4Address())//�ҵ�ipv4��ַ
		{
			ui.lineEdit_ip->setText(IPaddress.at(i).toString());
		}
	}

	//ÿ���пͻ��˵��ź�ʱ,������������Ӧ�ķ�Ӧ
	connect(server, &QTcpServer::newConnection, this, &MainWindow::NewConnectionSlot);
	//������Ͱ�ť����ͻ��˷�����Ϣ
	connect(ui.pushButton_send, &QPushButton::clicked, this, &MainWindow::SSendMessage);
	//����Ͽ���ť��������ͻ��˶Ͽ�����
	connect(ui.pushButton_dis, &QPushButton::clicked, this, &MainWindow::DisConnect);
}


void MainWindow::NewConnectionSlot()
{
	currentClient = server->nextPendingConnection();//�õ�һ��tcp����
	tcpClientList.push_back(currentClient);//��Ϊһ�����������Զ�Ӧ����ͻ��ˣ����Զ��洢����
	//����׽��ִ�������״̬������peerAddress()���������ӵĶԷ��ĵ�ַ
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
			QMessageBox::information(this, "��ʾ", "��ͻ��˶Ͽ�����");
			ui.comboBox->removeItem(ui.comboBox->findText(tr("%1:%2").arg(tcpClientList[i]->peerAddress().toString().split("::ffff:")[1]).arg(tcpClientList[i]->peerPort())));
			tcpClientList[i]->destroyed();
			tcpClientList.removeAt(i);//�ɹ��Ͽ��ʹ����������ӵĿͻ����Ƴ����
		}
	}
}

//�����Ϳͻ��˶Ͽ�����
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
		//�жϷ��ʹ˴���Ϣ�Ŀͻ��˺���һ���ͻ����ǲ�����һ��
		static QString IP, IP_Pre;
		qDebug() << tcpClientList[i]->peerPort() << endl;
		IP = tr("[%1:%2]:").arg(tcpClientList[i]->peerAddress().toString().split("::ffff:")[1]).arg(tcpClientList[i]->peerPort());
		if (IP != IP_Pre)
		{
			ui.textEdit_com->append(IP);//��ʾ������Ϣ�Ŀͻ�����Ϣ
		}
		ui.textEdit_com->append(buffer);//��ʾ��Ϣ����
		IP_Pre = IP;
	}
}

void MainWindow::SSendMessage()
{
	QString data = ui.textEdit_send->toPlainText();
	ui.textEdit_send->clear();
	if (!data.isEmpty())
	{
		//��ָ�������ӷ�����Ϣ
		
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

