#include <iostream>
#include <string>
#include <vector>
#include "AddressBook.h"
using namespace std;

int main()
{
	string name, phone, group;//��ʱ�ַ���
	AddressBook MB;//������ַ������
	string cmd, parameter;//��������
	while (true)//�������ѭ��
	{
		cout << "��ַ����ϰ>>:";//�����ʾ��
		cin >> cmd;//��������
		if (_strcmpi(cmd.c_str(), "exit") == 0)break;//�˳�
		if (_strcmpi(cmd.c_str(), "help") == 0)
		{
			cout << "[������ϵ��]" << "add NAME NUMBER GROUP" << endl;
			cout << "[������ϵ��]" << "find NAME NUMBER GROUP" << endl;
			cout << "[ɾ����ϵ��]" << "delete NAME NUMBER GROUP" << endl;
			cout << "[�о�������ϵ��]" << "list" << endl;
			cout << "[����ַ������������]" << "sort" << endl;
			cout << "[����ַ����Ⱥ������]" << "sortByGroup" << endl;
			cout << "[�оٳ�ĳ���е���ϵ��]" << "ListbyGroup GROUP" << endl;
			cout << "[�˳�����]" << "exit" << endl;
			continue;
		}
		//add�����ʽ: addnode [name] [number] [group]��
		//���� Add John 1234567 friends�� []���Ŵ������
		if (_strcmpi(cmd.c_str(), "add") == 0)
		{
			cin >> name >> phone >> group;//��ȡ��ϵ����������Ⱥ��
			MB.AddContact(name, phone, group);//ӳ�䵽��ַ��AddContact����
			continue;
		}
		if (_strcmpi(cmd.c_str(), "find") == 0)
			//find [Name] [Number] [Group] ������Ѱ��ĳһ�ڵ�
		{
			cin >> name >> phone >> group;
			MB.Find(name, phone, group);
			continue;
		}
		if (_strcmpi(cmd.c_str(), "Delete") == 0)
			//delete [Name][Number][Group]��������ɾ��ĳһ�ڵ�
		{
			cin >> name >> phone >> group;
			MB.Delete(name, phone, group);
			continue;
		}
		if (_strcmpi(cmd.c_str(), "List") == 0)//list���ڵ��б�
		{
			MB.List();
			continue;
		}
		if (_strcmpi(cmd.c_str(), "sortbyname") == 0)//sort���ڵ㰴�����������С�
		{
			MB.Sort();
			continue;
		}
		if (_strcmpi(cmd.c_str(), "sortbygroup") == 0)//�ڵ㰴Ⱥ����������
		{
			MB.SortGroup();
			continue;
		}
		if (_strcmpi(cmd.c_str(), "Listbygroup") == 0)//�г�ĳȺ���е���ϵ��
		{
			cin >> parameter;
			MB.ListGroup(parameter);
			continue;
		}
		cout << "Illeagle command!" << endl;
		cin.clear();
	}
	system("pause");
	return 0;
}