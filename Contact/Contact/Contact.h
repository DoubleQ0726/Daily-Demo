#pragma once
#include <string>
using namespace std;

//判断字符串source是否匹配pattern,或者说字符串source是pattern所表达的集合中的某个成员
	bool match(string& pattern, string& source);//字符串匹配
class CContact
{
public:
	CContact();
	CContact(string &name, string &number, string &group);//使用Name,Number,Group创建联系人对象
	CContact(const CContact &contact);//拷贝构造函数
	bool operator<(CContact &contact);//重载<运算符，供算法sort使用,按姓名排序
	CContact& operator=(const CContact &contact);//重载赋值运算符
	friend ostream& operator<<(ostream &ost, CContact contact);//利用友元函数重载运算符<<
	friend istream& operator>>(istream &ist, CContact contact);//利用友元函数重载运算符>>
	virtual ~CContact();//析构函数
	//定义组排序函数，供算法sort使用
	friend bool pr(const CContact &contact1, const CContact &contact2);
	string getContact();//获取对象的成员
	void setContact(string &name, string &number, string &group);//设定对象的三个成员
	bool PatternMatch(string &name, string &number, string &group);//判定本对象是否匹配搜索条件

private:
	string Name;
	string Number;
	string Group;
};
	

