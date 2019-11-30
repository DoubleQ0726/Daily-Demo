//Windows用户保存之后的文本应该使用带BOM的 UTF-8格式，否则会出现中文乱码//
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
	this->setFixedSize(600, 400);//固定大小
	address_book = new AddressBook();
	//让tablewidget无法编辑
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	//点击退出按钮，退出程序
	connect(ui.pushButton_exit, SIGNAL(clicked()), this, SLOT(close()));
	//获取姓名
	connect(ui.lineEdit_name, &QLineEdit::textChanged, this, &MainWindow::GetName);
	//获取号码
	connect(ui.lineEdit_number, &QLineEdit::textChanged, this, &MainWindow::GetNumber);
	//获取组别
	connect(ui.comboBox, &QComboBox::currentTextChanged, this, &MainWindow::GetGroup);
	//点击新建按钮，获取新建的联系人信息
	connect(ui.pushButton_new, &QPushButton::clicked, this, &MainWindow::NewContact);
	//点击载入按钮，将通讯录载入到界面
	connect(ui.pushButton_input, &QPushButton::clicked, this, &MainWindow::OpenFile);
	//点击保存按钮，将新建联系人信息文件保存
	connect(ui.pushButton_save, &QPushButton::clicked, this, &MainWindow::SaveFile);
	//点击更新按钮，更新联系人
	connect(ui.pushButton_update,&QPushButton::clicked, this, &MainWindow::Update);
	//点击表格获取数据进行修改
	connect(ui.tableWidget, &QTableWidget::itemDoubleClicked, this, &MainWindow::GetItem);
	//点击删除按钮，删除选中的联系人
	connect(ui.pushButton_delete, &QPushButton::clicked, this, &MainWindow::Delete);
	//点击清除按钮，清除表格内容
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
	if (!file->open(QIODevice::ReadOnly | QIODevice::Text))//end-of-line结束符被转译为'\n'
	{
		QMessageBox::warning(this, tr("错误"), tr("打开文件失败"));
		return;
	}
	else
	{
		if (!file->isReadable())
		{
			QMessageBox::warning(this, tr("错误"), tr("该文件不可读"));
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
				parts = line.split(" ");//将空格忽略
				int row = ui.tableWidget->rowCount();
				ui.tableWidget->setRowCount(row + 1);
				//将读取的联系人数据存储，以便于之后的更新和删除
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
	file->open(QIODevice::Append);//设置打开方式
	for (size_t i = 0; i < book.size(); i++)
	{
		file->write(book[i].Name.toUtf8());
		file->write(" ");//与前面读取的时候对应起来，加了空格
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
	file->open(QIODevice::WriteOnly);//以重写的方式打开
	for (size_t i = 0; i < book_update.size(); i++)
	{
		
		file->write(book_update[i].Name.toUtf8());
		file->write(" ");
		file->write(book_update[i].Number.toUtf8());
		file->write(" ");
		file->write(book_update[i].Group.toUtf8());
		file->write("\n");
	}
	file->close();//别忘了将文件关闭，不然无法读写成功
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
		QMessageBox::warning(this, tr("错误"), tr("还没有输入任何人的信息！请先输入联系人再新建"));
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
	str = ui.tableWidget->item(index.row(), index.column())->text();//根据当前的行列号读取内容
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
