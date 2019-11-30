#include "AddressBook.h"
#include <iostream>
using namespace std;



AddressBook::AddressBook()
{
}


AddressBook::~AddressBook()
{
}

//�����ϵ��
void AddressBook::AddContact(string & name, string & number, string & group)
{
	contact.setContact(name, number, group);
	Book.push_back(contact);
}

//������ϵ��
int AddressBook::Find(string & name, string & number, string & group)
{
	int count = 0;
	for (size_t i = 0; i < Book.size(); i++)
	{
		if (Book[i].PatternMatch(name, number, group))//�������ģ��ƥ��
		{
			cout << Book[i] << endl;
			count++;
		}
	}
	if (count != 0)
	{
		cout << "�ܹ��ҵ�" << count << "����ϵ��" << endl;
		return 0;
	}
	else
	{
		cout << "û���ҵ���ϵ��" << endl;
		return 0;
	}
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

//ɾ����ϵ��
void AddressBook::Delete(string & name, string & number, string & group)
{
	vector<CContact>::iterator iter = Book.begin();
	for (iter; iter != Book.end();)
	{
		if ((*iter).PatternMatch(name, number, group))
		{
			iter = Book.erase(iter);//������һ��������
		}
		else
		{
			iter++;
		}
	}
	return;
}

//����������<�����Ѿ�����
void AddressBook::Sort()//������ð������
{
	CContact temp;
	for (size_t i = 0; i < Book.size() - 1; i++)//���ѭ��������������
	{
		for (size_t j = 0; j < Book.size() - i - 1; j++)//�ڲ�ѭ�����Ƶ�ǰ�˵ıȽϴ���
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

//��������
void AddressBook::SortGroup()
{
	CContact temp;
	for (size_t i = 0; i < Book.size() - 1; i++)//���ѭ��������������
	{
		for (size_t j = 0; j < Book.size() - i - 1; j++)//�ڲ�ѭ�����Ƶ�ǰ�˵ıȽϴ���
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

//�����<<�Ѿ�����
void AddressBook::List()
{
	for (size_t i = 0; i < Book.size(); i++)
	{
		cout << Book[i] << endl;
	}
}

//������ʾ
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
