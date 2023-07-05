#pragma once
const std::string strDefaultPaymentCardAccount = "DefaultPaymentCardAccount";
const std::string strDefaultSavingsAccount = "DefaultSavingsAccount";
const std::string strDefaultCashAccount = "DefaultCashAccount";

// Based on AbstractFactory pattern

class Account
{
public:
    Account(std::string logFile = "log.txt") : current(0) {}
	virtual ~Account() 	{}
	int deposit(double amount) ;
	int withdraw(double amount) ;
	void transfer(double amount, Account &a);
	double balance() { return current; }
	int getID() { return ID; }
	virtual string getAccountType() = 0;
	virtual string getAccountName() { return accountName; };
	string getTransactionDate(bool local = true);
	friend ostream& operator<<(ostream& out, Account& a);
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
	Account *createAccount(double amount, string name = strDefaultPaymentCardAccount)
	{
		return new PaymentCardAccount(amount, name);
	}
};

class CashAccountFactory : public Factory
{
public:
	Account* createAccount(double amount, string name = strDefaultCashAccount) 
	{
		return new CashAccount(amount, name);
	}
};

class SavingsAccountFactory : public Factory
{
public:
	Account* createAccount(double amount, string name= strDefaultSavingsAccount)
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

void print_balances(vector<Account*> &av);
void print_account_types(map<int, MapData> &accTypesMap);
void print_available_commands();