//Windows�û�����֮����ı�Ӧ��ʹ�ô�BOM�� UTF-8��ʽ������������������//
#pragma execution_character_set("utf-8")
#include "MainWindow.h"
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qtextcodec.h>
#include <string>

MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	status = false;
	this->setWindowTitle("Contracts");
	this->setFixedSize(600, 400);//�̶���С
	address_book = new AddressBook();
	//��tablewidget�޷��༭
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	//����˳���ť���˳�����
	connect(ui.pushButton_exit, SIGNAL(clicked()), this, SLOT(close()));
	//��ȡ����
	connect(ui.lineEdit_name, &QLineEdit::textChanged, this, &MainWindow::GetName);
	//��ȡ����
	connect(ui.lineEdit_number, &QLineEdit::textChanged, this, &MainWindow::GetNumber);
	//��ȡ���
	connect(ui.comboBox, &QComboBox::currentTextChanged, this, &MainWindow::GetGroup);
	//����½���ť����ȡ�½�����ϵ����Ϣ
	connect(ui.pushButton_new, &QPushButton::clicked, this, &MainWindow::NewContact);
	//������밴ť����ͨѶ¼���뵽����
	connect(ui.pushButton_input, &QPushButton::clicked, this, &MainWindow::OpenFile);
	//������水ť�����½���ϵ����Ϣ�ļ�����
	connect(ui.pushButton_save, &QPushButton::clicked, this, &MainWindow::SaveFile);
	//������°�ť��������ϵ��
	connect(ui.pushButton_update,&QPushButton::clicked, this, &MainWindow::Update);
	//�������ȡ���ݽ����޸�
	connect(ui.tableWidget, &QTableWidget::itemDoubleClicked, this, &MainWindow::GetItem);
	//���ɾ����ť��ɾ��ѡ�е���ϵ��
	connect(ui.pushButton_delete, &QPushButton::clicked, this, &MainWindow::Delete);
	//��������ť������������
	connect(ui.pushButton_clear, &QPushButton::clicked, this, &MainWindow::Clear);
}

void MainWindow::OpenFile()
{
	parts.clear();
	book_update.clear();
	QString filename = QFileDialog::getOpenFileName(this, "Open Contact Person", ".", tr("Text File (*.txt)"));
	if (filename.isEmpty())
	{
		return;
	}
	file = new QFile(filename);
	if (!file->open(QIODevice::ReadOnly | QIODevice::Text))//end-of-line��������ת��Ϊ'\n'
	{
		QMessageBox::warning(this, tr("����"), tr("���ļ�ʧ��"));
		return;
	}
	else
	{
		if (!file->isReadable())
		{
			QMessageBox::warning(this, tr("����"), tr("���ļ����ɶ�"));
		}
		else
		{
			QTextStream in(file);
			while (true) 
			{
				QString line = in.readLine();
				if (line.isNull())
				{
					break;
				}
				parts = line.split(" ");//���ո����
				int row = ui.tableWidget->rowCount();
				ui.tableWidget->setRowCount(row + 1);
				//����ȡ����ϵ�����ݴ洢���Ա���֮��ĸ��º�ɾ��
				contact_backup.Name = parts[0];
				contact_backup.Number = parts[1];
				contact_backup.Group = parts[2];
				book_update.push_back(contact_backup);
				for (size_t i = 0; i < parts.size(); i++)
				{
					ui.tableWidget->setItem(row, i, new QTableWidgetItem(parts[i].toUtf8().data()));
				}
			}
			file->close();
		}
	}
}


MainWindow::~MainWindow()
{
	delete address_book;
	address_book = NULL;
	delete file;
	file = NULL;
}

void MainWindow::SaveFile()
{
	QString filename = QFileDialog::getSaveFileName(this, "Save Contact Person", ".", tr("Text File (*.txt)"));
	if (filename.isNull())
	{
		return;
	}
	file = new QFile(filename);
	file->open(QIODevice::Append);//���ô򿪷�ʽ
	for (size_t i = 0; i < book.size(); i++)
	{
		file->write(book[i].Name.toUtf8());
		file->write(" ");//��ǰ���ȡ��ʱ���Ӧ���������˿ո�
		file->write(book[i].Number.toUtf8());
		file->write(" ");
		file->write(book[i].Group.toUtf8());
		file->write("\n");
	}
	file->close();
	book.clear();
	book_update.clear();
	address_book->Book.clear();
}

void MainWindow::Update()
{
	QString filename = QFileDialog::getSaveFileName(this, "Update Contact Person", ".", tr("Text File (*.txt)"));
	if (filename.isNull())
	{
		return;
	}
	file = new QFile(filename);
	file->open(QIODevice::WriteOnly);//����д�ķ�ʽ��
	for (size_t i = 0; i < book_update.size(); i++)
	{
		
		file->write(book_update[i].Name.toUtf8());
		file->write(" ");
		file->write(book_update[i].Number.toUtf8());
		file->write(" ");
		file->write(book_update[i].Group.toUtf8());
		file->write("\n");
	}
	file->close();//�����˽��ļ��رգ���Ȼ�޷���д�ɹ�
	//book.clear();
	//book_update.clear();
	//address_book->Book.clear();
}

void MainWindow::Delete()
{
	std::vector<CContact>::iterator iter = book_update.begin();
	iter = book_update.erase(iter + index.row());
}

void MainWindow::GetName()
{
	if (!status)
	{
		contact.Name = ui.lineEdit_name->text();
	}
	else
	{
		contact_backup.Name = ui.lineEdit_name->text();
		book_update[index.row()].Name = contact_backup.Name;
	}
}

void MainWindow::GetNumber()
{
	if (!status)
	{
		contact.Number = ui.lineEdit_number->text();
	}
	else
	{
		contact_backup.Number = ui.lineEdit_number->text();
		book_update[index.row()].Number = contact_backup.Number;
		status = false;
	}
}

void MainWindow::GetGroup()
{
	if (!status)
	{
		contact.Group = ui.comboBox->currentText();
	}
	else
	{
		contact_backup.Group = ui.comboBox->currentText();
		book_update[index.row()].Group = contact_backup.Group;
		status = false;
	}
}

void MainWindow::NewContact()
{
	status = false;
	if (contact.Name.isEmpty() || contact.Group.isEmpty() || contact.Group.isEmpty())
	{
		QMessageBox::warning(this, tr("����"), tr("��û�������κ��˵���Ϣ������������ϵ�����½�"));
	}
	else
	{
		address_book->AddContact(contact.Name, contact.Number, contact.Group);
		book = address_book->Book;
	}
	contact.Name.clear();
	contact.Number.clear();
	contact.Group.clear();
	ui.lineEdit_name->clear();
	ui.lineEdit_number->clear();
	ui.comboBox->setCurrentIndex(0);
}

void MainWindow::GetItem()
{
	status = true;
	QString str;
	index = ui.tableWidget->currentIndex();
	str = ui.tableWidget->item(index.row(), index.column())->text();//���ݵ�ǰ�����кŶ�ȡ����
	if (index.column() == 0)
	{
		ui.lineEdit_name->setText(str);
	}
	if (index.column() == 1)
	{
		ui.lineEdit_number->setText(str);
	}
}

void MainWindow::Clear()
{
	ui.tableWidget->setRowCount(0);
	ui.tableWidget->clearContents();
}
