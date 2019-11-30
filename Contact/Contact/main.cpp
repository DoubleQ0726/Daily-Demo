#include <iostream>
#include <string>
#include <vector>
#include "AddressBook.h"
using namespace std;

int main()
{
	string name, phone, group;//临时字符串
	AddressBook MB;//创建地址簿对象
	string cmd, parameter;//命令及其参数
	while (true)//命令解释循环
	{
		cout << "地址簿练习>>:";//输出提示符
		cin >> cmd;//读入命令
		if (_strcmpi(cmd.c_str(), "exit") == 0)break;//退出
		if (_strcmpi(cmd.c_str(), "help") == 0)
		{
			cout << "[增加联系人]" << "add NAME NUMBER GROUP" << endl;
			cout << "[查找联系人]" << "find NAME NUMBER GROUP" << endl;
			cout << "[删除联系人]" << "delete NAME NUMBER GROUP" << endl;
			cout << "[列举所有联系人]" << "list" << endl;
			cout << "[将地址簿按姓名排序]" << "sort" << endl;
			cout << "[将地址簿按群组排序]" << "sortByGroup" << endl;
			cout << "[列举出某组中的联系人]" << "ListbyGroup GROUP" << endl;
			cout << "[退出程序]" << "exit" << endl;
			continue;
		}
		//add命令格式: addnode [name] [number] [group]。
		//例如 Add John 1234567 friends。 []符号代表参数
		if (_strcmpi(cmd.c_str(), "add") == 0)
		{
			cin >> name >> phone >> group;//获取联系人姓名号码群组
			MB.AddContact(name, phone, group);//映射到地址簿AddContact方法
			continue;
		}
		if (_strcmpi(cmd.c_str(), "find") == 0)
			//find [Name] [Number] [Group] 按名字寻找某一节点
		{
			cin >> name >> phone >> group;
			MB.Find(name, phone, group);
			continue;
		}
		if (_strcmpi(cmd.c_str(), "Delete") == 0)
			//delete [Name][Number][Group]，按姓名删除某一节点
		{
			cin >> name >> phone >> group;
			MB.Delete(name, phone, group);
			continue;
		}
		if (_strcmpi(cmd.c_str(), "List") == 0)//list，节点列表
		{
			MB.List();
			continue;
		}
		if (_strcmpi(cmd.c_str(), "sortbyname") == 0)//sort，节点按姓名升序排列。
		{
			MB.Sort();
			continue;
		}
		if (_strcmpi(cmd.c_str(), "sortbygroup") == 0)//节点按群组升序排列
		{
			MB.SortGroup();
			continue;
		}
		if (_strcmpi(cmd.c_str(), "Listbygroup") == 0)//列出某群组中的联系人
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