#pragma once
#include "Contact.h"
#include <vector>
using namespace std;

class AddressBook
{
public:
	AddressBook();//建立空地址簿
	~AddressBook();//地址簿析构函数，其中必须清空联系人向量Book
	void AddContact(string &name, string &number, string &group);//在向量中增加一个联系人
	int Find(string &name, string &number, string &group);//寻找联系人
	CContact operator[](int index);//重载下标运算符
	void Delete(string &name, string &number, string &group);
	//按条件删除联系人，返回删除的人数。如果没有删除任何人，返回0
	void Sort();//按姓名排序Book；
	void SortGroup();//按群组排序Book;
	void List();//输出Book中所有联系人。
	void ListGroup(string& group);//输出某组别中的所有联系人

private:
	CContact contact;
	vector<CContact> Book;
	//以CContact类实例化类模板vector形成CContact向量作为存储结构。
	//Book是CContact向量类的一个实例
};

