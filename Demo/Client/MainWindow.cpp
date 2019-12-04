#pragma execution_character_set("utf-8")
#include "MainWindow.h"
#include <qdebug.h>

MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowTitle(tr("�ͻ���"));
	ui.pushButton_send->setEnabled(false);//Ĭ�ϴ�ʱ��û���������ӵģ���ֹ����
	//�½�TCP�ͻ���
	client = new QTcpSocket(this);
	client->abort();//ȡ��ԭ������
	//�յ��������˵��źţ��ٽ��ж�ȡ��Ϣ
	connect(client, &QTcpSocket::readyRead, this, &MainWindow::ReadData);
	connect(client, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(ReadError(QAbstractSocket::SocketError)));
	//������Ӱ�ť�����������������
	connect(ui.pushButton_connect, &QPushButton::clicked, this, &MainWindow::Connect);
	//���ȡ����ť��������������Ͽ�
	connect(ui.pushButton_dis, &QPushButton::clicked, this, &MainWindow::Close);
	connect(client, &QTcpSocket::disconnected, this, [=]() {
		ui.pushButton_connect->show();
	});
	//������Ͱ�ť���������������Ϣ
	connect(ui.pushButton_send, &QPushButton::clicked, this, &MainWindow::SendMessage);
}

void MainWindow::Connect()
{
	client->connectToHost(ui.lineEdit_ip->text(), ui.lineEdit_port->text().toInt());//����TCP����
	//�ȴ�TCP���ӳɹ�
	if (client->waitForConnected(1000))//�ȴ�һ�룬���ӳɹ�����true
	{
		QMessageBox::information(this, "��ʾ", "�ɹ��ͷ���������");
		ui.pushButton_connect->hide();//���ӳɹ�����ť����ʾ�ɹ��Ͽ�(�������Ӱ�ť)
		ui.pushButton_send->setEnabled(true);//���Ͱ�ť��������
	}
}

MainWindow::~MainWindow()
{
	delete client;
	client = NULL;
}

void MainWindow::Close()
{
	client->disconnectFromHost();//�Ͽ�TCP����
	//�ȴ�TCP����ʧ��
	if (client->state() == QAbstractSocket::UnconnectedState || client->waitForDisconnected(1000))
	{
		QMessageBox::information(this, "��ʾ", "�Ͽ�����");
		ui.pushButton_connect->show();
		ui.pushButton_send->setEnabled(false);
	}
}

//��������ʱ�����ȶϿ�TCP���ӣ�����QMessageBox��ʾ��errorString��������ԭ��
void MainWindow::ReadError(QAbstractSocket::SocketError)
{
	client->disconnectFromHost();
	QMessageBox msgBox;
	msgBox.setText(tr("failed to connect server because %1").arg(client->errorString()));
}

void MainWindow::ReadData()
{
	QByteArray buffer = client->readAll();
	if (!buffer.isEmpty())
	{
		ui.textEdit_com->append(buffer);
	}
}

void MainWindow::SendMessage()
{
	QString data = ui.textEdit_send->toPlainText();//��ȡ�ı��������
	ui.textEdit_send->clear();
	if (!data.isEmpty())
	{
		//���������������
		ui.textEdit_com->append(data);//�����ı�׷�ӵķ�ʽ
		client->write(data.toUtf8());
	}
}


