#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <ctime>
#include <map>
#include "logger.h"
#include "homeacc.hpp"

using namespace std;

static Logger *logger;

int Account::deposit(double amount) 
{
	//logger->writeToLogFile("")
	if (amount < 0.0)
		throw std::invalid_argument("amount is invalid");
	
	if (current + amount >= current)
	{ 
		current += amount;
		return 1;
	} 
	else
	{
		cout << "Deposit operation failed." << endl;
		throw std::runtime_error("Deposit operation failed.");
		return 0;
	}
}
int Account::withdraw(double amount) 
{ 
	if (amount < 0.0)
		throw std::invalid_argument("amount is invalid");
	
	double result = current - amount;
	if (result >= 0.0 && result < current)
	{
		current -= amount;
		return 1;
	}
	else
	{
		cout << "Not enough funds." << endl;
		throw std::runtime_error("Not enough funds!");
		return 0;
	}
};
void Account::transfer(double amount, Account &a)
{
	if (amount < 0.0)
		throw std::invalid_argument("amount is invalid");
	double fromBalance = this->balance();
	double toBalance = a.balance();

	this->withdraw(amount);
	if (!a.deposit(amount))
	{
		cout << "Error while transferring funds." << endl;		
		return;
	}
	else
	{
		
	}
	
	cout << "Transaction date: " << getTransactionDate(true) << endl;
	//logger->writeToLogFile()
}

string Account::getTransactionDate(bool local)
{
	time_t now = time(0);
	char *dt = NULL;
	if (local) 
	{
		dt = ctime(&now);
	}
	else
	{
		tm *gmtm = gmtime(&now);
		dt = asctime(gmtm);
	}
	return string(dt);
}
ostream& operator<<(ostream& out, Account& a)
{
	out << "Account Type = " << a.accountType << "; Account Name = " << a.accountName << "; Current Balance = " << a.current << endl;
	return out;
}

void print_balances(vector<Account*> &av)
{	
	for (int i =0; i < av.size(); i++)	
		cout << i << ": " << av[i]->getAccountName() << '<' 
			 << av[i]->getAccountType() << '>' << " = "
			 << av[i]->balance() << endl;
}

void print_account_types(map<int, MapData> &accTypesMap)
{
	for (auto it = accTypesMap.begin(); it != accTypesMap.end(); ++it)
	{
		cout << it->first << " : " << it->second.name<< endl;
	}		
}

void print_available_commands()
{
	cout << "Enter command: " << endl 
		 << "3: list all accounts with balances" << endl
		 << "2: create/initialize accounts" << endl
		 << "1: transfer funds" << endl
		 << "0: terminate program" << endl;	
}

