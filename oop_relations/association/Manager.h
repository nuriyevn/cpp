#ifndef __MANAGER_H__
#define __MANAGER_H__

#include <iostream>
#include "SwipeCard.h"

using std::cout;
using std::endl;
using std::string;

class SwipeCard;

class Employee
{
public:
	Employee()
		: name(""){}
	Employee(const string& n)
		: name(n){}
	~Employee() {}
	const string& getName(void) const
	{
		return name;
	}
private:
	Employee& operator=(const Employee& rhs){};
	Employee(const Employee& rhs){}
	string name;
};

class Manager : public Employee
{
public:
	Manager();
	Manager(const string& n);
	~Manager();
	void Fire(void);
	double salary;	
	string Logon(SwipeCard* swipeCard);
	void HowIsTheManager(bool Good);
};

class Worker : public Employee
{
};

#endif
