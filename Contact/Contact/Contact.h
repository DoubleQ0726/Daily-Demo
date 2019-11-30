#pragma once
#include <string>
using namespace std;

//�ж��ַ���source�Ƿ�ƥ��pattern,����˵�ַ���source��pattern�����ļ����е�ĳ����Ա
	bool match(string& pattern, string& source);//�ַ���ƥ��
class CContact
{
public:
	CContact();
	CContact(string &name, string &number, string &group);//ʹ��Name,Number,Group������ϵ�˶���
	CContact(const CContact &contact);//�������캯��
	bool operator<(CContact &contact);//����<����������㷨sortʹ��,����������
	CContact& operator=(const CContact &contact);//���ظ�ֵ�����
	friend ostream& operator<<(ostream &ost, CContact contact);//������Ԫ�������������<<
	friend istream& operator>>(istream &ist, CContact contact);//������Ԫ�������������>>
	virtual ~CContact();//��������
	//�����������������㷨sortʹ��
	friend bool pr(const CContact &contact1, const CContact &contact2);
	string getContact();//��ȡ����ĳ�Ա
	void setContact(string &name, string &number, string &group);//�趨�����������Ա
	bool PatternMatch(string &name, string &number, string &group);//�ж��������Ƿ�ƥ����������

private:
	string Name;
	string Number;
	string Group;
};
	

