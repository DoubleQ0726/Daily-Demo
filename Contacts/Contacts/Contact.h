#pragma once
#include <qstring.h>
using namespace std;

class CContact
{
public:
	CContact();
	~CContact();
	CContact(const CContact &contact);//�������캯��
	void setContact(QString &name, QString &number, QString &group);//�趨�����������Ա

public:
	QString Name;
	QString Number;
	QString Group;
};
	

