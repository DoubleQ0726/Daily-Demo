#include "AddressBook.h"
#include <qdebug.h>
#include <iostream>
using namespace std;



AddressBook::AddressBook()
{
}


AddressBook::~AddressBook()
{
}

//�����ϵ��
void AddressBook::AddContact(QString & name, QString & number, QString & group)
{
	contact.setContact(name, number, group);
	Book.push_back(contact);
}

CContact AddressBook::operator[](int index)
{
	if (index >= Book.size() || index < 0)
	{
		cout << "����ֵ��Ч" << endl;
		exit(1);
	}
	else
	{
		return Book[index];
	}
}