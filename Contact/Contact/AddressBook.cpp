#include "AddressBook.h"
#include <iostream>
using namespace std;



AddressBook::AddressBook()
{
}


AddressBook::~AddressBook()
{
}

//添加联系人
void AddressBook::AddContact(string & name, string & number, string & group)
{
	contact.setContact(name, number, group);
	Book.push_back(contact);
}

//查找联系人
int AddressBook::Find(string & name, string & number, string & group)
{
	int count = 0;
	for (size_t i = 0; i < Book.size(); i++)
	{
		if (Book[i].PatternMatch(name, number, group))//如果符合模糊匹配
		{
			cout << Book[i] << endl;
			count++;
		}
	}
	if (count != 0)
	{
		cout << "总共找到" << count << "名联系人" << endl;
		return 0;
	}
	else
	{
		cout << "没有找到联系人" << endl;
		return 0;
	}
}

CContact AddressBook::operator[](int index)
{
	if (index >= Book.size() || index < 0)
	{
		cout << "索引值无效" << endl;
		exit(1);
	}
	else
	{
		return Book[index];
	}
}

//删除联系人
void AddressBook::Delete(string & name, string & number, string & group)
{
	vector<CContact>::iterator iter = Book.begin();
	for (iter; iter != Book.end();)
	{
		if ((*iter).PatternMatch(name, number, group))
		{
			iter = Book.erase(iter);//返回下一个迭代器
		}
		else
		{
			iter++;
		}
	}
	return;
}

//按名字排序，<符号已经重载
void AddressBook::Sort()//采用了冒泡排序
{
	CContact temp;
	for (size_t i = 0; i < Book.size() - 1; i++)//外层循环控制排序趟数
	{
		for (size_t j = 0; j < Book.size() - i - 1; j++)//内层循环控制当前趟的比较次数
		{
			if (Book[j + 1] < Book[j])
			{
				temp = Book[j];
				Book[j] = Book[j + 1];
				Book[j + 1] = temp;
			}
		}
	}
}

//按组排序
void AddressBook::SortGroup()
{
	CContact temp;
	for (size_t i = 0; i < Book.size() - 1; i++)//外层循环控制排序趟数
	{
		for (size_t j = 0; j < Book.size() - i - 1; j++)//内层循环控制当前趟的比较次数
		{
			if (pr(Book[j + 1], Book[j]))
			{
				temp = Book[j];
				Book[j] = Book[j + 1];
				Book[j + 1] = temp;
			}
		}
	}
}

//输出，<<已经重载
void AddressBook::List()
{
	for (size_t i = 0; i < Book.size(); i++)
	{
		cout << Book[i] << endl;
	}
}

//按组显示
void AddressBook::ListGroup(string & group)
{
	for (size_t i = 0; i < Book.size(); i++)
	{
		if (match(Book[i].getContact(), group))
		{
			cout << Book[i] << endl;
		}
	}
}
