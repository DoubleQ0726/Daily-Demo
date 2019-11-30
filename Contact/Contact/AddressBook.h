#pragma once
#include "Contact.h"
#include <vector>
using namespace std;

class AddressBook
{
public:
	AddressBook();//�����յ�ַ��
	~AddressBook();//��ַ���������������б��������ϵ������Book
	void AddContact(string &name, string &number, string &group);//������������һ����ϵ��
	int Find(string &name, string &number, string &group);//Ѱ����ϵ��
	CContact operator[](int index);//�����±������
	void Delete(string &name, string &number, string &group);
	//������ɾ����ϵ�ˣ�����ɾ�������������û��ɾ���κ��ˣ�����0
	void Sort();//����������Book��
	void SortGroup();//��Ⱥ������Book;
	void List();//���Book��������ϵ�ˡ�
	void ListGroup(string& group);//���ĳ����е�������ϵ��

private:
	CContact contact;
	vector<CContact> Book;
	//��CContact��ʵ������ģ��vector�γ�CContact������Ϊ�洢�ṹ��
	//Book��CContact�������һ��ʵ��
};

