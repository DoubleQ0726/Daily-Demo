#include "Contact.h"



CContact::CContact()
{
}

CContact::CContact(string & name, string & number, string & group)
{
	Name = name;
	Number = number;
	Group = group;
}

CContact::CContact(const CContact & contact)
{
	Name = contact.Name;
	Number = contact.Number;
	Group = contact.Group;
}

bool CContact::operator<(CContact & contact)
{
	if (Name < contact.Name)
	{
		return true;
	}
	return false;
}

CContact & CContact::operator=(const CContact & contact)
{
	Name = contact.Name;
	Number = contact.Number;
	Group = contact.Group;
	return *this;
}


CContact::~CContact()
{
}


string CContact::getContact()
{

	return Group;
}

void CContact::setContact(string & name, string & number, string & group)
{
	Name = name;
	Number = number;
	Group = group;
}

//主要用于具体联系人的查找和删除具体联系人
bool CContact::PatternMatch(string & name, string & number, string & group)
{
	bool status1 = false;//每个字段的状态值，当符合匹配条件为真，反之为假
	bool status2 = false;
	bool status3 = false;
	//以name为例，判断输入字段与原字段模糊匹配
	for (size_t i = 0; i < name.size(); i++)
	{
		if (name.c_str()[i] == '*')//当字符遇到通配符表示以匹配
		{
			status1 = true;
			break;
		}
		if (name[i] == Name[i])//再进行每个字符的匹配判断
		{
			status1 = true;
		}
		else
		{
			status1 = false;
			break;
		}
	}
	for (size_t i = 0; i < number.size(); i++)
	{
		if (number.c_str()[i] == '*')
		{
			status2 = true;
			break;
		}
		if (number[i] == Number[i])
		{
			status2 = true;
		}
		else
		{
			status2 = false;
			break;
		}
	}
	for (size_t i = 0; i < group.size(); i++)
	{
		if (group.c_str()[i] == '*')
		{
			status3 = true;
			break;
		}
		if (group[i] == Group[i])
		{
			status3 = true;
		}
		else
		{
			status3 = false;
			break;
		}
	}
	if (status1 && status2 && status3)//当三个字段的状态都为真
	{
		return true;
	}
	else
	{
		return false;
	}
}

//判断输入字符串和原字符串是否完全匹配，主要用于后续联系人簿按分组查找
bool match(string & pattern, string & source)
{
	int i;
	if (pattern.size() != source.size())//两个字符长度不同，则不匹配
	{
		return false;
	}
	else
	{
		for (i = 0; i < pattern.size(); i++)
		{
			if (pattern[i] != source[i])
			{
				break;
			}
		}
		if (i == pattern.size())
		{
			return true;
		}
	}
	return false;
}

ostream & operator<<(ostream & ost, CContact contact)
{
	ost << contact.Name << " ";
	ost << contact.Number << " ";
	ost << contact.Group << " ";
	return ost;
}

istream & operator>>(istream & ist, CContact contact)
{
	ist >> contact.Name;
	ist >> contact.Number;
	ist >> contact.Group;
	return ist;
}

//定义组排序，为后面利用组进行排序使用
bool pr(const CContact & contact1, const CContact & contact2)
{
	if (contact1.Group < contact2.Group)
	{
		return true;
	}
	return false;
}


