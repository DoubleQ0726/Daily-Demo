#pragma execution_character_set("utf-8")
#include "MainWindow.h"
#include <qdebug.h>

MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowTitle(tr("客户端"));
	ui.pushButton_send->setEnabled(false);//默认打开时是没有网络连接的，禁止发送
	//新建TCP客户端
	client = new QTcpSocket(this);
	client->abort();//取消原有连接
	//收到服务器端的信号，再进行读取信息
	connect(client, &QTcpSocket::readyRead, this, &MainWindow::ReadData);
	connect(client, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(ReadError(QAbstractSocket::SocketError)));
	//点击连接按钮，请求与服务器连接
	connect(ui.pushButton_connect, &QPushButton::clicked, this, &MainWindow::Connect);
	//点击取消按钮，请求与服务器断开
	connect(ui.pushButton_dis, &QPushButton::clicked, this, &MainWindow::Close);
	connect(client, &QTcpSocket::disconnected, this, [=]() {
		ui.pushButton_connect->show();
	});
	//点击发送按钮，向服务器发送信息
	connect(ui.pushButton_send, &QPushButton::clicked, this, &MainWindow::SendMessage);
}

void MainWindow::Connect()
{
	client->connectToHost(ui.lineEdit_ip->text(), ui.lineEdit_port->text().toInt());//建立TCP连接
	//等待TCP连接成功
	if (client->waitForConnected(1000))//等待一秒，连接成功返回true
	{
		QMessageBox::information(this, "提示", "成功和服务器连接");
		ui.pushButton_connect->hide();//连接成功，按钮就显示成功断开(隐藏连接按钮)
		ui.pushButton_send->setEnabled(true);//发送按钮功能启用
	}
}

MainWindow::~MainWindow()
{
	delete client;
	client = NULL;
}

void MainWindow::Close()
{
	client->disconnectFromHost();//断开TCP连接
	//等待TCP连接失败
	if (client->state() == QAbstractSocket::UnconnectedState || client->waitForDisconnected(1000))
	{
		QMessageBox::information(this, "提示", "断开连接");
		ui.pushButton_connect->show();
		ui.pushButton_send->setEnabled(false);
	}
}

//当错误发生时，首先断开TCP连接，再用QMessageBox提示出errorString，即错误原因
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
	QString data = ui.textEdit_send->toPlainText();//获取文本框的内容
	ui.textEdit_send->clear();
	if (!data.isEmpty())
	{
		//向服务器发送数据
		ui.textEdit_com->append(data);//采用文本追加的方式
		client->write(data.toUtf8());
	}
}


