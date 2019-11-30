#pragma once
#include <qstring.h>
using namespace std;

class CContact
{
public:
	CContact();
	~CContact();
	CContact(const CContact &contact);//拷贝构造函数
	void setContact(QString &name, QString &number, QString &group);//设定对象的三个成员

public:
	QString Name;
	QString Number;
	QString Group;
};
	

