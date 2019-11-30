#pragma once
#include <QtWidgets/QWidget>
#include "ui_MainWindow.h"
#include "Contact.h"
#include <qdebug.h>
#include "AddressBook.h"
#include <qfile.h>
#include <vector>

class MainWindow : public QWidget
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();

public slots:
	void OpenFile();
	void SaveFile();
	void Update();
	void Delete();

private:
	Ui::MainWindowClass ui;
	CContact contact;
	CContact contact_backup;
	AddressBook *address_book;
	QFile *file;
	std::vector<CContact> book;
	std::vector<CContact> book_update;
	QModelIndex index;//获取表格的当前行列号
	bool status;//用于区分新建联系人和修改联系人
	QStringList parts;
private:
	void GetName();
	void GetNumber();
	void GetGroup();
	void NewContact();
	void GetItem();
	void Clear();

};
