#include "Contact.h"



CContact::CContact()
{
}

CContact::CContact(const CContact & contact)
{
	Name = contact.Name;
	Number = contact.Number;
	Group = contact.Group;
}

CContact::~CContact()
{
}

void CContact::setContact(QString & name, QString & number, QString & group)
{
	Name = name;
	Number = number;
	Group = group;
}

