#pragma once
#include "Contact.h"
#include <vector>
using namespace std;

class AddressBook
{
public:
	AddressBook();//�����յ�ַ��
	~AddressBook();//��ַ���������������б��������ϵ������Book
	void AddContact(QString &name, QString &number, QString &group);//������������һ����ϵ��
	CContact operator[](int index);//�����±������

public:
	CContact contact;
	vector<CContact> Book;
	//��CContact��ʵ������ģ��vector�γ�CContact������Ϊ�洢�ṹ��
	//Book��CContact�������һ��ʵ��
};

