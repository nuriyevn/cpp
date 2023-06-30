#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "logger.h"
#include "homeacc.hpp"

const double ABS_ERROR = 1e-12;
// -------------------------------------------- CashAccountFactoryTestFixture
class  CashAccountFactoryTestFixture : public testing::Test
{
public:
    void SetUp() override;
	void TearDown() override;
protected:
    CashAccountFactory *cash_account_factory;
	Account *cash_account;
	double abs_error;
};

void CashAccountFactoryTestFixture::SetUp()
{
    //std::cout << "AccountTestFixture::SetUp() is called\n";
    cash_account_factory = new CashAccountFactory;
    cash_account = cash_account_factory->createAccount(0.0);
	abs_error = ABS_ERROR;
}
void CashAccountFactoryTestFixture::TearDown()
{
	delete cash_account;
	delete cash_account_factory;
}

TEST_F(CashAccountFactoryTestFixture, CreateAccountWithZeroAmount)
{
    double initialBalance = 0.0;
    cash_account->deposit(initialBalance);
    ASSERT_DOUBLE_EQ(initialBalance, cash_account->balance());
}

TEST_F(CashAccountFactoryTestFixture, CreateAccountWith1500Amount)
{
    double initialBalance = 1500.0;
	cash_account->deposit(initialBalance);
    ASSERT_DOUBLE_EQ(initialBalance, cash_account->balance());
}

TEST_F(CashAccountFactoryTestFixture, CreateAccountWithDefaultName)
{
	ASSERT_EQ(strDefaultCashAccount, cash_account->getAccountName());
}

TEST(CashAccountFactoryTestSuite, CreateAccountWithCustomName)
{
	std::string account_name("MyWallet");
	CashAccountFactory *cash_account_factory = new CashAccountFactory;
	Account *cash_account = cash_account_factory->createAccount(400.0, account_name);
	ASSERT_EQ(account_name, cash_account->getAccountName());
	delete cash_account;
	delete cash_account_factory;
}

TEST_F(CashAccountFactoryTestFixture, CreateAccountDepoAndWithdraw)
{
    // Arrange
    double initialBalance = 1500.0;
    // ACT
    cash_account->deposit(initialBalance);
    // ASSERT 
    ASSERT_NEAR(initialBalance, cash_account->balance(), abs_error);
	// More Act
	cash_account->withdraw(initialBalance);
	// More Assert
	ASSERT_NEAR(0.0, cash_account->balance(), abs_error);
}

TEST_F(CashAccountFactoryTestFixture, CreateAccountDepoAndWithdraw2)
{
    double initialBalance = 1500.0;
	double withdrawAmount = 750.51;
    cash_account->deposit(initialBalance);
    ASSERT_NEAR(initialBalance, cash_account->balance(), abs_error);
	cash_account->withdraw(withdrawAmount);
	ASSERT_NEAR(749.49, cash_account->balance(), abs_error);
	cash_account->withdraw(749.49);
	ASSERT_NEAR(double(0.0), cash_account->balance(), abs_error);
}

TEST_F(CashAccountFactoryTestFixture, CashAccountWithdrawFromEmpty)
{
	double initialAmount = 0.0;
	double withdrawAmount = 100.5;
	cash_account->deposit(initialAmount);
	ASSERT_NEAR(initialAmount, cash_account->balance(), abs_error);
	ASSERT_THROW(cash_account->withdraw(withdrawAmount), std::runtime_error);
}

TEST_F(CashAccountFactoryTestFixture, CashAccountNotEnoughFundsAfterDeposit)
{
	double initialAmount = 50.1;
	double withdrawAmount = 100.5;
	cash_account->deposit(initialAmount);
	ASSERT_NEAR(initialAmount, cash_account->balance(), abs_error);
	ASSERT_THROW(cash_account->withdraw(withdrawAmount), std::runtime_error);
}

// ------------------------------------ PaymentCardAccountFactoryTestFixture

class PaymentCardAccountFactoryTestFixture : public testing::Test
{
public:
	void SetUp() override;
	void TearDown() override;
protected:
	PaymentCardAccountFactory* payment_card_factory;
	Account *payment_card_account;
	double abs_error;
};

void PaymentCardAccountFactoryTestFixture::SetUp()
{
	payment_card_factory = new PaymentCardAccountFactory;
	payment_card_account = payment_card_factory->createAccount(0.0);
	abs_error = ABS_ERROR;
}
void PaymentCardAccountFactoryTestFixture::TearDown()
{
	delete payment_card_account;
	delete payment_card_factory;
}

TEST_F(PaymentCardAccountFactoryTestFixture, CreateCardAccountDepoAndWithdraw)
{
	double initialAmount = 978.45;
	double withdrawAmount = 108.32;
	payment_card_account->deposit(978.45);
	ASSERT_NEAR(initialAmount, payment_card_account->balance(), abs_error);
	payment_card_account->withdraw(withdrawAmount);
	ASSERT_NEAR(870.13, payment_card_account->balance(), abs_error);
	payment_card_account->withdraw(870.13);
	ASSERT_NEAR(double(0.00), (double)payment_card_account->balance(), abs_error);
}

TEST_F(PaymentCardAccountFactoryTestFixture, NegativeAmountDepositTest)
{
	double initialAmount = -978.45;
	ASSERT_THROW(payment_card_account->deposit(initialAmount), std::invalid_argument);
}

// -------------------------------------- SavingsAccountFactoryTestFixture

class SavingsAccountFactoryTestFixture : public testing::Test
{
public:
	void SetUp() override;
	void TearDown() override;
protected:
	SavingsAccountFactory *savings_account_factory;
	Account *savings_account;
	double abs_error;
};

void SavingsAccountFactoryTestFixture::SetUp()
{
	savings_account_factory = new SavingsAccountFactory;
	savings_account = savings_account_factory->createAccount(0.0);
	abs_error = ABS_ERROR;
}

void SavingsAccountFactoryTestFixture::TearDown()
{
	delete savings_account;
	delete savings_account_factory;
}

TEST_F(SavingsAccountFactoryTestFixture, CreateSavingsAccountDepoAndWithdraw)
{
	double initialAmount = 50.1;
	double withdrawAmount = 25.5;
	savings_account->deposit(initialAmount);
	ASSERT_NEAR(initialAmount, savings_account->balance(), abs_error);
	savings_account->withdraw(withdrawAmount);
	ASSERT_NEAR(double(24.6), savings_account->balance(), abs_error);
	savings_account->withdraw(double(24.6));
	ASSERT_NEAR(double(0.0), savings_account->balance(), abs_error );
}


TEST_F(PaymentCardAccountFactoryTestFixture, NegativeAmountWithdrawTest)
{
	double initialAmount = 978.45;
	payment_card_account->deposit(initialAmount);
	ASSERT_NEAR(initialAmount, payment_card_account->balance(), abs_error);
	ASSERT_THROW(payment_card_account->withdraw(-100.0), std::invalid_argument);
}


// For 
TEST(HomeAccountSuite, BasicTest)
{
    Logger *logger = Logger::Instance();
	logger->openLogFile("program.log");
	//cout << "test " << endl;
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
	//print_available_commands();
	/*
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
    */
	logger->closeLogFile();
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}