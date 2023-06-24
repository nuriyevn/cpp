#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <ctime>
#include <map>
#include "logger.h"

using namespace std;

static Logger *logger;

class Account
{
public:
	Account(std::string logFile = "log.txt")
	{
		current = 0;
	}
	virtual ~Account()
	{
	}
	int deposit(double amount) 
	{
		//logger->writeToLogFile("")
		if (current + amount > current)
		{ 
			current += amount;
			return 1;
		} 
		else
		{
			cout << "Deposit operation failed." << endl;
			return 0;
		}
	}
	int debit(double amount) 
	{ 
		if (current - amount >= 0.0)
		{
			current -= amount;
			return 1;
		}
		else
		{
			cout << "Not enough funds." << endl;
			return 0;
		}
	};
	void transfer(double amount, Account &a)
	{
		if (this->debit(amount))
		{
			if (!a.deposit(amount))
			{
				cout << "Error while transferring funds." << endl;		
				return;
			}
		}
		else {
			cout << "Error while transferring funds." << endl;
			//logger->writeToLogFile()
			return;
		}
		cout << "Transaction date: " << getTransactionDate(true) << endl;
		//logger->writeToLogFile()
	}
	double balance() { return current; }

	int getID() { return ID; }
	virtual string getAccountType() = 0;
	virtual string getAccountName() 
	{
		return accountName;
	};
	string getTransactionDate(bool local = true)
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
	friend ostream& operator<<(const ostream& out, Account& a)
	{
		out << 
	}
protected:
	double current;
	string accountType;
	string accountName;
private:
	int ID;
};

class CashAccount : public Account
{
public:
	CashAccount(double amount, string accName)
	{
		current = amount;
		accountType = "CashAccount";
		accountName = accName;
	}
	string getAccountType()				
	{
		return accountType;
	}
};

class PaymentCardAccount : public Account
{
public:
	PaymentCardAccount(double amount, string accName, 
						string num="", string valid="", 
						string c="", string holder="")
		: number(num), validTill(valid), cvc(c), holderName(holder)
	{
		current = amount;		
		accountName = accName;
		accountType = "PaymentCard";	
	}
	string getAccountType()
	{
		return accountType;
	}

private:
	string number;
	string validTill;
	string cvc;
	string holderName; 
};


class SavingsAccount : public Account
{
public:
	SavingsAccount(double amount, string accName) 
	{
		current = amount;
		accountName = accName;
		accountType = "SavingsAccount";
	}
	string getAccountType()
	{
		return accountType;
	}
};

class Factory
{
public:
	virtual Account* createAccount(double amount, string name) = 0;
	virtual ~Factory() {}
};

class PaymentCardAccountFactory : public Factory
{
public:
	Account *createAccount(double amount, string name="DefaultPaymentCardAccount")
	{
		return new PaymentCardAccount(amount, name);
	}
};

class CashAccountFactory : public Factory
{
public:
	Account* createAccount(double amount, string name = "DefaultCashAccount") 
	{
		return new CashAccount(amount, name);
	}
};

class SavingsAccountFactory : public Factory
{
public:
	Account* createAccount(double amount, string name="DefaultSavingsAccount")
	{
		return new SavingsAccount(amount, name);	
	}		
};
struct MapData
{   
    string name;
    Factory* factoryPtr;
    MapData(string n, Factory *f) : name(n), factoryPtr(f) {}
};


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


int main()
{
	Logger *logger = Logger::Instance();
	logger->openLogFile("program.log");
	cout << "test " << endl;
	CashAccountFactory *cash_account_factory = new CashAccountFactory;
	PaymentCardAccountFactory *payment_card_account_factory = new PaymentCardAccountFactory;
	SavingsAccountFactory *savings_account_factory = new SavingsAccountFactory;

	std::map<int, MapData> accountTypesMap = {
        {0, MapData("CashAccount", cash_account_factory)},
        {1, MapData("PaymentCardAccount", payment_card_account_factory)},
        {2, MapData("SavingsAccount", savings_account_factory)}
    };

	vector<Account*> av;
	vector<Account*>::iterator it;

	av.push_back(cash_account_factory->createAccount(100));
	av.push_back(payment_card_account_factory->createAccount(200));
	av.push_back(savings_account_factory->createAccount(1000));
	av.push_back(cash_account_factory->createAccount(200, "Secondary Cash"));
	av.push_back(payment_card_account_factory->createAccount(650, "Secondary Payment Card"));
	av.push_back(savings_account_factory->createAccount(950, "Secondary Savings"));

	//print_balances(av);

	int cmd = 0;
	print_available_commands();
	
	while (cin >> cmd)
	{
		bool terminate = false;
		switch (cmd)
		{
			case 3:
				{	
					print_balances(av);
					break;
				}
			case 2:
				{
					cout << "Please select the type of account:" << endl;
					print_account_types(accountTypesMap);						
					int type; string name; double initial_balance = 0.0;
					cin >> type;
					cout << "Please select the name of an account: " << endl;
					cin.ignore();
					getline(cin, name);
					map<int, MapData>::iterator it = accountTypesMap.find(type);
					cout << "PLease intput initial balaances";
					cin >> initial_balance;
					av.push_back(it->second.factoryPtr->createAccount(initial_balance, name));		
					
					break;
				}	
			case 1:
				{
					int from;
					int to;
					double amount;
					print_balances(av);
					cout << "From: " << endl;
					cin >> from;
					cout << "To: " << endl;
					cin >> to;
					cout << "Amount: " << endl;
					cin >> amount;
					if (from < av.size() && from >= 0 && to < av.size() && to >= 0)
					{
						av[from]->transfer(amount, *av[to]);
						print_balances(av);
					}
					break;
				}
			case 0:
				terminate = true;				
				break;
			default:	
				cout << "Enter proper command" << endl;
				break;
		}
		if (terminate)
			break;
		print_available_commands();
	}	

	logger->closeLogFile();
	return 0;
}



