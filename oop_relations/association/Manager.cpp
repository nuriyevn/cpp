#include "Manager.h"

Manager::Manager()
	: Employee()
{
}

Manager::Manager(const string& n)
	: Employee(n)
{
}


void Manager::Fire(void)
{
	cout << "Manager " << getName() << " has been fired!! "	 << endl;
}

Manager::~Manager()
{
	Fire();
}

string Manager::Logon(SwipeCard* swipeCard)
{
	return swipeCard->Swipe(this);
}

void Manager::HowIsTheManager(bool Good)
{
	if (Good)
		salary += 5000;
}
