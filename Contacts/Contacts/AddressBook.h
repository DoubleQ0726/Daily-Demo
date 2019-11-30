#pragma once
#include "Contact.h"
#include <vector>
using namespace std;

class AddressBook
{
public:
	AddressBook();//建立空地址簿
	~AddressBook();//地址簿析构函数，其中必须清空联系人向量Book
	void AddContact(QString &name, QString &number, QString &group);//在向量中增加一个联系人
	CContact operator[](int index);//重载下标运算符

public:
	CContact contact;
	vector<CContact> Book;
	//以CContact类实例化类模板vector形成CContact向量作为存储结构。
	//Book是CContact向量类的一个实例
};

