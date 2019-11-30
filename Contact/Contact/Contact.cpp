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

//��Ҫ���ھ�����ϵ�˵Ĳ��Һ�ɾ��������ϵ��
bool CContact::PatternMatch(string & name, string & number, string & group)
{
	bool status1 = false;//ÿ���ֶε�״ֵ̬��������ƥ������Ϊ�棬��֮Ϊ��
	bool status2 = false;
	bool status3 = false;
	//��nameΪ�����ж������ֶ���ԭ�ֶ�ģ��ƥ��
	for (size_t i = 0; i < name.size(); i++)
	{
		if (name.c_str()[i] == '*')//���ַ�����ͨ�����ʾ��ƥ��
		{
			status1 = true;
			break;
		}
		if (name[i] == Name[i])//�ٽ���ÿ���ַ���ƥ���ж�
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
	if (status1 && status2 && status3)//�������ֶε�״̬��Ϊ��
	{
		return true;
	}
	else
	{
		return false;
	}
}

//�ж������ַ�����ԭ�ַ����Ƿ���ȫƥ�䣬��Ҫ���ں�����ϵ�˲����������
bool match(string & pattern, string & source)
{
	int i;
	if (pattern.size() != source.size())//�����ַ����Ȳ�ͬ����ƥ��
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

//����������Ϊ�����������������ʹ��
bool pr(const CContact & contact1, const CContact & contact2)
{
	if (contact1.Group < contact2.Group)
	{
		return true;
	}
	return false;
}


